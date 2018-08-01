#include "std_lib_facilities.h"
#include "retval.h"

// test harness for retval.cpp:
int main()
{
    DoubleRet d(4.3);

    cout << d << '\n';

    vector<double> argv = {8.9, 76.1, 0.23, 45.2};
    VectorRet v(argv);

    cout << v << '\n';
}

