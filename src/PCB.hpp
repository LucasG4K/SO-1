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

    // Registradores e memorias usadas
    vector<int> registers;
    vector<int> memoryUsage;

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
    string get_name();

    // Espaço da RAM para ser guardado quando bloqueia
    void set_ram(int ramStorage);
    int get_ram();

    // Mudar estado do processo
    void block_process(int time);
    void return_state(string state);
    void unblock_process();
    void start_process();
    void finish_process();

    // Memoria e registradores
    void set_registers(vector<int> registers);
    vector<int> get_registers();
    void add_memory(int registers);
    vector<int> get_memoryUsage();


};

#endif