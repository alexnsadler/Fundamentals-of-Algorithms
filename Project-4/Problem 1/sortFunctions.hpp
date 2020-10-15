#pragma once

// global variables
extern int moves;
extern int comps;

// helper functions
int *copyArray(int theArray[], int n);
bool isSorted(int theArray[], int n);

// sort functions
// Selection Sort
int findIndexOfLargest(int theArray[], int n);
void selectionSort(int theArray[], int n);

// Bubble Sort
void bubbleSort(int theArray[], int n);

// Insertion Sort
void insertionSort(int theArray[], int n);

// Merge Sort
void merge(int theArray[], int first, int mid, int last);
void mergeSort(int theArray[], int first, int last);

// Quick Sort
void order(int theArray[], int i, int j);
int sortFirstMiddleLast(int theArray[], int first, int last);
int partition(int theArray[], int first, int last);
void quickSort(int theArray[], int first, int last);

// Heap Sort
void heapRebuild(int theArray[], int rootIdx, int itemCount);
void heapCreate(int theArray[], int itemCount);
void heapSort(int theArray[], int itemCount);