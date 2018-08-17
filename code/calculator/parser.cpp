#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "token.h"
#include "retval.h"
#include "vars.h"
#include "funcs.h"
#include "parser.h"


RetVal statement(Token_stream& ts)
{
/* grammar recognized:
 Statement:
    Var "=" Expression
    Var ";"
    Expression
 */
    Token t = ts.get();
    if(t.kind == name) {
        Token var = t;
        t = ts.get();
        if(t.kind == '=') {  // an assignment
            RetVal r = expression(ts);
            set_value(var.name, r);
            return r;
        }
        else if(t.kind == print) {
            ts.putback(t);
            return get_value(var.name);
        }
        ts.putback(t);
        ts.putback(var);
        return expression(ts);
    }
    ts.putback(t);
    return expression(ts);
}

RetVal expression(Token_stream& ts)
{
/* grammar recognized:
 Expression:
    Term
    Expression "+" Term
    Expression "-" Term
 */
    RetVal r = term(ts);
    Token t = ts.get();         // get the next token from token stream

    while(true) {    
        switch(t.kind) {
        case '+':
            r += term(ts);    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            r -= term(ts);    // evaluate Term and subtract
            t = ts.get();
            break;
        default: 
            ts.putback(t);     // put t back into the token stream
            return r;  // finally: no more + or -: return the answer
        }
    }
}

RetVal term(Token_stream& ts)
{
/* grammar recognized:
Term:
    Expon
    Term "*" Expon
    Term "/" Expon
    Term mod Expon
    Term cross Expon
*/
    RetVal r = exp_fact(ts);
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '*':
            r *= exp_fact(ts);
            t = ts.get();
            break;
        case '/':
            r /= exp_fact(ts); 
            t = ts.get();
            break;
        case mod:
            {
                RetVal rhs = exp_fact(ts);
                if(rhs.isvec()) throw runtime_error("can't mod by a vector");
                double m = rhs.get_dval();
                if(m == 0) throw runtime_error("divide by zero");
                r = r.mod(m);
                t = ts.get();
                break;
            }
        case cross:
            {
                RetVal rhs = exp_fact(ts);
                return r.cross(rhs);
            }
        default: 
            ts.putback(t);     // put t back into the token stream
            return r;
        }
    }
}

RetVal exp_fact(Token_stream& ts)
{
/* grammar recognized:
Exp:
    Primary
    Primary power Primary
    Primary fact
*/
    double left;
    RetVal r = primary(ts);

    Token t = ts.get();
    if(t.kind == power) {
        double x = primary(ts).get_dval();
        return r.exp(x);
    }
    else if(t.kind == fact) {
        return r.fact();
    }
    else {
        ts.putback(t);     // put t back into the token stream
        return r;
    }
}

RetVal primary(Token_stream& ts)
{
/* grammar recognized:
Primary:
    Number
    "(" Expression ")"
    "[" Vector "]"
    +Number
    -Number
    Variable
    -Variable
    +Variable
    Function "(" Expression ")"
*/
    Token t = ts.get();
    cout << t << '\n';
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
        {    
            double d = expression(ts).get_dval();
            t = ts.get();
            if (t.kind != ')') throw runtime_error("')' expected");
            return RetVal(d);
        }
    case '[':    // handle '[' vector ']'
        {
            vector<double> v;
            for(Token next_t = ts.get(); next_t.kind != ']'; next_t = ts.get()) {
                ts.putback(next_t);
                RetVal r = primary(ts).get_dval();
                v.push_back(r.get_dval());
            }
            return RetVal{v};
        }
    case number:
        return RetVal(t.value);  // return the number's value
    case name:
        {
            Token next_t = ts.get();
            if(next_t.kind == '(') {
                double ret;
                double arg1 = expression(ts).get_dval();
                next_t = ts.get();
                // multi-arg func (2 for now!)
                if (next_t.kind == ',') {
                    double arg2 = expression(ts).get_dval();
                    ret = exec_func(t.name, arg1, arg2);
                    next_t = ts.get();
                }
                // single arg func:
                else ret = exec_func(t.name, arg1);

                if (next_t.kind != ')') throw runtime_error("')' expected");
                return RetVal(ret);
            }
            else {
                ts.putback(next_t);
                return RetVal(get_value(t.name));
            }
        }
    case '-':
        return -(primary(ts));
    case '+':
        return primary(ts);
    default:
        string s(1, t.kind);
        throw runtime_error("primary expected; got: " + s);
    }
    return RetVal(0.0);
}

