#include "PCB.hpp"

PCB::PCB(string nameFile){
  ifstream codigo("./dataset/"+nameFile+".txt");
  string temp;
  getline(codigo, temp);
  this->name = temp.substr(temp.find(" - "),temp.size());

  getline(codigo, temp);
  this->id = stoi(temp.substr(temp.find(" - "),temp.size()));

  getline(codigo, temp);
  this->ramSpace = stoi(temp.substr(temp.find(" - "),temp.size()));

  while (getline(codigo, temp)) {
    this->instructions.push_back(temp);
  }

  this->state="ready";
  this->timeSpent=0;
  this->quantum=Quantum;
}

vector<string> PCB::get_instruction() {return this->instructions;}
int PCB::get_id() {return this->id;}
int PCB::get_quantum() {return this->quantum;}
string PCB::get_state() {return this->state;}

void PCB::set_ram(int ramStorage){this->ramSpace=ramStorage;};
int PCB::get_ram() {return this->ramSpace;}

void PCB::set_registers(vector<int> registers){this->registers=registers;};
vector<int> PCB::get_registers() {return this->registers;}

void PCB::add_memory(int memory){this->memoryUsage.push_back(memory);};
vector<int> PCB::get_memoryUsage() {return this->memoryUsage;}

void PCB::block_process(int time){
    this->timeSpent+=time;
    this->state="blocked";
}

void PCB::unblock_process(){
    this->state="executing";
}

void PCB::start_process(){
  this->startTime = chrono::system_clock::now();
  this->state="executing";
}

void PCB::finish_process(){
  this->endTime = chrono::system_clock::now();
  this->state="finished";
}