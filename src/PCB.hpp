#ifndef _PCB
#define _PCB

#define Quantum 250

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

class PCB {
  private:
    vector<string> instructions;
    int id;
    string name;
    string state;
    int quantum;
    int ramSpace;
    int pipelineStage;

    // Control
    chrono::_V2::system_clock::time_point startTime;
    chrono::_V2::system_clock::time_point endTime;
    int timeSpent;
  public:
    PCB(string nameFile);
    vector<string> get_instruction();
    int get_id();
    int get_quantum();
    string get_state();

    // Espaço da RAM para ser guardado quando bloqueia
    void set_ram(int ramStorage);
    int get_ram();

    // Mudar estado do processo
    void block_process(int time);
    void unblock_process();
    void start_process();
    void finish_process();

    // Fase de pipeline
    void set_pipelineStage(int stage);
    int get_pipelineStage();

};

#endif