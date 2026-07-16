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
    std::string depthFirstTraversal();
    std::string dftAtVertex(int vertex);
    std::string breadthFirstTraversal();
    static std::regex nameRegex;

protected:
    int maxSize;
    std::vector<UnorderedLinkedList<int>> graph;
    std::vector<std::string> names;

private:
    void dft(int v, std::vector<bool> &visited, std::ostringstream &output);
};

#endif