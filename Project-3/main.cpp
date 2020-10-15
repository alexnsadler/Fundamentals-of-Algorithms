#include <iostream>
#include "ArrayStack.hpp"
#include "Dec2Bin.hpp"
#include "StackInterface.hpp"
using namespace std;

const int MAX_FIB_IDX = 50;
int fibArray[MAX_FIB_IDX];

int fibSeq(int n) {
    if (n <= 1)
        return n;
    else
        return fibSeq(n - 1) + fibSeq(n - 2);
}

int fibSeqDynamic(int n) {
    if (n <= 1) fibArray[n] = n;
    if (fibArray[n] != -1)
        return fibArray[n];
    else
        fibArray[n] = fibSeq(n - 1) + fibSeq(n - 2);
    return fibArray[n];
}


int main() {
    // Problem 1
    Dec2Bin dec2bin;
    dec2bin.readDecNum();
    dec2bin.dec2bin_rcv(dec2bin.decNum);
    dec2bin.dec2bin_itr();

    // Problem 3 initialization
    for (int i = 0; i < MAX_FIB_IDX; i++) {
        fibArray[i] = -1;
    }

    // Problem 3 output
    int fibEg[5] = {5, 10, 20, 30, 40};
    for (int i = 0; i < 5; i++) {
        cout << "Fibonacci number " << i << " from initial implementation: "
             << fibSeq(fibEg[i]) << endl;
        cout << "Fibonacci number " << i << " from dynamic implementation: "
             << fibSeqDynamic(fibEg[i]) << endl;
        cout << endl;
    }

    return 0;
}
