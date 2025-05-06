#pragma once

#include "File_manager.hpp"
#include "Data.hpp"


namespace pc_club {

class Handler {
public:
  explicit Handler(const std::string file_path);
  
  void handle_file(void);

  bool isDigit(const std::string& string) const;
  bool isHours(const std::string &string) const; 
  bool isMinutes(const std::string &string) const;
  bool isTime(const std::string& string) const;
  Time getTime(const std::string& string) const;

  bool isID(const std::string &string) const;
  ID getID(const std::string &string) const;

  bool isName(const std::string &string) const;
  bool isNumOfDesk(const std::string &string) const;
  uint16_t getDigit(const std::string &string) const;
  
  bool isNotice(const std::string& string) const;
  Notice getNotice(const std::string &string) const;

private:

  
  std::vector<std::string> split(std::string string, std::string del) const;
  bool isAppropriateTime(const Time& time) const;
  bool Handle_ID_1(const Notice &note);
  bool Handle_ID_2(const Notice &note);
  bool Handle_ID_3(const Notice &note);
  bool Handle_ID_4(const Notice &note);

  File_manager fm;
  Data pc_db;
};
}