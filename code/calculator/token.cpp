#include <iostream>
#include <string>
#include <vector>
#include "token.h"


std::ostream &operator<<(std::ostream &os, const Token &t) { 
    os << "Token of kind: ";
    os << t.kind;
    switch(t.kind) {
        case number:
            cout << " with a value of " << t.value;
            break;
        case name:
            cout << " with name " << t.name;
            break;
    }
    return os;
}


void Token_stream::putback(Token t)
{
    buffer.push_back(t);
}

Token Token_stream::popback()
{
    Token t = buffer.back();
    buffer.pop_back();
    return t;
}

Token Token_stream::get() {
    if(buffer.size() > 0) {
        Token t = popback();
        return t;
    }
    char ch;
    cin >> ch;
    switch(ch) {
        case print:
        case quit:
        case '(':
        case ')':
        case '[':
        case ']':
        case '+':
        case '-':
        case '/':
        case '*':
        case '=':
        case ',':
        case mod:
        case power:
        case fact:
        case cross:
            return Token{ch};
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            cin.putback(ch);
            double val;
            cin >> val;
            return Token{number, val};
        }
        default:
            if(isalpha(ch)) {
                string s;
                s += ch;
                while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
                cin.putback(ch);
                return Token{name, s};
            }
            return Token{invalid, double(ch)};
    }
    return Token{quit};
}

void Token_stream::ignore(char c)
    // c is token kind to look for
{
    // first check buffer:
    while(buffer.size() > 0) {
        Token t = popback();
        if(t.kind == c) return;
    }

    // now search input:
    char ch = 0;
    while(cin>>ch)
        if(ch == c) return;
}

