#include "std_lib_facilities.h"
#include "retval.h"


ostream& operator<<(ostream& os, const RetVal& r) { 
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

