#include "std_lib_facilities.h"
#include "retval.h"


ostream& operator<<(ostream& os, const Retval& r) { 
    return os << "No val: instance of base type\n";
}

ostream& operator<<(ostream& os, const DoubleRet& d) { 
    return os << d.val;
}

ostream& operator<<(ostream& os, const VectorRet& v) { 
    os << "[ ";
    for(double d : v.val)
        os << d << " ";
    return os << "]\n";
}
