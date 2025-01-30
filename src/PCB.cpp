#include "PCB.hpp"

PCB::PCB(string nameFile) {
  ifstream codigo("dataset/"+nameFile);
  string temp;
  getline(codigo, temp);
  this->name = temp.substr(temp.find(" - ")+3,temp.size());

  getline(codigo, temp);
  this->id = stoi(temp.substr(temp.find(" - ")+3,temp.size()));

  getline(codigo, temp);
  this->ramSpace = stoi(temp.substr(temp.find(" - ")+3,temp.size()));

  while (getline(codigo, temp)) {
    this->instructions.push_back(temp);
  }

  this->state="ready";
  this->timeSpent=0;
  this->quantum=Quantum;
}

vector<string> PCB::get_instruction() {return this->instructions;}
int PCB::get_id() {return this->id;}
int PCB::get_et() {return this->estimatedTime;}
void PCB::set_et(int et){this->estimatedTime=et;};
int PCB::get_quantum() {return this->quantum;}
void PCB::set_quantum(int quantum) {this->quantum=quantum;};
string PCB::get_state() {return this->state;}
string PCB::get_name() {return this->name;}

void PCB::set_ram(int ramStorage) {this->ramSpace=ramStorage;};
int PCB::get_ram() {return this->ramSpace;}

void PCB::set_registers(vector<int> registers) {this->registers=registers;};
vector<int> PCB::get_registers() {return this->registers;}

void PCB::add_memory(int memory) {this->memoryUsage.push_back(memory);};
vector<int> PCB::get_memoryUsage() {return this->memoryUsage;}

void PCB::block_process(int time) {
    this->timeSpent+=time;
    this->state="blocked";
}

void PCB::return_state(string state) {
    this->state=state;
}

void PCB::unblock_process() {
    this->state="executing";
}

void PCB::start_process() {
  this->startTime = chrono::system_clock::now();
  this->state="executing";
}

void PCB::finish_process() {
  this->endTime = chrono::system_clock::now();
  this->state="finished";
}