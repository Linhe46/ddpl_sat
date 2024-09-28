#include "cnf.h"
#include <iostream>

CNF::CNF(){}
CNF::CNF(const CNF& cnf){
    assigned = cnf.assigned;
    solution = cnf.solution;
    clauses = cnf.clauses;
    num_val = cnf.num_val;
    num_clause = cnf.num_clause;
}
CNF::~CNF(){}
void CNF::addClause(const std::vector<int>& clause){
    clauses.push_back(std::list<int>(clause.begin(), clause.end()));
}
void CNF::setNum(int num_val, int num_clause){
    this->num_val = num_val;
    this->num_clause = num_clause;
    assigned.assign(num_val + 1, false);
    solution.assign(num_val + 1, false);
    assigned[0] = true;
}
void CNF::printClause(){
    for(const auto& clause:clauses){
        for(auto i: clause)
            std::cout << i << ' ';
        std::cout << '\n';
    }
}
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
    //Assignment BCP
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
                        state = -1;
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
        case -1:
            return false;
        }
    }
    return true;
}

void CNF::printSolution(){
    for (int i = 1; i <= num_val;i++){
        //std::cout << i << ": " << std::boolalpha << solution[i] << '\n';
        std::cout << (solution[i] ? "" : "-") << i << ' ';
    }
}