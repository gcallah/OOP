#include "std_lib_facilities.h"
#include "token.h"
#include "parser.h"

const string prompt = "> ";
const string result = "= ";

void calculate(Token_stream& ts)
{
    while(cin) {
        cout << prompt;
        Token t = ts.get();
// this output is for debugging:
//			cout << "in main(), got token: " << t.kind
//				<< " with val of " << t.value << '\n';
        while(t.kind == print) t = ts.get();
        if(t.kind == quit) return;
        ts.putback(t);
        cout << result << expression(ts) << '\n';
    }
}


int main()
{
    Token_stream ts;

    try {
        calculate(ts);
        // keep_window_open();   only if needed!
        return 0;
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
