#pragma once
#include <iostream>
using namespace std;

class Dec2Bin {
   public:
    int decNum;
    Dec2Bin() : decNum(0){};
    void readDecNum();
    void dec2bin_rcv(int d);
    void dec2bin_itr();
};