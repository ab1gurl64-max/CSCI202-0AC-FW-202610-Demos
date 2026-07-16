#include <fstream>
#include <iostream>
#include "graph.h"
// graph viz online https://dreampuf.github.io/GraphvizOnline/

int main()
{
    Graph g;
    g.createGraph("graph.txt");
    std::ofstream out("g.txt");
    out << g;
    std::cout << g.breadthFirstTraversal() << std::endl;
    std::cout << g.depthFirstTraversal() << std::endl;
    std::cout << g.dftAtVertex(2) << std::endl;
    return 0;
}