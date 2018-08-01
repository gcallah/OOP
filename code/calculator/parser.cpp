#include "std_lib_facilities.h"
#include "token.h"
#include "vars.h"
#include "funcs.h"
#include "retval.h"
#include "parser.h"

Retval statement(Token_stream& ts)
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
            return DoubleRet(d);
        }
        else if(t.kind == print) {
            ts.putback(t);
            return DoubleRet(get_value(var.name));
        }
        ts.putback(t);
        ts.putback(var);
        return expression(ts);
    }
    ts.putback(t);
    return expression(ts);
}

Retval expression(Token_stream& ts)
{
/* grammar recognized:
 Expression:
    Term
    Expression "+" Term
    Expression "-" Term
 */
    double left = term(ts).get_dval();  // read and evaluate a Term
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
            return DoubleRet(left);  // finally: no more + or -: return the answer
        }
    }
}

Retval term(Token_stream& ts)
{
/* grammar recognized:
Term:
    Expon
    Term "*" Expon
    Term "/" Expon
    Term "%" Expon
*/
    double left = expon(ts).get_dval();
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
            return DoubleRet(left);
        }
    }

}

Retval expon(Token_stream& ts)
{
/* grammar recognized:
Exp:
    Primary
    Primary "^" Primary
*/
    double left = primary(ts).get_dval();
    Token t = ts.get();
    if(t.kind == power) {
        double d = primary(ts).get_dval();
        return DoubleRet(pow(left, d));
    }
    else {
        ts.putback(t);     // put t back into the token stream
        return DoubleRet(left);
    }
}

Retval primary(Token_stream& ts)
{
/* grammar recognized:
Primary:
    Number
    "(" Expression ")"
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
            return DoubleRet(d);
        }
    case number:
        return DoubleRet(t.value);  // return the number's value
    case name:
        {
            Token next_t = ts.get();
            if(next_t.kind == '(') {
                double d = expression(ts).get_dval();
                next_t = ts.get();
                if (next_t.kind != ')') error("')' expected");
                d = exec_func(t.name, d);
                return DoubleRet(d);
            }
            else {
                ts.putback(next_t);
                return DoubleRet(get_value(t.name));
            }
        }
    case '-':
        return DoubleRet(-(primary(ts).get_dval()));
    case '+':
        return primary(ts);
    default:
        error("primary expected");
    }
    return DoubleRet(0.0);
}

