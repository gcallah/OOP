#include "std_lib_facilities.h"

int main()
{
    cout << "Please enter an expression (we can handle +, -, *, and /):\n";
    cout << "Add an x to end expression (e.g., 1+2*3x): ";
    int lval = 0;
    int rval;
    int res;
    cin >> lval;
    if(!cin) error("No first operand!");
    for(char op; cin >> op;) {   // repeatedly read ops
        if(op!='x') cin >> rval;
        if(!cin) error("No second operand!");
        switch(op) {
        case '+':
            lval += rval;
            break;
        case '-':
            lval -= rval;
            break;
        case '*':
            lval *= rval;
            break;
        case '/':
            lval /= rval;
            break;
        default:
            cout << "Result: " << lval << '\n';
            keep_window_open();  // if necessary on your system!
            return 0;
        }
    }
    error("Bad expression");
}

