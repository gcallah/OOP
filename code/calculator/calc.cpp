#include "std_lib_facilities.h"
#include "token.h"
#include "parser.h"

int main()
{
    Token_stream ts;

    try {
        double val = 0.0;
        while(cin) {
            Token t = ts.get();
// this output is for debugging:
			cout << "in main(), got token: " << t.kind
				<< " with val of " << t.value << '\n';
            if(t.kind == 'q') break;
            if(t.kind == ';')
                cout << " = " << val << '\n';
            else
                ts.putback(t);
            val = expression(ts);
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
