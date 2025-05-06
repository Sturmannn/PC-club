#pragma once

#include "types.hpp"
#include <cmath>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

namespace pc_club {

class Data {
public:
  Data() = default;
  Data(const Data &) = delete;
  Data(Data &&) = delete;
  Data &operator=(const Data &) = delete;
  Data &operator=(Data &&) = delete;

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
  std::vector<std::string> getAlphabetClients(void);

  void occupyDesk(const Client_name &name, const Time &time,
                  Comp_desks_num num_of_desk);
  void updateTable(const Client_name &name, const Time &time,
                   Comp_desks_num num_of_desk);
  void freeDesk(const Client_name &name);
  uint16_t getFreeDesk(void);
  uint16_t getClientDesk(const Client_name &name) const;

  uint16_t getQueueSize(void) const;
  void addToQueue(const std::string &client_name);
  Client_name popQueue(const Time &time);

  void payUp(const Client_name &name, const Time &time);

  Time getClosingTime(void) const;
  void getTableProceed(Comp_desks_num num_of_desk, Hourly_rate &hr,
                       Time &time) const;

  ~Data() = default;

private:
  Time start_of_work;
  Time end_of_work;
  Time previos_time;
  Hourly_rate hourly_rate;
  std::vector<bool> desks_busy;
  std::vector<Hourly_rate> paid_desks;
  std::vector<uint16_t> minutes_of_busy_desks;
  std::unordered_map<std::string, Client> clients;
  std::queue<std::string> queue;
};

} // namespace pc_club