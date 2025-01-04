#ifndef _PCB
#define _PCB

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

class PCB {
  private:
    vector<string> instructions;
    int id;
    string name;
    string state;
    int quantum;
    int ramSpace;
    int timeSpent;
  public:
    PCB(string nameFile);
    vector<string> get_instruction();
    int get_id();
    int get_quantum();
    string get_state();
    void block_process(int time);
    void start_process();
    void finish_process();
};

#endif