#pragma once

#include <cstdint>
#include <string>

namespace pc_club {
enum class ID { _1, _2, _3, _4, _11, _12, _13 };
using Comp_desks_num = uint16_t;
using Hourly_rate = uint16_t;
using Client_name = std::string;

struct Time {

  uint8_t hours;
  uint8_t minutes;

  friend std::ostream &operator<<(std::ostream &os, const Time &time);
  friend bool operator>=(const Time &first, const Time &second);
};

struct Notice {
  Time time;
  ID id;
  Client_name client_name;
  Comp_desks_num num_of_desk = 0;
};

struct Client {
  Time start_time;
  Time end_time;
  Comp_desks_num table_number = 0;
  bool isFree = true;
};

inline std::ostream &operator<<(std::ostream &os, const Time &time) {
  std::string hours = (time.hours < 10 ? "0" : "") + std::to_string(time.hours);
  std::string minutes =
      (time.minutes < 10 ? "0" : "") + std::to_string(time.minutes);
  os << hours + ':' + minutes;
  return os;
}

inline bool operator>=(const Time &first, const Time &second) {
  if (first.hours > second.hours)
    return true;
  if (first.hours == second.hours && first.minutes >= second.minutes)
    return true;
  return false;
}

inline std::string to_string(ID id) {
  switch (id) {
  case ID::_1:
    return "_1";
  case ID::_2:
    return "_2";
  case ID::_3:
    return "_3";
  case ID::_4:
    return "_4";
  case ID::_11:
    return "_11";
  case ID::_12:
    return "_12";
  case ID::_13:
    return "_13";
  default:
    return "unknown";
  }
}

} // namespace pc_club