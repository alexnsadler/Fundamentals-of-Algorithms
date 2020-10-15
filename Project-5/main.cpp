#include <iostream>
using namespace std;

int h1(int key) {
    int x = (key + 5) * (key + 5);
    x = x / 16;
    x = x + key;
    x = x % 11;
    return x;
}

int main() {
    // initialize array
    const int arrayLen = 11;
    int array[arrayLen];
    for (int i = 0; i < arrayLen; i++) {
        array[i] = -1;
    }

    // keys
    int key_vals[12] = {43, 23, 1, 0, 15, 31, 4, 7, 11, 3, 5, 9};


    for (int i = 0; i < arrayLen; i++) {
        cout << "Value to save out: " << key_vals[i] << endl;
        int hashKey = h1(key_vals[i]) % 11;
        cout << "Init hash key: " << hashKey << endl;;
        
        int probIdx = 1;
        while (array[hashKey] != -1) {
            hashKey = (h1(key_vals[i]) + probIdx) % 11;
            cout << "Next attempt: " << hashKey << endl;
            probIdx++;
        }

        array[hashKey] = key_vals[i];
        cout << endl;
    }


    
    cout << endl;
    cout << h1(9) << " " << h1(23) << " " << h1(1) << endl;;
    return 0;
}