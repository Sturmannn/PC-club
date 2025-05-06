#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Handler.hpp"

int main(int argc, char *argv[]) {

    // if (argc != 2) {
    //     std::cout << "Specify the path to the text file!" << std::endl;
    //     return -1;
    // }
    try {
        // pc_club::Handler handler(argv[1]);
        pc_club::Handler handler("/home/sturmannn/PC-club/test_file.txt");
        handler.handle_file();
    } catch (const std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    
    // std::string str;
    // std::ifstream in("/home/sturmannn/PC-club/test_file.txt");

    // std::vector<std::string> slova;
    // std::string string = "Petya,Vasya,Manya";

    // while(std::getline(in, str)) {
    //     std::cout << str << std::endl;
    // }

    // std::vector<std::string> tokens;
    // size_t start = 0;
    // char del = ',';
    // size_t end = string.find(del);
    // while (end != std::string::npos) {
    //     tokens.push_back(string.substr(start, end - start));
    //     start = end + 1;
    //     end = string.find(del, start);
    // }
    // tokens.push_back(string.substr(start));

    // for (auto token : tokens) {
    //     std::cout << token << std::endl;
    // }

    return 0;
}