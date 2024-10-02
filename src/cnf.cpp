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
void CNF::printSolution(){
    for (int i = 1; i <= num_val;i++){
        //std::cout << i << ": " << std::boolalpha << solution[i] << '\n';
        std::cout << (solution[i] ? "" : "-") << i << ' ';
    }
}