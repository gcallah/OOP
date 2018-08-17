#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "funcs.h"

using namespace std;

// dispatch tables
std::map<const string, std::function<double(double)> > oneArgFuncs {
    {"acos",  [](double a) { return acos(a); }},
    {"asin",  [](double a) { return asin(a); }},
    {"atan",  [](double a) { return atan(a); }},
    {"cos",   [](double a) { return cos(a); }},
    {"cosh",  [](double a) { return cosh(a); }},
    {"gamma", [](double a) { return tgamma(a); }},
    {"log",   [](double a) { return log(a); }},
    {"log2",  [](double a) { return log2(a); }},
    {"log10", [](double a) { return log10(a); }},
    {"sin",   [](double a) { return sin(a); }},
    {"sinh",  [](double a) { return sinh(a); }},
    {"sqrt",  [](double a) { return sqrt(a); }},
    {"tan",   [](double a) { return tan(a); }},
    {"tanh",  [](double a) { return tanh(a); }},
};

std::map<const string, std::function<double(double, double)> > twoArgFuncs {
    {"C",  [](double n, double k) { return choose(n, k); }},
};

double exec_func(string fname, double arg)
{
    try {
        return oneArgFuncs[fname](arg);
    }
    catch(exception) {
        cout << "Error: undefined function " << fname << '\n';
    }
    return 0.0;   // stop compiler warning!
}

double exec_func(string fname, double arg1, double arg2)
{
    try {
        return twoArgFuncs[fname](arg1, arg2);
    }
    catch(exception) {
        cout << "Error: undefined function " << fname << '\n';
    }
    return 0.0;   // stop compiler warning!
}

double choose(double nd, double kd)
{
    int n = int(nd);
    int k = int(kd);
    if(k == 0) return 1;
    return((n * choose(n - 1, k - 1)) / k);
}

