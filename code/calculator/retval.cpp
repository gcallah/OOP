#include <cmath>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "retval.h"


int minlen(const RetVal& r1, const RetVal& r2)
{
    return (r1.length() < r2.length()) ? r1.length() : r2.length();
}

bool equallen(const RetVal& r1, const RetVal& r2)
{
    return (r1.length() == r2.length());
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

RetVal RetVal::exp(double x) const
{
     RetVal r;
     if(isdbl()) {
         r.rtype = dbl;
         r.dval = pow(dval, x);
     }
     else if(isvec()) {
         r.rtype = vec;
         for(double d : vval)
             r.vval.push_back(pow(d, x));
     }
     return r;
}

RetVal RetVal::mod(double m) const
{
     RetVal r;
     if(isdbl()) {
         r.rtype = dbl;
         r.dval = fmod(dval, m);
     }
     else if(isvec()) {
         r.rtype = vec;
         for(double d : vval)
             r.vval.push_back(fmod(d, m));
     }
     return r;
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

RetVal RetVal::operator+=(const RetVal& rhs)
{
    if(this->isdbl()) {
        if(rhs.isdbl())
            this->dval = (this->dval + rhs.dval);
        else
            throw runtime_error("can't add a vector to a double");
    }
    else if(this->isvec()) {
        if(rhs.isdbl()) {
            for(double& d : vval)
                d += rhs.dval;
        }
        else if(rhs.isvec()) {
            for(int i = 0; i < minlen(*this, rhs); i++)
                this->vval[i] += rhs.vval[i];
        }
    }
    return *this;
}

RetVal RetVal::operator-=(const RetVal& rhs)
{
    if(this->isdbl()) {
        if(rhs.isdbl())
            this->dval = (this->dval - rhs.dval);
        else
            throw runtime_error("can't subtract a vector from a double");
    }
    else if(this->isvec()) {
        if(rhs.isdbl()) {
            for(double& d : vval)
                d -= rhs.dval;
        }
        else if(rhs.isvec()) {
            for(int i = 0; i < minlen(*this, rhs); i++)
                this->vval[i] -= rhs.vval[i];
        }
    }
    return *this;
}

RetVal RetVal::operator*=(const RetVal& rhs)
{
    if(this->isdbl()) {
        if(rhs.isdbl())
            this->dval = (this->dval * rhs.dval);
        else
            throw runtime_error("can't multiply a double by a vector");
    }
    else if(this->isvec()) {
        if(rhs.isdbl()) {
            for(double& d : vval)
                d *= rhs.dval;
        }
        else if(rhs.isvec()) {
            if(!equallen(*this, rhs))
                throw runtime_error("dot product requires equal length vectors");
            double d = 0.0;
            for(int i = 0; i < rhs.length(); i++)
                d += this->vval[i] * rhs.vval[i];
            this->rtype = dbl;
            this->dval = d;
        }
    }
    return *this;
}

RetVal RetVal::operator/=(const RetVal& rhs)
{
    if(this->isdbl()) {
        if(rhs.isdbl()) {
            if(rhs.dval == 0) throw runtime_error("divide by zero");
            this->dval = (this->dval / rhs.dval);
        }
        else throw runtime_error("can't divide a double by a vector");
    }
    else if(this->isvec()) {
        if(rhs.isdbl()) {
            for(double& d : vval)
                d /= rhs.dval;
        }
        else if(rhs.isvec())
            throw runtime_error("division is not defined for two vectors");
    }
    return *this;
}

