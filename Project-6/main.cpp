// Homework 6 by Alex Sadler - 001792279

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <climits>

#define maxVert 60
using namespace std;

void shortestPath(int startVert, int endVert, int numVert,
                  int graph[maxVert][maxVert]) {
    // Initialize weights to INT_MAX and all vertex predecessors to unknown
    int vertDist[maxVert];
    int vertPred[maxVert];
    for (int i = 0; i < maxVert; i++) {
        vertDist[i] = INT_MAX;
        vertPred[i] = -1;
    }

    // Distance from starting vertex to itself is 0
    vertDist[startVert] = 0;

    // Initial distances to neighbors of source and set predecessors
    for (int i = 0; i < maxVert; i++) {
        if (graph[startVert][i] < INT_MAX) {
            vertDist[i] = graph[startVert][i];
            vertPred[i] = startVert;
        }
    }

    // Vertex set of vertices with finalized least distance from source
    bool vertSet[maxVert];
    // Source node is always first in vertex set
    vertSet[startVert] = true;

    for (int step = 0; step < numVert - 1; step++) {
        // Add vertex with smallest distance to vertex set
        int minWt = INT_MAX;
        int v;
        for (int i = 0; i < maxVert; i++) {
            if ((vertDist[i] < minWt) && (vertSet[i] == 0)) {
                minWt = vertDist[i];
                v = i;
            }
        }
        vertSet[v] = true;
        vertDist[v] = minWt;

        // if there is an edge between the nodes, if the cost of getting from
        // the starting node to v through u is smaller than the current cost,
        // and if u is not in the vertex set, update cost
        for (int u = 0; u < maxVert; u++) {
            if ((graph[v][u] < INT_MAX) &&
                (vertDist[u] > vertDist[v] + graph[v][u]) &&
                (vertSet[u] == 0)) {
                vertDist[u] = vertDist[v] + graph[v][u];
                vertPred[u] = v;
            }
        }
    }

    // display results
    cout << endl;
    for (int j = 0; j < maxVert; j++) {
        if (vertDist[j] < INT_MAX) {
            cout << "Distance from building " << startVert << " to building "
                 << j << ": " << vertDist[j] << ". Predecessor: " << vertPred[j]
                 << endl;
        }
    }

    cout << endl
         << "Path from building " << endVert << " to building " << startVert
         << ": ";
    int vertTmp = endVert;
    while (vertTmp != startVert) {
        cout << vertTmp << ", ";
        vertTmp = vertPred[vertTmp];
    }
    cout << startVert;
}

int main() {
    // open file
    ifstream inf;
    inf.open("undir_graph.txt");
    if (inf.fail()) {
        cerr << "Error: Could not open input file\n";
        exit(1);
    }

    // activate the exception handling of inf stream
    inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    int adjMatrix[maxVert][maxVert];
    for (int i = 0; i < maxVert; i++) {
        for (int j = 0; j < maxVert; j++) {
            adjMatrix[i][j] = INT_MAX;
        }
    }

    int maxints = maxVert * maxVert;
    int count = 0;
    int numVert;
    int vert1;
    int vert2;
    int dist;
    while (count < maxints) {  // keep reading until reading maxints or until a
                               // reading failure is caught.
        try {
            if (count == 0) {
                inf >> numVert;
            }
            inf >> vert1;
            inf >> vert2;
            inf >> dist;
        }

        // Check for reading failure due to end of file or
        // due to reading a non‐integer value from the file.
        catch (std::ifstream::failure e) {
            break;
        }

        // Add distance between vertices to matrix
        adjMatrix[vert1][vert2] = dist;
        adjMatrix[vert2][vert1] = dist;

        count += 3;
    }

    // starting and ending vertices supplied by user
    int startVert;
    int endVert;
    cout << "Enter start vertex: ";
    cin >> startVert;
    cout << "Enter end vertex: ";
    cin >> endVert;
    cout << endl;

    shortestPath(startVert, endVert, numVert, adjMatrix);

    inf.close();  // Close the file at the end of your program.
    return 0;
}