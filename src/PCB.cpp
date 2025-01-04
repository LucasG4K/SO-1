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
  this->quantum=10;
}

vector<string> PCB::get_instruction() {return this->instructions;}
int PCB::get_id() {return this->id;}
int PCB::get_quantum() {return this->quantum;}
string PCB::get_state() {return this->state;}

void PCB::block_process(int time){
    this->timeSpent+=time;
    this->state="blocked";
}

void PCB::start_process(){
    this->state="executing";
}

void PCB::finish_process(){
    this->state="finished";
}