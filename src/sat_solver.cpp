#include "sat_solver.h"
#include <iostream>

SAT_SOLVER::SAT_SOLVER(){}
SAT_SOLVER::~SAT_SOLVER(){}
void SAT_SOLVER::addClause(const std::vector<int>& clause){
    clauses.push_back(clause);
}
void SAT_SOLVER::printClause(){
    for(const auto& clause:clauses){
        for(auto i: clause)
            std::cout << i << ' ';
        std::cout << '\n';
    }
}
bool SAT_SOLVER::solve(){
    // solve a sat problem
    return 1;
}
