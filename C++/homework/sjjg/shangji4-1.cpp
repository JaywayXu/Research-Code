#include <iostream>
#include "MinSpanTree.h"
using namespace std;

int main() {
    MSTree mt;
    mt.Kruskal();
    mt.Print_Graph();
    mt.Prim();
    mt.Print_Graph();
    return 0;
}