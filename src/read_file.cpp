#include <iostream>
#include <fstream>
#include <cassert>
#include <iomanip>
#include <cctype>
#include <set>
#include "cnf.h"

std::string read_file(const std::string& path){
    std::ifstream file(path);
    // if file not existed, exit with code 1
    if(!file.is_open())
        std::exit(1);
    std::string s;
    char x;
    while(file.get(x))
        s += x;
    return s;
}
void getCNF(CNF* cnf_form, const std::string& input){
    int id = 0;
    int end = input.size();

    // parse head lines and get num_val, num_clause
    bool detect_head_line = false;
    std::string num_val, num_clause;

    // load clauses
    std::vector<int> clause;
    std::string val;

    // check the variables and clauses count
    std::set<int> all_val;
    int count_clause=0;

    while(id<end){
        char x = input[id];
        // c starts a comment line
        if(x=='c'){
            id++;
            if(id==end)
                throw std::runtime_error("Empty cnf form!");
            else if(input[id]==' '){
                id++;
                while(id<end&&input[id]!='\n')
                    id++;
                if(id<end && input[id]=='\n')
                    id++;
            }
            else
                throw std::runtime_error("Illegal text line!");
        }
        // p cnf starts a head line
        else if(x=='p'&&!detect_head_line){
            if(end-id>=4 && input.substr(id,5)=="p cnf"){
                detect_head_line = true;
                id += 5;
                bool get_num_val = false;
                if(id==end)
                    throw std::runtime_error("Malformed header line!");
                else if(input[id]==' '){
                    id++;
                    while(id<end){
                        char _ = input[id];
                        if(isdigit(_)){
                            get_num_val ? num_clause += _ : num_val += _;
                            id += 1;
                        }
                        else if(_==' '&&!get_num_val){
                            get_num_val = true;
                            id += 1;
                        }
                        else if(_=='\n'){
                            id += 1;
                            break;
                        }
                        else
                            throw std::runtime_error("Malformed header line!");
                    }
                    try{
                        cnf_form->setNum(std::stoi(num_val), std::stoi(num_clause));
                    }
                    catch(const std::invalid_argument&){
                        throw std::runtime_error("Malformed header line");
                    }
                }
            }
            else
                throw std::runtime_error("Illegal text line!");
        }
        else {
            if(x=='0' && val==""){
                cnf_form->addClause(clause);
                std::transform(clause.begin(), clause.end(), clause.begin(), [](int n)
                               { return std::abs(n); });// only count once for pos and neg literal
                all_val.insert(clause.begin(), clause.end());
                count_clause += 1;
                clause.clear(); // clear clause and read another clause
            }
            else if(isdigit(x)||x=='-')
                val += x;
            else if (x == ' '){
                try{
                    clause.push_back(std::stoi(val));
                }
                catch(const std::invalid_argument&){
                    throw std::runtime_error("Malformed header line!");
                }
                val = ""; // clear val and read next val name
            }
            id += 1;
        }
    }

    if(detect_head_line){
        if(std::stoi(num_val)<all_val.size())// real #val must <= num_val
            throw std::runtime_error("Number of variables not match the header line!");
        if(std::stoi(num_clause)!=count_clause)
            throw std::runtime_error("Number of clauses not match the header line!");
    }

    if(count_clause==0||all_val.size()==0)
        throw std::runtime_error("Empty cnf form!");
}
int main(int argc, char* args[]){
    //assert(argc == 2);
    if(argc!=2){
        std::cerr << "Usage: ./" << args[0] << " <cnf_file_path>" << std::endl;
        return 1;
    }
    std::string cnf_path = args[1];
    auto input = read_file(cnf_path);
    // std::cout << input << '\n';
    CNF* cnf_form = new CNF();
    try{
        getCNF(cnf_form, input);
    }
    catch(std::runtime_error&e){
        std::cout << e.what() << std::endl;
        return 1;
    }
    //cnf_form->printClause();
    //std::cout<<(BCP(1, 0, *cnf_form) ? "true" : "false")<<std::endl;
    //std::cout<<(BCP(2, 1, *cnf_form) ? "true" : "false")<<std::endl;
    //std::cout<<(BCP(3, 1, *cnf_form) ? "true" : "false")<<std::endl;
    bool sat = DPLL(*cnf_form);
    std::cout << (sat ? "SAT" : "UNSAT") << std::endl;
    if(sat)
        cnf_form->printSolution();
    return 0;
}