#include "std_lib_facilities.h"
#include "token.h"
#include "vars.h"
#include "funcs.h"
#include "parser.h"

double statement(Token_stream& ts)
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
            double d = expression(ts);
            set_value(var.name, d);
            return d;
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

double expression(Token_stream& ts)
{
/* grammar recognized:
 Expression:
    Term
    Expression "+" Term
    Expression "-" Term
 */
    double left = term(ts);      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {    
        switch(t.kind) {
        case '+':
            left += term(ts);    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term(ts);    // evaluate Term and subtract
            t = ts.get();
            break;
        default: 
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

double term(Token_stream& ts)
{
/* grammar recognized:
Term:
    Expon
    Term "*" Expon
    Term "/" Expon
    Term "%" Expon
*/
    double left = expon(ts);
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '*':
            left *= expon(ts);
            t = ts.get();
            break;
        case '/':
            {    
                double d = expon(ts);
                if (d == 0) error("divide by zero");
                left /= d; 
                t = ts.get();
                break;
            }
        case '%':
            {
                double d = expon(ts);
                if (d == 0) error("divide by zero");
                left = fmod(left, d);
                t = ts.get();
                break;
            }
        default: 
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }

}

double expon(Token_stream& ts)
{
/* grammar recognized:
Exp:
    Primary
    Primary "^" Primary
*/
    double left = primary(ts);
    Token t = ts.get();
    if(t.kind == power) {
        double d = primary(ts);
        return pow(left, d);
    }
    else {
        ts.putback(t);     // put t back into the token stream
        return left;
    }
}

double primary(Token_stream& ts)
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
            double d = expression(ts);
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
    case number:
        return t.value;  // return the number's value
    case name:
        {
            Token next_t = ts.get();
            if(next_t.kind == '(') {
                double d = expression(ts);
                d = exec_func(t.name, d);
                t = ts.get();
                if (t.kind != ')') error("')' expected");
                return d;
            }
            else {
                ts.putback(next_t);
                return get_value(t.name);
            }
        }
    case '-':
        return -primary(ts);
    case '+':
        return primary(ts);
    default:
        error("primary expected");
    }
    return 0.0;
}

