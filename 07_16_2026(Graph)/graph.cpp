#include "graph.h"

Graph::Graph(int size)
{
    if (size >= 0)
    {
        maxSize = size;
    }
    else
    {
        maxSize = 0;
    }
    graph.resize(maxSize);
}

bool Graph::isEmpty() const
{
    return graph.empty();
}

void Graph::createGraph(std::string filename)
{
    std::ifstream fin(filename);
    int index = 0;
    int vertex = 0;
    int adjacentVertex = 0;
    int totalVertex = 0;
    if (!isEmpty())
    {
        clearGraph();
    }
    if (!fin.is_open())
    {
        throw std::runtime_error("Cannot open input file.");
    }
    while (!fin.eof())
    {
        std::string temp;
        getline(fin, temp);
        totalVertex++;
    }
    fin.seekg(0);
    if (maxSize < totalVertex)
    {
        maxSize = totalVertex;
        graph.resize(maxSize);
    }
    while (!fin.eof())
    {
        fin >> vertex;
        fin >> adjacentVertex;
        while (adjacentVertex != -999)
        {
            graph[vertex].insert(adjacentVertex);
            fin >> adjacentVertex;
        }
    }
    fin.close();
}
