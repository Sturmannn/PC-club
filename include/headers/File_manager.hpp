#pragma once

#include <fstream>
#include <iostream>

namespace pc_club {

class File_manager {
public:

  explicit File_manager(const std::string &file_path);
  bool read_line(std::string &string);

  bool isFileValid(const std::string &file_path);
  std::string &get_last_read_line(void);
  ~File_manager();

  // File_manager(const File_manager &fm) = default;

private:
  std::ifstream ifs;
  std::string last_read_line;
};
} // namespace pc_club
