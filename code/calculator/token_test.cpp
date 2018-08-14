#include <iostream>
#include <vector>
#include "token.h"


// test harness for tokenizer:
int main()
{
    vector<Token> tokens;
    Token_stream ts;

    for(Token t = ts.get(); t.kind != quit; t = ts.get()) {
        tokens.push_back(t);
    }

    for(Token tok : tokens) {
        if(tok.kind == number)
            cout << "A number token with val = " << tok.value << '\n';
        else if(tok.kind == invalid)
            cout << "We received an invalid token of value " 
                << char(tok.value) << '\n';
        else if(tok.kind == name)
            cout << "A variable token with name " << tok.name << '\n';
        else
            cout << "A token of kind " << tok.kind << '\n';
    }
    return 0;
}

