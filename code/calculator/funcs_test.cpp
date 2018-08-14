#include <iostream>
#include <iomanip>
#include <string>
#include "const.h"
#include "funcs.h"

using namespace std;

void calc_print(double d, string f)
{
    cout << setprecision(8) << "d = " << d << "; " << f << "(d) = "
        << exec_func(f, d) << '\n';
}


// test harness for funcs.cpp:
int main()
{
    double incr = pi / 4;
    for(double d = 0.0; d < 3 * pi; d += incr) {
        calc_print(d, "sin");
        calc_print(d, "cos");
        calc_print(d, "tan");
    }
    incr = .5;
    for(double d = 0.0; d < 10; d += incr) {
        calc_print(d, "log");
        calc_print(d, "log10");
        calc_print(d, "gamma");
    }
}
