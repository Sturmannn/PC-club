#include "File_manager.hpp"

pc_club::File_manager::File_manager(const std::string &file_path) {
  if (!isFileValid(file_path)) {
    throw std::runtime_error("File error: " + file_path);
  }
}

bool pc_club::File_manager::read_line(std::string &string) {
  std::getline(ifs, string);
  if (ifs.good()) {
    last_read_line = string;
    return true;
  }
  return false;
}

bool pc_club::File_manager::isFileValid(const std::string &file_path) {
  ifs.open(file_path);
  if (!ifs.good()) {
    return false;
  }
  return true;
}

std::string &pc_club::File_manager::get_last_read_line(void) {
  return last_read_line;
}
