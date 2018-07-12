#include "std_lib_facilities.h"
#include "parser.h"

int main()
{
    try {
        while(cin) {
            int flag;
            cout << expression() << '\n';
            cin >> flag;
        }
        // keep_window_open();   only if needed!
    }
    catch(exception& e) {
        cerr << e.what() << '\n';
        return 1;
    }
    catch(...) {
        cerr << "exception \n";
        return 2;
    }
}
