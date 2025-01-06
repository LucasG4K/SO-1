#include "SO.hpp"

vector<string> read_ROM(string nameFile) {
}

void writeRamToFile(string& instruction, pair<int,pthread_mutex_t>* ram) {
  ofstream outFile("output/ram.txt", ios::out);

  if (outFile.is_open()) {
    outFile << instruction << endl;

    for (int i = 0; i < 32; i++) outFile << "0x" << i << " " << ram[i].first << endl;

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
    cerr << "Erro ao acessar pasta folder: " << e.what() << endl;
  }
  return filaProcessos;
}

void Success(string print){cout<<"Sucesso thread "<<pthread_self()<<": "<<print<<endl;}
void Checkpoint(string print){cout<<"Checkpoint thread "<<pthread_self()<<": "<<print<<endl;}
void Error(string print){cout<<"Erro thread "<<pthread_self()<<": "<<print<<endl;}