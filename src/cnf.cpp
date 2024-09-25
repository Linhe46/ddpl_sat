#include "cnf.h"
#include <iostream>

CNF::CNF(){}
CNF::~CNF(){}
void CNF::addClause(const std::vector<int>& clause){
    clauses.push_back(clause);
}
void CNF::setNum(int num_val, int num_clause){
    this->num_val = num_val;
    this->num_clause = num_clause;
}
void CNF::printClause(){
    for(const auto& clause:clauses){
        for(auto i: clause)
            std::cout << i << ' ';
        std::cout << '\n';
    }
}
