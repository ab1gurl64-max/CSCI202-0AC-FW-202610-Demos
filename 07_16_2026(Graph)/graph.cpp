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

std::string Graph::depthFirstTraversal()
{
    std::vector<bool> visited(graph.size(), false);
    std::ostringstream out;
    for (int i = 0; i < graph.size(); i++)
    {
        if (!visited[i])
        {
            dft(i, visited, out);
        }
    }
    return out.str();
}

std::string Graph::dftAtVertex(int vertex)
{
    std::vector<bool> visited(graph.size(), false);
    std::ostringstream out;
    dft(vertex, visited, out);
    return out.str();
}

std::string Graph::breadthFirstTraversal()
{
    LinkedQueue<int> queue;
    std::vector<bool> visited(graph.size(), false);
    std::ostringstream out;
    for (int i = 0; i < graph.size(); i++)
    {
        if (!visited[i])
        {
            queue.enqueue(i);
            while (!queue.isEmptyQueue())
            {
                int u = queue.dequeue();
                if (!visited[u])
                {
                    visited[u] = true;
                    out << u << " ";
                }
                for (auto graphIt = graph[u].begin(); graphIt != graph[u].end(); ++graphIt)
                {
                    int w = *graphIt;
                    if (!visited[w])
                    {
                        queue.enqueue(w);
                    }
                }
            }
        }
    }
    return out.str();
}

void Graph::dft(int v, std::vector<bool> &visited, std::ostringstream &output)
{
    visited[v] = true;
    output << v << " ";
    LinkedListIterator<int> graphIt;
    for (graphIt = graph[v].begin(); graphIt != graph[v].end(); ++graphIt)
    {
        int w = *graphIt;
        if (!visited[w])
        {
            dft(w, visited, output);
        }
    }
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
