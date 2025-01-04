#include "RAM.hpp"


RAM::RAM() {
  for (int j = 0; j < RamSize; j++){
    this->ram[j].first = 0;
    this->ram[j].second=false;
  }
}

int RAM::Read(int address) {
  if (!(address < 0 || address >= 32)) {
    return ram[address].first;
  }
  return 0;
}

void RAM::Write_Update(int address, int value) {
  if (!(address < 0 || address >= 32) && !this->ram[address].second) {
    this->ram[address].first = value;
    this->ram[address].second=true;
  }
  else{
    throw exception();
  }
}

void RAM::Delete(int address) {
  if (!(address < 0 || address >= 32)) {
    this->ram[address].first = 0;
    this->ram[address].second=false;
  }
}

void RAM::print(string& instruction) {
  writeRamToFile(instruction, ram);
}