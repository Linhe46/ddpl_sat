#include "cnf.h"
#include <algorithm>

bool BCP(int name, bool val, CNF& cnf_form){
    if(cnf_form.clauses.size()==0)
        return true;
    for (auto clause_it = cnf_form.clauses.begin(); clause_it != cnf_form.clauses.end();){
        int state = 0;// 0 for unsolved, 1 for satisfied, -1 for conflict
        for (auto list_it = clause_it->begin(); list_it != clause_it->end();){
            if(*list_it==name||*list_it==-name){//find the literal to be assigned
                bool flag = (*list_it > 0 ? val : !val);//if negative literal, reverse
                if(flag){// get a 1 in the clause, delete the clause
                    state = 1;
                    break;
                }
                else{// get a 0, delete the literal
                    list_it = clause_it->erase(list_it);
                    if(clause_it->size()==0)
                        return false;
                }
            }
            else
                list_it++;// not find the literal
        }
        switch (state)
        {
        case 1:
            clause_it = cnf_form.clauses.erase(clause_it);
            break;
        case 0:
            clause_it++;
            break;
        /*case -1:
            return false;*/
        }
    }
    return true;
}