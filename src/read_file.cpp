#include <iostream>
#include <fstream>

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
int main(){
    std::string s;
    std::cin>>s;
    std::cout<<read_file(s);
    return 0;
}