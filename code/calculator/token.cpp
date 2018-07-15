#include "std_lib_facilities.h"
#include "token.h"


// uncomment this for testing:
//int main()
//{
// vector<Token> tokens;
//    // frazzyswizel!
//    for(Token t = get_token(); t.kind != 'q'; t = get_token()) {
//    	tokens.push_back(t);
//	}
//
//	for(Token tok : tokens) {
//        if(tok.kind == '8')
//		    cout << "A number token with val = " << tok.value << '\n';
//        else if(tok.kind == 'i')
//		    cout << "We received an invalid token of value " 
//                << char(tok.value) << '\n';
//        else
//		    cout << "A token of kind " << tok.kind << '\n';
//	}
//    return 0;
//}

std::ostream &operator<<(std::ostream &os, Token const &t) { 
    return os << t.kind;
}


void Token_stream::putback(Token t)
{
    buffer =t;
    full = true;
}

Token Token_stream::get() {
    if(full) {
        full = false;
        return buffer;
    }
	char ch;
	cin >> ch;
	switch(ch) {
    	case print:
    	case quit:
        case '(':
        case ')':
        case '+':
        case '-':
        case '/':
        case '*':
        case '%':
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
            return Token{'i', double(ch)};
	}
    return Token{'q'};
}
