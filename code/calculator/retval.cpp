#include <vector>
#include <iostream>
#include "retval.h"


int minlen(const RetVal& r1, const RetVal& r2)
{
    return (r1.length() < r2.length()) ? r1.length() : r2.length();
}

ostream& operator<<(ostream& os, const RetVal& r)
{ 
    if(r.isdbl())
        return os << r.get_dval();
    else if(r.isvec()) {
        os << "[ ";
        for(double d : r.get_vval())
            os << d << " ";
        return os << "]\n";
    }
    return os << "No val: type undefined\n";
}

RetVal RetVal::operator-() const
{
     RetVal r;
     if(isdbl()) {
         r.rtype = dbl;
         r.dval = -dval;
     }
     else if(isvec()) {
         r.rtype = vec;
         for(double d : vval)
             r.vval.push_back(-d);
     }
     return r;
}

RetVal RetVal::operator+(const RetVal& r2) {
    RetVal r;
    if(isdbl() && r2.isdbl()) {
         r.rtype = dbl;
         r.dval = dval + r2.dval;
    }
    else if(isvec() && r2.isvec()) {
         r.rtype = vec;
         for(int i = 0; i < minlen(*this, r2); i++)
             r.vval.push_back(vval[i] + r2.vval[i]);
    }
    return r;
}
