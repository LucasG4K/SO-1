#ifndef _RAM
#define _RAM

#include <bits/stdc++.h>

using namespace std;

class RAM {
    private:
    int values[32];

    public:
    int get_value(int address) {
        return values[address];
    }
    void set_value(int address, int value) {
        this->values[address] = value;
    }
    void print() {
        for (int i = 0; i < 32; i++) {
            cout << "RAM " << i << " " << this->values[i] << endl;
        }
        cout << endl; 
    }
};

#endif