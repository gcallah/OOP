
class Retval {
    public:
        class WrongRetval {};
        virtual double get_dval() const { return dval; }
        virtual vector<double> get_vval() const { return vval; }
        ~Retval() {}
    protected:
        Retval() {}
        double dval = 0.0;
        vector<double> vval;
};

class DoubleRet : public Retval {
    public:
        DoubleRet(double d) { dval = d; }
        virtual vector<double> get_vval() const { throw WrongRetval(); }
};

class VectorRet : public Retval {
    public:
        VectorRet(vector<double> v) { vval = v; }
        virtual double get_dval() const { throw WrongRetval(); }
};

ostream& operator<<(ostream &os, const Retval &r);
ostream& operator<<(ostream &os, const DoubleRet &d);
ostream& operator<<(ostream &os, const VectorRet &v);
