#include <vector>
#include <iostream>
#include "retval.h"
#include "vars.h"

vector<Variable> var_table;

RetVal get_value(string s)
{
    for(Variable var : var_table) 
        if(var.name == s) return var.value;

    return RetVal{0.0};
}

void set_value(string s, RetVal r)
{
    for(Variable& var : var_table)
        if(var.name == s) {
            var.value = r;
            return;
        }
    // if var not in table, we choose to add it:
    var_table.push_back(Variable{s, r});
}

void print_vars()
{
    for(Variable var : var_table)
        cout << "Var " << var.name; // we want val here at some point
}

