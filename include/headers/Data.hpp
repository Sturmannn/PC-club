#pragma once

#include "types.hpp"
#include <unordered_map>
#include <vector>
#include <queue>
#include <cmath>

namespace pc_club {

class Data {
public:
  bool isBusyDesk(Comp_desks_num num_of_desk) const;
  bool isAllDesksBusy(void) const;
  bool isOpenClub(Time time) const;
  bool isClientPresent(const Client_name &_client) const;
  bool isFreeClient(const Client_name &_client);
  void addNewClient(const Client_name &_client);
  void removeClient(const Client_name &_client);

  void setDesksNum(size_t size);
  void setWorkingTime(const Time &start_time, const Time &end_time);
  void setHourlyRate(const Hourly_rate hr);

  void setPreviosTime(const Time &time);
  Time getPreviosTime(void) const;

  uint16_t getCountOfDesks(void) const;
  std::unordered_map<std::string, Client> &getClients(void);

  void occupyDesk(const Client_name& name, const Time& time, Comp_desks_num num_of_desk);
  void updateTable(const Client_name& name, const Time& time, Comp_desks_num num_of_desk);
  void freeDesk(Comp_desks_num num_of_desk);

  uint16_t getQueueSize(void) const;
  void addToQueue(const std::string& client_name);
  void popQueue(const Time& time, Comp_desks_num num_of_desk);

  void payUp(const Client_name& name, const Time& time);

private:
  Time start_of_work;
  Time end_of_work;
  Hourly_rate hourly_rate;
  std::vector<bool> desks_busy;
  std::vector<Hourly_rate> paid_desks;
  std::vector<uint16_t> minutes_of_busy_desks;
  // std::unordered_set<Client> clients;
  std::unordered_map<std::string, Client> clients;
  std::queue<std::string> queue;

  Time previos_time;
};

} // namespace pc_club