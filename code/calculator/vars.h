
class Variable {
    public:
        string name;
        RetVal value;
};

RetVal get_value(string s);
void set_value(string s, RetVal r);
void print_vars();
