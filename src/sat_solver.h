#ifndef SAT_SOLVER_H
#define SAT_SOLVER_H

#include <vector>

class SAT_SOLVER{
    public:
        SAT_SOLVER();
        ~SAT_SOLVER();
        void addClause(const std::vector<int> &clause);
        void setNum(int num_val, int num_clause);
        void printClause();
        bool solve();
    private:
        int num_val, num_clause;
        std::vector<std::vector<int>> clauses;
};


#endif