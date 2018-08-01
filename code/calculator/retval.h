
class Retval {
    public:
        double get_dval() { return 0.0; }
};

class DoubleRet : Retval {
    public:
        DoubleRet(double d) { val = d; }
        double get_dval() { return val; }
        double val = 0.0;
};

class VectorRet : Retval {
    public:
        VectorRet(vector<double> v) { val = v; }
        vector<double> val;
};


ostream& operator<<(ostream &os, const Retval &r);
ostream& operator<<(ostream &os, const DoubleRet &d);
ostream& operator<<(ostream &os, const VectorRet &v);
