#include <iostream>
#include <fstream>
#include <cassert>
#include <iomanip>
#include <cctype>
#include "cnf.h"

std::string read_file(const std::string& path){
    std::ifstream file(path);
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
    while(id<end){
        char x = input[id];
        if(x=='p'){
            if(end-id>=5 && input.substr(id,6)=="p cnf "){
                detect_head_line = true;
                id += 6;
                break;
            }
            else
                throw std::runtime_error("No head line p cnf the .cnf file!");
        }
        else
            id++;
    }
    if(!detect_head_line)
        throw std::runtime_error("No head line in the file!");
    // detect num_val and num_clause
    std::string num_val = "";
    std::string num_clause = "";
    bool get_num_val = false;
    while(id<end){
        char x = input[id];
        if(isdigit(x)){
            //std::cout << 'x' << std::endl;
            get_num_val ? num_clause += x : num_val += x;
            id += 1;
        }
            else if (x == ' ')
            {
                if (num_val != "")
                    get_num_val = true;
                id += 1;
                continue;
        }
        else if(x=='\n'){
            id += 1;
            break;
        }
    }
    cnf_form->setNum(std::stoi(num_val), std::stoi(num_clause));
    //std::cout << num_val << ' ' << num_clause << std::endl;
    //std::cout << "now id is at char:" << input[id] << '\n';

    // load clauses
    std::vector<int> clause;
    std::string val;
    while(id<end){
        char x = input[id];
        if(x=='0' && val==""){
            cnf_form->addClause(clause);
            /*
            for(auto x:clause)
                std::cout << x << ',';
            std::cout << '\n';
            */
            clause.clear(); //clear clause and read another clause
        }
        else if(isdigit(x)||x=='-')
            val += x;
        else if (x == ' '){
            clause.push_back(std::stoi(val));
            val = ""; //clear val and read next val name
        }
        id += 1;
    }
}
int main(int argc, char* args[]){
    assert(argc == 2);
    std::string cnf_path = args[1];
    auto input = read_file(cnf_path);
    //std::cout << input << '\n';
    CNF* cnf_form = new CNF();
    try{
        getCNF(cnf_form, input);
    }
    catch(std::runtime_error&){
        std::cout << "Malformed .cnf file!" << std::endl;
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