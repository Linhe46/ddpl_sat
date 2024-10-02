#ifndef CNF_H
#define CNF_H

#include <vector>
#include <list> 
#include <unordered_map>

class CNF{
    public:
        CNF();
        CNF(const CNF &cnf);
        ~CNF();
        void addClause(const std::vector<int> &clause);
        void setNum(int num_val, int num_clause);
        void printClause();
        void printSolution();

        friend bool DPLL(CNF& cnf_form);
        friend bool BCP(int name, bool val, CNF& cnf_form);

    private:
        int num_val, num_clause;
        std::vector<bool> assigned;
        std::vector<bool> solution;
        std::list<std::list<int>> clauses;
};



#endif