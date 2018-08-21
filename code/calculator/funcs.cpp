#include <cmath>
#include <limits>
#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "funcs.h"

using namespace std;

bool almost_equal(double d1, double d2, double m)
{
    return(abs(d1 - d2) <= m * numeric_limits<double>::epsilon());
}

double choose(double nd, double kd)
{
    int n = int(nd);
    int k = int(kd);
    if(k == 0) return 1;
    return((n * choose(n - 1, k - 1)) / k);
}


double cosine(double a)
{
    double ret = cos(a);
    if(almost_equal(ret, 0.0, 2.5)) return 0.0;
    else if(almost_equal(ret, 1.0, 2.5)) return 1.0;
    else return ret;
}


double sine(double a)
{
    double ret = sin(a);
    if(almost_equal(ret, 0.0, 2.5)) return 0.0;
    else if(almost_equal(ret, 1.0, 2.5)) return 1.0;
    else return ret;
}


// dispatch tables
std::map<const string, std::function<double(double)> > oneArgFuncs {
    {"abs",   [](double a) { return abs(a); }},
    {"acos",  [](double a) { return acos(a); }},
    {"asin",  [](double a) { return asin(a); }},
    {"atan",  [](double a) { return atan(a); }},
    {"ceil",  [](double a) { return ceil(a); }},
    {"cos",   [](double a) { return cosine(a); }},
    {"cosh",  [](double a) { return cosh(a); }},
    {"floor", [](double a) { return floor(a); }},
    {"gamma", [](double a) { return tgamma(a); }},
    {"log",   [](double a) { return log(a); }},
    {"log2",  [](double a) { return log2(a); }},
    {"log10", [](double a) { return log10(a); }},
    {"sin",   [](double a) { return sine(a); }},
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

