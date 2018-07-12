#include "std_lib_facilities.h"

int main()
{
    cout <<"Please enter an expression (we can handle + and -):\n";
    int lval = 0;
    int rval;
    char op;
    int res;
    cin >> lval >> op >> rval; // read e.g. 1 + 3

    if(op=='+')
        res = lval + rval;
    else if(op=='-')
        res = lval - rval;

    cout << "Result: " << res << '\n';
    return 0;
}
