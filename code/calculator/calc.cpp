#include "std_lib_facilities.h"
#include "token.h"
#include "parser.h"

int main()
{
    Token_stream ts;

    try {
        double val = 0.0;
        while(cin) {
            cout << "> ";
            Token t = ts.get();
// this output is for debugging:
//			cout << "in main(), got token: " << t.kind
//				<< " with val of " << t.value << '\n';
            while(t.kind == print) t = ts.get();
            if(t.kind == quit) {
                // keep_window_open();   only if needed!
                return 0;
            }
            ts.putback(t);
            cout << "= " << expression(ts) << '\n';
        }
    }
    catch(exception& e) {
        cerr << e.what() << '\n';
        cout << "Please enter the character ~ to close the window\n";
        for(char ch; cin >> ch; )
            if(ch=='~') return 1;
        return 1;
    }
    catch(...) {
        cerr << "exception \n";
        return 2;
    }
}
