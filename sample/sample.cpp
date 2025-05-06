#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Handler.hpp"

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cout << "Specify the path to the text file!" << std::endl;
    return -1;
  }
  try {
    pc_club::Handler handler(argv[1]);
    handler.handle_file();
  } catch (const std::runtime_error &e) {
    std::cout << e.what() << std::endl;
    return -1;
  }

  return 0;
}