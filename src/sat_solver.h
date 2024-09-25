#ifndef SAT_SOLVER_H
#define SAT_SOLVER_H

#include <vector>

class SAT_SOLVER{
    public:
        SAT_SOLVER(int, int);
        ~SAT_SOLVER();
        void addClause(const std::vector<int> &clause);
        void printClause();
        bool solve();
    private:
        int num_val, num_clause;
        bool checkInput();
        std::vector<std::vector<int>> clauses;
};


#endif