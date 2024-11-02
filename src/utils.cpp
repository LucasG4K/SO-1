#include "utils.hpp"

vector<string> read_ROM() {
  ifstream codigo("./dataset/codigo.txt");
  vector<string> retorno;
  string temp;
  while (getline(codigo, temp)) {
    retorno.push_back(temp);
  }
  return retorno;
}

void writeRamToFile(string& instruction, int* ram) {
  ofstream outFile("output/ram.txt", ios::out);

  if (outFile.is_open()) {
    outFile << instruction << endl;

    for (int i = 0; i < 32; i++) outFile << "0x" << i << " " << ram[i] << endl;

    outFile << endl << endl;
    outFile.close();
  } else {
    cout << "Unable to open file: ram.txt" << std::endl;
  }
}

vector<string> split(const string &str) {
  vector<string> result;
  istringstream iss(str);
  string word;

  while (iss >> word) {
    result.push_back(word);
  }

  while (result.size() < 4) {
    result.push_back("!");
  }

  return result;
}