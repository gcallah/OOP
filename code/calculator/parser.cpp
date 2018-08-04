#include "std_lib_facilities.h"
#include "token.h"
#include "vars.h"
#include "funcs.h"
#include "retval.h"
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
//        cout << "Got a var with name " << var.name << endl;
        t = ts.get();
        if(t.kind == '=') {  // an assignment
            double d = expression(ts).get_dval();
            set_value(var.name, d);
            return RetVal(d);
        }
        else if(t.kind == print) {
            ts.putback(t);
            return RetVal(get_value(var.name));
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
    double left;
    RetVal r = term(ts);
    if(r.isvec()) return r;    // for now!

    left = r.get_dval();  // read and evaluate a Term
    Token t = ts.get();         // get the next token from token stream

    while(true) {    
        switch(t.kind) {
        case '+':
            left += term(ts).get_dval();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term(ts).get_dval();    // evaluate Term and subtract
            t = ts.get();
            break;
        default: 
            ts.putback(t);     // put t back into the token stream
            return RetVal(left);  // finally: no more + or -: return the answer
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
    Term "%" Expon
*/
    RetVal r = expon(ts);
    if(r.isvec()) {
        return r;    // for now!
    }
    else {
        double left = r.get_dval();
        Token t = ts.get();        // get the next token from token stream
    
        while(true) {
            switch (t.kind) {
            case '*':
                left *= expon(ts).get_dval();
                t = ts.get();
                break;
            case '/':
                {    
                    double d = expon(ts).get_dval();
                    if (d == 0) error("divide by zero");
                    left /= d; 
                    t = ts.get();
                    break;
                }
            case '%':
                {
                    double d = expon(ts).get_dval();
                    if (d == 0) error("divide by zero");
                    left = fmod(left, d);
                    t = ts.get();
                    break;
                }
            default: 
                ts.putback(t);     // put t back into the token stream
                return RetVal(left);
            }
        }
    }
}

RetVal expon(Token_stream& ts)
{
/* grammar recognized:
Exp:
    Primary
    Primary "^" Primary
*/
    double left;
    RetVal r = primary(ts);
    if(r.isvec()) return r;    // for now!

    left = r.get_dval();
    Token t = ts.get();
    if(t.kind == power) {
        double d = primary(ts).get_dval();
        return RetVal(pow(left, d));
    }
    else {
        ts.putback(t);     // put t back into the token stream
        return RetVal(left);
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
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
        {    
            double d = expression(ts).get_dval();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
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
                double d = expression(ts).get_dval();
                next_t = ts.get();
                if (next_t.kind != ')') error("')' expected");
                d = exec_func(t.name, d);
                return RetVal(d);
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
        error("primary expected; got: " + s);
    }
    return RetVal(0.0);
}

