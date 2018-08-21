using namespace std;

enum RetType { dbl, vec, mat, undef };

class RetVal {
    public:
        class WrongRetVal {};
        RetVal() { rtype = undef; }
        RetVal(double d) { dval = d; rtype = dbl; }
        RetVal(vector<double> v) { vval = v; rtype = vec; }
        RetVal(vector<vector<double>> m) { mval = m; rtype = mat; }
        double get_dval() const { return dval; }
        void set_dval(double d) { dval = d; }
        vector<double> get_vval() const { return vval; }
        void set_vval(vector<double> v) { vval = v; }
        vector<vector<double>> get_mval() const { return mval; }
        void set_mval(vector<vector<double>> m) { mval = m; }
        ~RetVal() {}
        bool isdbl() const { return rtype == dbl; }
        bool isvec() const { return rtype == vec; }
        bool ismat() const { return rtype == mat; }
        int length() const { 
            switch(rtype) {
                case dbl: return 1;
                case vec: return vval.size();
                case mat: return mval.size();
                case undef: return 0;
            }
        }
        RetVal exp(double x) const;
        RetVal fact() const;
        RetVal mod(double m) const;
        RetVal cross(const RetVal& rhs) const;
        RetVal operator-() const;
        RetVal operator+=(const RetVal& rhs);
        RetVal operator-=(const RetVal& rhs);
        RetVal operator*=(const RetVal& rhs);
        RetVal operator/=(const RetVal& rhs);
private:

    protected:
        double dval = 0.0;
        vector<double> vval;
        vector<vector<double>> mval;
        RetType rtype = undef; 
};

ostream& operator<<(ostream &os, const RetVal &v);
