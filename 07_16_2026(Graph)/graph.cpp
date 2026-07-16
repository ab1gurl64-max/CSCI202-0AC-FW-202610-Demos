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

void Graph::clearGraph()
{
    for (int i = 0; i < graph.size(); i++)
    {
        graph[i].destroyList();
    }
    graph.clear();
    maxSize = 0;
}

std::ostream &operator<<(std::ostream &out, Graph &g)
{
    out << "digraph {" << std::endl; // graphviz
    for (int i = 0; i < g.graph.size(); i++)
    {
        /* out << i << " ";
        g.graph[i].print(out);
        out << std::endl; //python program output*/
        for (LinkedListIterator<int> graphIt = g.graph[i].begin(); graphIt != g.graph[i].end(); ++graphIt)
        {
            out << i << "->" << *graphIt << ";" << std::endl;
        }
    }
    out << std::endl; // graphViz output
    out << "}";
    return out;
}
