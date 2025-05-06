#include "Data.hpp"

bool pc_club::Data::isBusyDesk(Comp_desks_num num_of_desk) const {
  return desks_busy[num_of_desk - 1];
}

bool pc_club::Data::isAllDesksBusy(void) const { 
  for (const auto isBusy : desks_busy) {
    if (isBusy == false) return false;
  }
  return true;
}

bool pc_club::Data::isOpenClub(Time time) const {
  if ((time.hours > start_of_work.hours ||
       (time.hours == start_of_work.hours &&
        time.minutes >= start_of_work.minutes)) &&
      (time.hours < end_of_work.hours ||
       (time.hours == end_of_work.hours &&
        time.minutes <= end_of_work.minutes))) {
    return true;
  }
  return false;
}

bool pc_club::Data::isClientPresent(const Client_name &_client) const {
  return clients.contains(_client);
}

bool pc_club::Data::isFreeClient(const Client_name &_client) {
  return clients[_client].isFree;
}

void pc_club::Data::addNewClient(const Client_name &_client) {
  clients.emplace(_client, Client());
}

void pc_club::Data::removeClient(const Client_name &_client) {
  clients.erase(_client);
}

void pc_club::Data::setDesksNum(size_t size) {
  desks_busy.resize(size, false); // false - desk is not busy by default
  paid_desks.resize(size, 0);
  minutes_of_busy_desks.resize(size, 0);
}

void pc_club::Data::setWorkingTime(const Time &start_time,
                                   const Time &end_time) {
  start_of_work.hours = start_time.hours;
  start_of_work.minutes = start_time.minutes;

  end_of_work.hours = end_time.hours;
  end_of_work.minutes = end_time.minutes;

  setPreviosTime({0, 0});
}

void pc_club::Data::setHourlyRate(const Hourly_rate hr) { hourly_rate = hr; }

void pc_club::Data::setPreviosTime(const Time &time) {
  previos_time.hours = time.hours;
  previos_time.minutes = time.minutes;
}

pc_club::Time pc_club::Data::getPreviosTime(void) const { return previos_time; }

uint16_t pc_club::Data::getCountOfDesks(void) const {
  return desks_busy.size();
}

std::unordered_map<std::string, pc_club::Client> &pc_club::Data::getClients(void) {
  return clients;
}

void pc_club::Data::occupyDesk(const Client_name& name, const Time& time, Comp_desks_num num_of_desk) {
  clients[name].isFree = false;
  clients[name].start_time = time;
  clients[name].table_number = num_of_desk;

  desks_busy[num_of_desk - 1] = true;
}

void pc_club::Data::updateTable(const Client_name& name, const Time& time, Comp_desks_num num_of_desk) {
  clients[name].start_time = time;
  clients[name].table_number = num_of_desk;
}

void pc_club::Data::freeDesk(Comp_desks_num num_of_desk) {
  desks_busy[num_of_desk - 1] = false;
}

uint16_t pc_club::Data::getQueueSize(void) const {
  return queue.size();
}

void pc_club::Data::addToQueue(const std::string &client_name) {
  queue.push(client_name);
}

void pc_club::Data::popQueue(const Time& time, Comp_desks_num num_of_desk) {
  clients[queue.front()].start_time = time;
  clients[queue.front()].table_number = num_of_desk;
  clients[queue.front()].isFree = false;

  queue.pop();
}

void pc_club::Data::payUp(const Client_name& name, const Time& time) {
  Client& client = clients[name];

  uint16_t total_start_minutes = client.start_time.hours * 60 + client.start_time.minutes;
  uint16_t total_end_minutes = time.hours * 60 + time.minutes;

  uint8_t num_of_hours = std::ceil((total_end_minutes - total_start_minutes) / 60.0);
  paid_desks[client.table_number - 1] = num_of_hours * hourly_rate;

  minutes_of_busy_desks[client.table_number - 1] += total_end_minutes - total_start_minutes;
}
