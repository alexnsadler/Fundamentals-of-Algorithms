#include "sortFunctions.hpp"

#include <iostream>
using namespace std;

// -------------------- Helper Functions ---------------------
int *copyArray(int theArray[], int n) {
    int *copy = new int[n];
    for (int i = 0; i < n; i++) {
        copy[i] = theArray[i];
    }

    return copy;
}

bool isSorted(int theArray[], int n) {
    bool sorted = true;

    // check that each item in theArray is smaller than the next
    for (int i = 0; i < n - 1; i++) {
        if (theArray[i] > theArray[i + 1]) {
            sorted = false;
        }
    }
    return sorted;
}

// -------------------- Selection Sort ------------------------
int findIndexOfLargest(int theArray[], int n) {
    int idxLargest = 0;  // initialize index of largest int to 0

    for (int i = 1; i < n; i++) {
        // check if entry for current index is larger than current largest
        if (theArray[i] > theArray[idxLargest]) {
            idxLargest = i;
        }

        comps++;  // increment comps
    }

    return idxLargest;
}

void selectionSort(int theArray[], int n) {
    for (int i = n - 1; i > 0; i--) {
        // only search array in theArray[0 : i] for largest int
        int largestIdx = findIndexOfLargest(theArray, i + 1);

        // only swap if largest element is not already in place
        if (largestIdx != i) {
            swap(theArray[i], theArray[largestIdx]);
            moves += 3;  // increment moves
        }
    }
}

// -------------------- Bubble Sort ---------------------------
void bubbleSort(int theArray[], int n) {
    bool sorted = false;  // false when swaps occur
    int pass = 1;

    while (!sorted && (pass < n)) {
        // theArray[n+1-pass : n-1] is sorted at this point
        sorted = true;

        // elements in theArray[0:idx-1] are less than theArray[idx]
        for (int idx = 0; idx < n - pass; idx++) {
            int nextIdx = idx + 1;

            // swap entries if next element > current element
            comps++;  // increment comps
            if (theArray[idx] > theArray[nextIdx]) {
                swap(theArray[idx], theArray[nextIdx]);
                moves += 3;      // increment moves
                sorted = false;  // signal swap
            }
        }
        pass++;
    }
}

// -------------------- Insertion Sort ------------------------
void insertionSort(int theArray[], int n) {
    // loop through each item in array
    for (int unsorted = 1; unsorted < n; unsorted++) {
        int nextItem = theArray[unsorted];
        int loc = unsorted;

        comps++;  // increment comps
        while ((loc > 0) && theArray[loc - 1] > nextItem) {
            // shift theArray[loc - 1] to the right
            theArray[loc] = theArray[loc - 1];
            loc--;
            moves++;  // increment moves
            comps++;  // increment comps
        }

        if (loc != unsorted) {  // don't do anything if item is in right place
            theArray[loc] = nextItem;  // insert nextItem into sorted region
            moves++;                   // increment moves
        }
    }
}

// -------------------- Merge Sort ----------------------------
void merge(int theArray[], int first, int mid, int last) {
    int tempArray[last];  // create temporary array

    // initialize local indices
    int first1 = first;    // beginning of first subarray
    int last1 = mid;       // end of first subarray
    int first2 = mid + 1;  // beginning of second subarray
    int last2 = last;      // end of second subarray

    // copy elements from subarrays to temp array until at least one subarray is
    // empty
    int idx = first1;
    while ((first1 <= last1) && (first2 <= last2)) {
        comps++;  // increment comps
        if (theArray[first1] <= theArray[first2]) {
            tempArray[idx] = theArray[first1];
            first1++;
        } else {
            tempArray[idx] = theArray[first2];
            first2++;
        }
        idx++;
        moves++;  // incremement moves
    }

    // copy the rest of elements from first subarray, if necessary
    while (first1 <= last1) {
        tempArray[idx] = theArray[first1];
        first1++;
        idx++;
        moves++;  // incremement moves
    }

    // copy the rest of elements from second subarray, if necessary
    while (first2 <= last2) {
        tempArray[idx] = theArray[first2];
        first2++;
        idx++;
        moves++;  // incremement moves
    }

    // copy results back into the original array
    for (idx = first; idx <= last; idx++) {
        theArray[idx] = tempArray[idx];
        moves++;
    }
}

void mergeSort(int theArray[], int first, int last) {
    // check if there are elements to sort for given array
    if (first < last) {
        int mid = (first + last) / 2;  // midpoint

        mergeSort(theArray, first, mid);     // sort left half of array
        mergeSort(theArray, mid + 1, last);  // sort right half of array
        merge(theArray, first, mid, last);   // merge two halves
    }
}

// -------------------- Quick Sort ----------------------------
void order(int theArray[], int i, int j) {
    comps++;  // increment comps
    if (theArray[i] > theArray[j]) {
        swap(theArray[i], theArray[j]);
        moves += 3;  // incremement moves
    }
}

int sortFirstMiddleLast(int theArray[], int first, int last) {
    int mid = (first + last) / 2;
    order(theArray, first, mid);
    order(theArray, mid, last);
    order(theArray, first, mid);

    return mid;
}

int partition(int theArray[], int first, int last) {
    // choose pivot and reposition to last-1 in array
    int pivotIdx = sortFirstMiddleLast(theArray, first, last);
    swap(theArray[pivotIdx], theArray[last - 1]);
    moves += 3;  // increment moves
    pivotIdx = last - 1;
    int pivot = theArray[pivotIdx];

    // indices of s1 and s2 to start searching
    int idxFromLeft = first + 1;
    int idxFromRight = last - 2;
    bool done = false;

    while (!done) {
        // locate first entry on left that is >= pivot
        while (theArray[idxFromLeft] < pivot) {
            idxFromLeft++;
            comps++;  // incremement comps
        }

        // locate first entry on right that is <= pivot
        while (theArray[idxFromRight] > pivot) {
            idxFromRight--;
            comps++;  // incremement comps
        }

        if (idxFromLeft < idxFromRight) {
            swap(theArray[idxFromLeft], theArray[idxFromRight]);
            idxFromLeft++;
            idxFromRight--;
            moves += 3;  // incremement moves
        } else
            done = true;
    }

    // place pivot in proper position between s1 and s2
    moves += 3;  // incremement moves
    swap(theArray[pivotIdx], theArray[idxFromLeft]);
    pivotIdx = idxFromLeft;

    return pivotIdx;
}

void quickSort(int theArray[], int first, int last) {
    int sz = last - first + 1;

    if (sz < 5) {
        insertionSort(theArray + first, sz);
    } else {
        // create partition: s1 | pivot | s2
        int pivotIdx = partition(theArray, first, last);

        // sort subarrays s1 and s2
        quickSort(theArray, first, pivotIdx - 1);
        quickSort(theArray, pivotIdx + 1, last);
    }
}

// -------------------- Heap Sort ----------------------------
void heapRebuild(int theArray[], int rootIdx, int itemCount) {
    // Recursively trickle the item at index root down to its proper position by
    // swapping it with its larger child, if the child is larger than the item.
    if (rootIdx <= itemCount / 2 - 1) {
        int largerChildIdx = 2 * rootIdx + 1;

        // check if there is a right child and if it is larger than the left
        // child
        if (2 * rootIdx + 2 < itemCount) {
            int rightChildIdx = 2 * rootIdx + 2;
            comps++; // incremement comps
            if (theArray[rightChildIdx] > theArray[largerChildIdx]) {
                largerChildIdx = rightChildIdx;
            }
        }
        // if the root is smaller than the larger child, swap items
        comps++; // incremement comps
        if (theArray[rootIdx] < theArray[largerChildIdx]) {
            swap(theArray[rootIdx], theArray[largerChildIdx]);
            moves+=3; // incremement moves
            heapRebuild(theArray, largerChildIdx, itemCount);
        }
    }
}

void heapCreate(int theArray[], int itemCount) {
    // Rebuild the heap starting from the last non-leaf node
    for (int idx = (itemCount / 2) - 1; idx >= 0; idx--) {
        heapRebuild(theArray, idx, itemCount);
    }
}

void heapSort(int theArray[], int itemCount) {
    int heapSize = itemCount;

    // convert array to heap
    heapCreate(theArray, itemCount);

    while (heapSize > 1) {
        // the first entry is the largest item in the heap theArray. Swap it
        // with the end of the heap and decrease the heap size. Repeat until
        // heap size is 1
        swap(theArray[0], theArray[heapSize - 1]);
        moves+=3; // incremement moves
        heapSize--;
        heapRebuild(theArray, 0, heapSize);
    }
}