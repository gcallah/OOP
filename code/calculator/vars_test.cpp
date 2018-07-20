#include "std_lib_facilities.h"
#include "vars.h"

// test harness for vars.cpp:
int main()
{
    set_value("foo", 12.2);
    set_value("goo", 16.2);
    set_value("blue", 2.2);
    set_value("grue", 145.3);
    set_value("foo", 2.9);

    double d;
    d = get_value("foo");
    cout << "foo = " << d << endl;
    d = get_value("goo");
    cout << "goo = " << d << endl;
    d = get_value("blue");
    cout << "blue = " << d << endl;
    d = get_value("grue");
    cout << "grue = " << d << endl;
}
