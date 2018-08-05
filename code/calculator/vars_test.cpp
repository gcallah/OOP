#include <vector>
#include <iostream>
#include "retval.h"
#include "vars.h"

// test harness for vars.cpp:
int main()
{
    vector<double> v = {23.3, 43.2, 39.8};
    set_value("foo", RetVal{13.2});
    set_value("goo", RetVal{44.2});
    set_value("blue", RetVal{10.9});
    set_value("grue", RetVal{v});
    set_value("foo", RetVal{23.5});

    RetVal r = get_value("foo");
    cout << "foo = " << r << endl;
    r = get_value("goo");
    cout << "goo = " << r << endl;
    r = get_value("blue");
    cout << "blue = " << r << endl;
    r = get_value("grue");
    cout << "grue = " << r << endl;
}
