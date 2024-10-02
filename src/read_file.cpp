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
    if(!file.is_open()){
        std::cout<<"Path: "<<path<<" not exist!"<<std::endl;
        std::exit(1);
    }
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
    bool end_head_line = false; // if a clause is received, stop detecting header line
    std::string num_val, num_clause;

    // load clauses
    std::vector<int> clause;
    std::string val;

    // check the variables and clauses count
    int count_clause = 0;
    int count_val = 0;

    // parse every char
    while(id<end){
        char x = input[id];
        // c starts a comment line
        if(x=='c'){
            id++;
            if(id==end)
                throw std::runtime_error("Empty cnf form!");
            else if(input[id]==' '){
                id++;
                while(id<end && input[id]!='\n')
                    id++;
                if(id<end && input[id]=='\n')
                    id++;
            }
            else
                throw std::runtime_error("Illegal text line!");
        }
        // p cnf starts a header line
        else if(!end_head_line && x=='p' && !detect_head_line){
            if(end-id>4 && input.substr(id,5)=="p cnf"){
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
                        else if(_==' ')
                            id += 1;
                        else
                            throw std::runtime_error("Malformed header line!");
                    }
                }
                try{
                        cnf_form->setNum(std::stoi(num_val), std::stoi(num_clause));
                }
                catch(const std::invalid_argument&){
                    throw std::runtime_error("Malformed header line");
                }
            }
            else
                throw std::runtime_error("Illegal line detected!");
        }
        // a number(including a minus sign) starts a clause
        else if(isdigit(x)|| x=='-'){
            end_head_line = true;
            bool end_clause = false;
            while(!end_clause){
                x = input[id];
                // end of a clause
                if(x=='0' && val==""){
                    end_clause = true;
                    cnf_form->addClause(clause);
                    count_clause += 1;
                    // clear clause and read another clause
                    clause.clear(); 
                }
                // parse a literal
                else if(isdigit(x)||x=='-')
                    val += x;
                // end of a literal
                else if(x== ' ' && val!=""){
                    try{
                        int val_num = std::stoi(val);
                        clause.push_back(val_num);
                        count_val = std::max(count_val, val_num);// select the max val as #variable
                    }catch (const std::invalid_argument &){
                        throw std::runtime_error("Malformed clause line!");
                    }
                    val = ""; // clear val and read next val name
                }
                else if(x==' ' || x=='\n'){
                    // neglect redundant space and newline(if existed)
                }
                else{
                    throw std::runtime_error("Malformed clause line!");
                }
                id += 1;
            }
        }
        // neglect empty line
        else if(x==' '||x=='\n')
            id += 1;
        else
            throw std::runtime_error("Illegal line detected!");
    }

    // check the # of vals and clauses
    if(detect_head_line){
        if(std::stoi(num_val)<count_val)// header line must give a #variable no smaller than received
            throw std::runtime_error("Number of variables does not match the header line!");
        if(std::stoi(num_clause)!=count_clause)// header line must give exact # clause
            throw std::runtime_error("Number of clauses does not match the header line!");
    }
    else
        cnf_form->setNum(count_val, count_clause);

    // check if the cnf expression is empty
    if(count_clause==0||count_val==0)
        throw std::runtime_error("Empty cnf expression!");
}
int main(int argc, char* args[]){
    // only accept one input once
    if(argc!=2){
        std::cerr << "Usage: ./" << args[0] << " <cnf_file_path>" << std::endl;
        return 1;
    }
    // parse the input .cnf file
    std::string cnf_path = args[1];
    auto input = read_file(cnf_path);
    CNF* cnf_form = new CNF();
    try{
        getCNF(cnf_form, input);
    }
    catch(std::runtime_error&e){
        std::cout << e.what() << std::endl;
        return 1;
    }
    // DPLL and output results
    bool sat = DPLL(*cnf_form);
    std::cout << (sat ? "SAT" : "UNSAT") << std::endl;
    if(sat)
        cnf_form->printSolution();
    return 0;
}