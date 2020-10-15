// Alex Sadler - 001792279
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include "sortFunctions.hpp"
using namespace std;

// global variables
int moves;
int comps;


int main() {
    
    // open output file
    ofstream outf;
    outf.open("sort.txt"); 
    if (outf.fail()) {
        cerr << "Error: Could not open output file\n";
        exit(1); }
    

    // set seed for srand
    srand(time(NULL));

    // initialize arrays
    const int arrayLen = 1000;
    int BST[arrayLen];
    int AVG[arrayLen];
    int WST[arrayLen];
    for(int i=0; i<arrayLen; i++){
        BST[i] = (i+1) * 10;
        AVG[i] = rand() % 100000;
        WST[i] = (arrayLen - i) * 10;
    }   

    // pointers for copies of initial arrays
    int *tBST; int *tAVG; int *tWST;


    // Selection Sort
    moves = 0; comps = 0; // initialize moves and comps to 0
    tBST = copyArray(BST, arrayLen);
    selectionSort(tBST, arrayLen);
    outf << "Selection Best: " << isSorted(tBST, arrayLen) << ", " << moves << ", " << comps << endl;

    moves = 0; comps = 0; // initialize moves and comps to 0
    tAVG = copyArray(AVG, arrayLen); 
    selectionSort(tAVG, arrayLen);
    outf << "Selection Average: " << isSorted(tAVG, arrayLen) << ", " << moves << ", " << comps << endl;
    
    moves = 0; comps = 0; // initialize moves and comps to 0
    tWST = copyArray(WST, arrayLen);
    selectionSort(tWST, arrayLen);
    outf << "Selection Worst: " << isSorted(tWST, arrayLen) << ", " << moves << ", " << comps << endl;
    
    delete[] tBST; delete[] tAVG; delete[] tWST;


    // Bubble Sort
    moves = 0; comps = 0; // initialize moves and comps to 0    
    tBST = copyArray(BST, arrayLen);
    bubbleSort(tBST, arrayLen);
    outf << "Bubble Best: " << isSorted(tBST, arrayLen) << ", " << moves << ", " << comps << endl;

    moves = 0; comps = 0; // initialize moves and comps to 0
    tAVG = copyArray(AVG, arrayLen); 
    bubbleSort(tAVG, arrayLen);
    outf << "Bubble Average: " << isSorted(tAVG, arrayLen) << ", " << moves << ", " << comps << endl;
    
    moves = 0; comps = 0; // initialize moves and comps to 0
    tWST = copyArray(WST, arrayLen);
    bubbleSort(tWST, arrayLen);
    outf << "Bubble Worst: " << isSorted(tWST, arrayLen) << ", " << moves << ", " << comps << endl;
    
    delete[] tBST; delete[] tAVG; delete[] tWST;
    

    // Insertion Sort
    moves = 0; comps = 0; // initialize moves and comps to 0
    tBST = copyArray(BST, arrayLen);
    insertionSort(tBST, arrayLen);
    outf << "Insertion Best: " << isSorted(tBST, arrayLen) << ", " << moves << ", " << comps << endl;

    moves = 0; comps = 0; // initialize moves and comps to 0
    tAVG = copyArray(AVG, arrayLen); 
    insertionSort(tAVG, arrayLen);
    outf << "Insertion Average: " << isSorted(tAVG, arrayLen) << ", " << moves << ", " << comps << endl;
    
    moves = 0; comps = 0; // initialize moves and comps to 0
    tWST = copyArray(WST, arrayLen);
    insertionSort(tWST, arrayLen);
    outf << "Insertion Worst: " << isSorted(tWST, arrayLen) << ", " << moves << ", " << comps << endl;
    
    delete[] tBST; delete[] tAVG; delete[] tWST;
    
    
    // Merge Sort
    moves = 0; comps = 0; // initialize moves and comps to 0
    tBST = copyArray(BST, arrayLen);
    mergeSort(tBST, 0, arrayLen);
    outf << "Merge Best: " << isSorted(tBST, arrayLen) << ", " << moves << ", " << comps << endl;

    moves = 0; comps = 0; // initialize moves and comps to 0
    tAVG = copyArray(AVG, arrayLen); 
    mergeSort(tAVG, 0, arrayLen);
    outf << "Merge Average: " << isSorted(tAVG, arrayLen) << ", " << moves << ", " << comps << endl;
    
    moves = 0; comps = 0; // initialize moves and comps to 0
    tWST = copyArray(WST, arrayLen);
    mergeSort(tWST, 0, arrayLen);
    outf << "Merge Worst: " << isSorted(tWST, arrayLen) << ", " << moves << ", " << comps << endl;
    
    delete[] tBST; delete[] tAVG; delete[] tWST;


    // Quick Sort
    moves = 0; comps = 0; // initialize moves and comps to 0
    tBST = copyArray(BST, arrayLen);
    quickSort(tBST, 0, arrayLen);
    outf << "Quick Best: " << isSorted(tBST, arrayLen) << ", " << moves << ", " << comps << endl;

    moves = 0; comps = 0; // initialize moves and comps to 0
    tAVG = copyArray(AVG, arrayLen); 
    quickSort(tAVG, 0, arrayLen);
    outf << "Quick Average: " << isSorted(tAVG, arrayLen) << ", " << moves << ", " << comps << endl;
    
    moves = 0; comps = 0; // initialize moves and comps to 0
    tWST = copyArray(WST, arrayLen);
    quickSort(tWST, 0, arrayLen);
    outf << "Quick Worst: " << isSorted(tWST, arrayLen) << ", " << moves << ", " << comps << endl;
    
    delete[] tBST; delete[] tAVG; delete[] tWST;


    // Heap Sort
    moves = 0; comps = 0; // initialize moves and comps to 0
    tBST = copyArray(BST, arrayLen);
    heapSort(tBST, arrayLen);
    outf << "Heap Best: " << isSorted(tBST, arrayLen) << ", " << moves << ", " << comps << endl;

    moves = 0; comps = 0; // initialize moves and comps to 0
    tAVG = copyArray(AVG, arrayLen); 
    heapSort(tAVG, arrayLen);
    outf << "Heap Average: " << isSorted(tAVG, arrayLen) << ", " << moves << ", " << comps << endl;
    
    moves = 0; comps = 0; // initialize moves and comps to 0
    tWST = copyArray(WST, arrayLen);
    heapSort(tWST, arrayLen);
    outf << "Heap Worst: " << isSorted(tWST, arrayLen) << ", " << moves << ", " << comps << endl;
    
    delete[] tBST; delete[] tAVG; delete[] tWST;


    outf.close(); //Close the file at the end of your program.
}