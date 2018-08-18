#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "const.h"
#include "token.h"
#include "retval.h"
#include "parser.h"
#include "vars.h"

const string prompt = "> ";
const string result = "= ";

void clean_up_mess(TokenStream& ts)   // naive version
{
    ts.ignore(print);
}

void calculate(TokenStream& ts)
{
    while(cin) {
        try {
            cout << prompt;
            Token t = ts.get();
// this output is for debugging:
//            cout << "in main(), got token: " << t.kind
//                << " with val of " << t.value << '\n';
            while(t.kind == print) t = ts.get();  // eat multiple prints!
            if(t.kind == quit) return;
            ts.putback(t);
            RetVal r = statement(ts);
            cout << setprecision(12) << result << r << '\n';
        }
        catch(exception& e) {
            cerr << e.what() << '\n';
            clean_up_mess(ts);
        }
    }

}


int main(int argc, char *argv[])
{
    // add some important constants to our variable table:
    set_value("pi", pi);
    set_value("e", e);

    istream* inp;
    if(argc < 2)
        inp = &cin;

    TokenStream ts(inp);

    try {
        calculate(ts);
        // keep_window_open();   // only if needed!
        return 0;
    }
    catch(...) {
        cerr << "unknown exception \n";
        return 2;
    }
}
