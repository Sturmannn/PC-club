#pragma once

#include <fstream>
#include <iostream>

namespace pc_club {

class File_manager {
public:
  explicit File_manager(const std::string &file_path);
  File_manager(const File_manager &fm) = delete;
  File_manager(File_manager &&fm) = delete;
  File_manager &operator=(const File_manager &fm) = delete;
  File_manager &operator=(File_manager &&fm) = delete;

  bool read_line(std::string &string);

  bool isFileValid(const std::string &file_path);
  std::string &get_last_read_line(void);

  ~File_manager() = default;

private:
  std::ifstream ifs;
  std::string last_read_line;
};
} // namespace pc_club
