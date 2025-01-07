#include "SO.hpp"

void writeRamToFile(string& instruction, pair<int,pthread_mutex_t>* ram) {
  ofstream outFile("output/ram.txt", ios::out);

  if (outFile.is_open()) {
    outFile << instruction << '\n';

    for (int i = 0; i < 32; i++) outFile << "0x" << i << " " << ram[i].first << '\n';

    outFile << '\n' << '\n';
    outFile.close();
  } else {
    cout << "Unable to open file: ram.txt" << '\n';
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

vector<PCB*> getFilaProcessos(){
  vector<PCB*> filaProcessos;
  string folderPath = "./dataset"; 
  try {
    for (const auto& entry : filesystem::directory_iterator(folderPath)) {
      if (entry.is_regular_file()) {
        PCB temp = PCB(entry.path().filename());
        filaProcessos.push_back(&temp);
      }
    }
  } catch (const filesystem::filesystem_error& e) {
    cerr << "Erro ao acessar pasta folder: " << e.what() << '\n';
  }
  return filaProcessos;
}

void Success(string print){cout<<"Sucesso thread "<<pthread_self()<<": "<<print<<'\n';}
void Checkpoint(string print){cout<<"Checkpoint thread "<<pthread_self()<<": "<<print<<'\n';}
void Error(string print){cout<<"Erro thread "<<pthread_self()<<": "<<print<<'\n';}