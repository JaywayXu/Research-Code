#include <iostream>
#include "MinSpanTree.h"
using namespace std;

int main() {
    MSTree mt;
    mt.Print_Graph();
    mt.Kruskal();
    mt.Prim();
    return 0;
}