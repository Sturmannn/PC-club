#include "Handler.hpp"

pc_club::Handler::Handler(const std::string file_path) : fm{file_path} {}

void pc_club::Handler::handle_file(void) {
  std::string read_string;

  // Handling the first input line
  if (fm.read_line(read_string)) {
    if (!isDigit(read_string)) {
      std::cout << read_string << std::endl;
      return;
    }
    pc_db.setDesksNum(std::stoul(read_string));
  } else {
    return;
  }

  // Handling the second input line
  if (fm.read_line(read_string)) {

    // if (!isTime(read_string)) {
    //   std::cout << read_string << std::endl;
    //   return;
    // }
    std::vector<std::string> tokens = split(read_string, " ");
    if (tokens.size() != 2 || !isTime(tokens[0]) || !isTime(tokens[1])) {
      std::cout << read_string << std::endl;
      return;
    }
    pc_db.setWorkingTime(getTime(tokens[0]), getTime(tokens[1]));
    std::cout << tokens[0] << std::endl;
  } else {
    return;
  }

  // Handling the third input line
  if (fm.read_line(read_string)) {
    if (!isDigit(read_string)) {
      std::cout << read_string << std::endl;
      return;
    }
    pc_db.setHourlyRate(std::stoul(read_string));
  } else {
    return;
  }

  // Handling the remaining input lines
  while (fm.read_line(read_string)) {
    if (!isNotice(read_string)) {
      std::cout << read_string << std::endl;
      return;
    }
    Notice notice = getNotice(read_string);
    switch (notice.id) {
    case ID::_1:
      if(!Handle_ID_1(notice)) return;
      break;
    case ID::_2:
      if(!Handle_ID_2(notice)) return;
      break;
    case ID::_3:
      if(!Handle_ID_3(notice)) return;
      break;
    case ID::_4:
      if(!Handle_ID_4(notice)) return;
      break;
    default:
      break;
    }
    // if (!(notice.time <= pc_db.getPreviosTime())) {
    //   std::cout << read_string << std::endl;
    //   return;
    // }
  }
}

bool pc_club::Handler::isDigit(const std::string &string) const {
  size_t pos = 0;
  try {
    std::stoul(string, &pos);
  } catch (...) {
    return false;
  }
  if (string.size() == pos)
    return true;
  return false;
}

bool pc_club::Handler::isHours(const std::string &string) const {
  try {
    size_t hours = std::stoul(string);
    if (hours < 24 && string.size() == 2)
      return true;
    return false;
  } catch (...) {
    return false;
  }
}

bool pc_club::Handler::isMinutes(const std::string &string) const {
  try {
    size_t minutes = std::stoul(string);
    if (minutes < 60 && string.size() == 2)
      return true;
    return false;
  } catch (...) {
    return false;
  }
}

bool pc_club::Handler::isTime(const std::string &string) const {
  std::vector<std::string> tokens = split(string, ":");
  if (tokens.size() != 2)
    return false;
  if (!isHours(tokens[0]) || !isMinutes(tokens[1]))
    return false;
  return true;
}

pc_club::Time pc_club::Handler::getTime(const std::string &string) const {
  uint8_t hours = 0;
  uint8_t minutes = 0;

  std::vector<std::string> tokens = split(string, ":");
  hours = std::stoul(tokens[0]);
  minutes = std::stoul(tokens[1]);

  return {hours, minutes};
}

bool pc_club::Handler::isID(const std::string &string) const {
  std::vector<std::string> IDs = {"_1", "_2", "_3", "_4", "_11", "_12", "_13"};
  for (const auto &ID : IDs) {
    if ("_" + string == ID)
      return true;
  }
  return false;
}

pc_club::ID pc_club::Handler::getID(const std::string &string) const {
  std::vector<ID> IDs = {ID::_1,  ID::_2,  ID::_3, ID::_4,
                         ID::_11, ID::_12, ID::_13};
  for (const auto &ID : IDs) {
    if ("_" + string == pc_club::to_string(ID))
      return ID;
  }
  throw std::invalid_argument("Unknown ID string: " + string);
}

bool pc_club::Handler::isName(const std::string &string) const {
  char a = 'a';
  char z = 'z';

  char _0 = '0';
  char _9 = '9';

  char _ = '_';
  char line = '-';

  for (const auto &sym : string) {
    if (!((sym >= a && sym <= z) || (sym >= _0 && sym <= _9) || sym == _ ||
          sym == line))
      return false;
  }
  return true;
}

bool pc_club::Handler::isNumOfDesk(const std::string &string) const {
  if (!isDigit(string))
    return false;
  uint16_t digit = getDigit(string);

  if (digit > pc_db.getCountOfDesks())
    return false;
  return true;
}

uint16_t pc_club::Handler::getDigit(const std::string &string) const {
  return std::stoul(string);
}

bool pc_club::Handler::isNotice(const std::string &string) const {
  std::vector<std::string> tokens = split(string, " ");
  if (tokens.size() != 3 && tokens.size() != 4)
    return false;
  if (!isTime(tokens[0]))
    return false;
  if (!isID(tokens[1]))
    return false;
  if (!isName(tokens[2]))
    return false;

  ID id = getID(tokens[1]);
  if (id == ID::_2) {
    if (tokens.size() == 4 && !isNumOfDesk(tokens[3]))
      return false;
  } else if (id != ID::_2 && tokens.size() != 3)
    return false;

  return true;
}

pc_club::Notice pc_club::Handler::getNotice(const std::string &string) const {
  std::vector<std::string> tokens = split(string, " ");
  if (tokens.size() == 4) {
    return {getTime(tokens[0]), getID(tokens[1]), tokens[2],
            getDigit(tokens[3])};
  }
  return {getTime(tokens[0]), getID(tokens[1]), tokens[2]};
}

std::vector<std::string> pc_club::Handler::split(std::string string,
                                                 std::string del) const {
  std::vector<std::string> tokens;
  size_t start = 0;
  size_t end = string.find(del);
  while (end != std::string::npos) {
    tokens.push_back(string.substr(start, end - start));
    start = end + 1;
    end = string.find(del, start);
  }
  tokens.push_back(string.substr(start));
  return tokens;
}

bool pc_club::Handler::isAppropriateTime(const Time &time) const {
  return time >= pc_db.getPreviosTime();
}

bool pc_club::Handler::Handle_ID_1(const Notice &note) {
  if (!isAppropriateTime(note.time)) {
    std::cout << fm.get_last_read_line();
    return false;
  }

  if (pc_db.isClientPresent(note.client_name)) {
    std::cout << fm.get_last_read_line() << std::endl;
    std::cout << note.time << ' ' << 13 << ' ' << "YouShallNotPass"
              << std::endl;
    return true;
  }
  if (!pc_db.isOpenClub(note.time)) {
    std::cout << fm.get_last_read_line() << std::endl;
    std::cout << note.time << ' ' << 13 << ' ' << "NotOpenYet" << std::endl;
    return true;
  }
  pc_db.addNewClient(note.client_name);
  std::cout << fm.get_last_read_line() << std::endl;
  return true;
}

bool pc_club::Handler::Handle_ID_2(const Notice &note) {
  if (!isAppropriateTime(note.time)) {
    std::cout << fm.get_last_read_line();
    return false;
  }

  if (!pc_db.isClientPresent(note.client_name)) {
    std::cout << fm.get_last_read_line() << std::endl;
    std::cout << note.time << ' ' << 13 << ' ' << "ClientUnknown" << std::endl;
    return true;
  }

  if (pc_db.isBusyDesk(note.num_of_desk)) {
    std::cout << fm.get_last_read_line() << std::endl;
    std::cout << note.time << ' ' << 13 << ' ' << "PlaceIsBusy" << std::endl;
    return true;
  }

  if (pc_db.isFreeClient(note.client_name)) {
    pc_db.occupyDesk(note.client_name, note.time, note.num_of_desk);
  } else {
    pc_db.payUp(note.client_name, note.time);
    pc_db.updateTable(note.client_name, note.time, note.num_of_desk);
  }

  std::cout << fm.get_last_read_line() << std::endl;
  return true;
}

bool pc_club::Handler::Handle_ID_3(const Notice &note) {
  if (!isAppropriateTime(note.time)) {
    std::cout << fm.get_last_read_line();
    return false;
  }

  if (!pc_db.isAllDesksBusy()) {
    std::cout << fm.get_last_read_line() << std::endl;
    std::cout << note.time << ' ' << 13 << ' ' << "ICanWaitNoLonger!" << std::endl;
    return true;
  }

  if (pc_db.getQueueSize() == pc_db.getCountOfDesks()) {
    std::cout << note.time << ' ' << 11 << ' ' << note.client_name << std::endl;
    pc_db.removeClient(note.client_name);
    return true;
  }

  std::cout << fm.get_last_read_line() << std::endl;
  pc_db.addToQueue(note.client_name);

  return true;
}

bool pc_club::Handler::Handle_ID_4(const Notice &note) {
  if (!isAppropriateTime(note.time)) {
    std::cout << fm.get_last_read_line();
    return false;
  }

  if (!pc_db.isClientPresent(note.client_name)) {
    std::cout << fm.get_last_read_line() << std::endl;
    std::cout << note.time << ' ' << 13 << ' ' << "ClientUnknown" << std::endl;
    return true;
  }

  pc_db.payUp(note.client_name, note.time);
  pc_db.removeClient(note.client_name);
  pc_db.freeDesk(note.num_of_desk);

  pc_db.popQueue(note.time, note.num_of_desk);

  return true;
}
