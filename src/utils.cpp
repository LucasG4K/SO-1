#include "utils.hpp"

vector<string> read_ROM(string nameFile) {
}

void writeRamToFile(string& instruction, pair<int,bool>* ram) {
  ofstream outFile("output/ram.txt", ios::out);

  if (outFile.is_open()) {
    outFile << instruction << endl;

    for (int i = 0; i < 32; i++) outFile << "0x" << i << " " << ram[i].first << " " << ram[i].second << endl;

    outFile << endl << endl;
    outFile.close();
  } else {
    cout << "Unable to open file: ram.txt" << endl;
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