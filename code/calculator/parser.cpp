#include "std_lib_facilities.h"
#include "token.h"
#include "parser.h"

double expression(Token_stream& ts)
{
/* grammar recognized:
 *
 Expression:
    Term
    Expression "+" Term
    Expression "-" Term
 *
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
    double left = primary(ts);
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '*':
            left *= primary(ts);
            t = ts.get();
            break;
        case '/':
            {    
                double d = primary(ts);
                if (d == 0) error("divide by zero");
                left /= d; 
                t = ts.get();
                break;
            }
        case '%':
            {
                double d = primary(ts);
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

double primary(Token_stream& ts)
{
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
    case '-':
        return -primary(ts);
    case '+':
        return primary(ts);
    default:
        error("primary expected");
    }
}

