#include "RAM.hpp"


RAM::RAM() {
  for (int i = 0; i < 32; i++) {
    values[i] = 0;
  }
}

int RAM::get_value(int address) {
  if (!(address < 0 || address >= 32)) {
    return values[address];
  }
  return 0;
}

void RAM::set_value(int address, int value) {
  if (!(address < 0 || address >= 32)) {
    this->values[address] = value;
  }
}

void RAM::print(string& instruction) {
  writeRamToFile(instruction, values);
}