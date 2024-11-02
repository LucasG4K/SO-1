#ifndef UTILS
#define UTILS

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> read_ROM();
void writeRamToFile(string& instruction, int* ram);
vector<string> split(const string& str);

#endif