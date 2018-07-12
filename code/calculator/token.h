
class Token {
public:
    char kind;
    double value;
};

class Token_stream {
    public:
        Token get();
        void putback(Token t);
    private:
        bool full{false};
        Token buffer;
};

