
enum RetType { dbl, vec, mat, undef };

class RetVal {
    public:
        class WrongRetVal {};
        RetVal(double d) { dval = d; rtype = dbl; }
        RetVal(vector<double> v) { vval = v; rtype = vec; }
        virtual double get_dval() const { return dval; }
        virtual vector<double> get_vval() const { return vval; }
        ~RetVal() {}
        bool isdbl() const { return rtype == dbl; }
        bool isvec() const { return rtype == vec; }
        bool ismat() const { return rtype == mat; }
    protected:
        RetVal() {}
        double dval = 0.0;
        vector<double> vval;
        RetType rtype = undef; 
};

ostream& operator<<(ostream &os, const RetVal &v);
