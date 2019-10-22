#include<iostream>
#include <list>
#include <stack>
#include "Graph.h"
#include<time.h>

int main() {
    srand(time(nullptr));
    Graph G(10000);
    //G.printMatrix();
    G.Task();
    return 0;
}