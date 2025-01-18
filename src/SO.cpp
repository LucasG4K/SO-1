#include "SO.hpp"

void writeRamToFile(string& instruction, pair<int,pthread_mutex_t*>* ram) {
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
  string folderPath = "dataset"; 
  try {
    for (const auto& entry : filesystem::directory_iterator(folderPath)) {
      if (entry.is_regular_file()) {
        PCB* temp = new PCB(entry.path().filename());
        filaProcessos.push_back(temp);
      }
    }
  } catch (const filesystem::filesystem_error& e) {
    cerr << "Erro ao acessar pasta folder: " << e.what() << '\n';
  }
  return filaProcessos;
}
void checkFile(string type,string filePath,string print){
  string dirPath="ThreadsLog";
  if (!filesystem::exists(dirPath)) {
    filesystem::create_directory(dirPath);
  }
  ofstream outFile(dirPath+"/"+filePath, std::ios::out | std::ios::app);
  if (!outFile) {
    throw ios_base::failure("Failed to create the file: " + filePath);
  }
  outFile<<type<<" thread "<<filePath<<": "<<print<<'\n';;
  outFile.close();
}
void Success(string print){
  checkFile("Sucesso",to_string(pthread_self()),print);
  cout<<"Sucesso thread "<<pthread_self()<<": "<<print<<'\n';
}
void Checkpoint(string print){
  checkFile("Checkpoint",to_string(pthread_self()),print);
  cout<<"Checkpoint thread "<<pthread_self()<<": "<<print<<'\n';
}
void Error(string print){
  checkFile("Error",to_string(pthread_self()),print);
  cout<<"Erro thread "<<pthread_self()<<": "<<print<<'\n';
}