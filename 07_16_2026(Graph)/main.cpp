#include <fstream>
#include <iostream>
#include "graph.h"

int main()
{
    Graph g;
    g.createGraph("graph.txt");
    std::ofstream out("g.txt");
    out << g;
    return 0;
}