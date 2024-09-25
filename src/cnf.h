#ifndef CNF_H
#define CNF_H

#include <vector>

class CNF{
    public:
        CNF();
        ~CNF();
        void addClause(const std::vector<int> &clause);
        void setNum(int num_val, int num_clause);
        void printClause();
    private:
        int num_val, num_clause;
        std::vector<std::vector<int>> clauses;
};


#endif