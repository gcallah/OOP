#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "funcs.h"

using namespace std;

// dispatch table
std::map<const string, std::function<double(double)> > dispTable {
    {"sin", [](double a) { return sin(a); }},
    {"cos", [](double a) { return cos(a); }},
    {"tan", [](double a) { return tan(a); }},
    {"asin", [](double a) { return asin(a); }},
    {"acos", [](double a) { return acos(a); }},
    {"atan", [](double a) { return atan(a); }},
    {"sinh", [](double a) { return sinh(a); }},
    {"cosh", [](double a) { return cosh(a); }},
    {"tanh", [](double a) { return tanh(a); }},
    {"sqrt", [](double a) { return sqrt(a); }},
    {"log", [](double a) { return log(a); }},
    {"log2", [](double a) { return log2(a); }},
    {"log10", [](double a) { return log10(a); }},
};

double exec_func(string fname, double arg)
{
    try {
        return dispTable[fname](arg);
    }
    catch(exception) {
        cout << "Error: undefined function " << fname << '\n';
    }
    return 0.0;   // stop compiler warning!
}
