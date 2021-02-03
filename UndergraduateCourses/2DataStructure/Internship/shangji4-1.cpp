#include <iostream>
#include "MinSpanTree.h"
using namespace std;

int main() {
    // MSTree mt;
    // mt.Print_Graph();
    // mt.Kruskal();
    // mt.Prim();
    Graph G;
    G.numVertexes = 4;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            cin >> G.arc[i][j];
        }
    }
    cout << InDegree(G, 3) << endl;;
    return 0;
}