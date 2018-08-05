using namespace std;

enum RetType { dbl, vec, mat, undef };

class RetVal {
    public:
        class WrongRetVal {};
        RetVal() { rtype = undef; }
        RetVal(double d) { dval = d; rtype = dbl; }
        RetVal(vector<double> v) { vval = v; rtype = vec; }
        double get_dval() const { return dval; }
        void set_dval(double d) { dval = d; }
        vector<double> get_vval() const { return vval; }
        void set_vval(vector<double> v) { vval = v; }
        ~RetVal() {}
        bool isdbl() const { return rtype == dbl; }
        bool isvec() const { return rtype == vec; }
        bool ismat() const { return rtype == mat; }
        int length() const { return rtype == dbl ? 1 : vval.size(); }
        RetVal exp(double x) const;
        RetVal mod(double m) const;
        RetVal operator-() const;
        RetVal operator+=(const RetVal& rhs);
        RetVal operator-=(const RetVal& rhs);
        RetVal operator*=(const RetVal& rhs);
        RetVal operator/=(const RetVal& rhs);
private:

    protected:
        double dval = 0.0;
        vector<double> vval;
        RetType rtype = undef; 
};

ostream& operator<<(ostream &os, const RetVal &v);
