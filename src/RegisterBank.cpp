#include "RegisterBank.hpp"

RegisterBank::RegisterBank() { this->registers.resize(RegisterBankSize); }

int RegisterBank::get_value(int address) {
  return this->registers[address].value;
}

void RegisterBank::set_value(int address, int value) {
  this->registers[address].value = value;
}

void RegisterBank::set_dirty(int address) {
  this->registers[address].dirty = true;
}

void RegisterBank::set_clean(int address) {
  this->registers[address].dirty = false;
}

vector<Register> RegisterBank::get_registers() {
  return this->registers;
}

void RegisterBank::set_registers(vector<int> registers) {
  this->registers.clear();
  this->registers.resize(RegisterBankSize);
  for (int i = 0; i < registers.size()-1; i++)
  {
    this->registers[i].value = registers[i];
  }
}

void RegisterBank::print() {

  for (int i = 0; i < this->registers.size(); i++) {
    cout << "0x" << i << " " << this->get_value(i) << '\n';
  }

}