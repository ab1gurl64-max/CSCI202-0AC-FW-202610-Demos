#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "unorderedLinkedList.h"
#include "linkedQueue.h"
#include <regex>

class Graph
{
public:
    Graph(int size = 0);
    bool isEmpty() const;
    void createGraph(std::string);
    void clearGraph();
    friend std::ostream &operator<<(std::ostream &, Graph &);

protected:
    int maxSize;
    std::vector<UnorderedLinkedList<int>> graph;
};

#endif