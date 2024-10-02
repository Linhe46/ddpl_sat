#include "cnf.h"
#include <algorithm>

bool DPLL(CNF& cnf_form){
    //All literals are assigned vals, and no conflict occurred
    if(std::count(cnf_form.assigned.begin(),cnf_form.assigned.end(),true)-1
        == cnf_form.num_val)
        return true;

    //Unit Clause Rule BCP
    for (const auto &clause : cnf_form.clauses)
        if(clause.size()==1){
            int name = *clause.begin();
            bool val = (name > 0 ? true : false);
            name = (val ? name : -name);// assigned positive literal
            cnf_form.assigned[name] = true;
            cnf_form.solution[name] = val;
            if(!BCP(name, val , cnf_form))
                return false;
    }
    //Assignment
    for (int i = 1; i <= cnf_form.num_val;i++){
        if(!cnf_form.assigned[i]){
            cnf_form.assigned[i] = true;
            // false branch
            cnf_form.solution[i] = false;
            CNF cnf_false = cnf_form;
            if(BCP(i, false, cnf_false)&&DPLL(cnf_false)){
                cnf_form = cnf_false;
                return true;
            }
            // true branch
            cnf_form.solution[i] = true;
            CNF cnf_true = cnf_form;
            if (BCP(i, true, cnf_true) && DPLL(cnf_true)){
                cnf_form = cnf_true;
                return true;
            }
            // two branched failed both
            cnf_form.assigned[i] = false;
            return false;
        }
    }
    //No literals to be assigned, thus SAT
    return true;
}