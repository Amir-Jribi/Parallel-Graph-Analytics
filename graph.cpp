#include <graph.h>
#include <iostream> // for std::cout and std::endl
#include <vector>
#include <map>
#include <fstream> // for std::ifstream
#include <algorithm> // required for std::sort and std::unique
#include <assert.h>
Graph::Graph(int vertices): vertices(vertices), edges(0)
{
  adjacency_list.resize(vertices); 
  // resize(vertices) will cause to seg fault , as we didnt allocate enough space if we are indexing from 1
  // resize(vertices) will be good if we index from 0
}

void Graph::addEdge(int u, int v)
{
  adjacency_list[u].emplace_back(v);
  edges++;
}

// addEdge from loadFromFile method maybe need to be addressed in case 
// the numbering is not contiguous
bool Graph::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "The filename " << filename << "that was provided doesnt exist !" << std::endl;
        return false;
    }
    // the file contains only edges its up to us to figure out vertices and edges
    // and try to have contiguous numbering ( from 0 to number of vertices - 1)
    adjacency_list.clear();
    // size of adjecency_list of 5e6 is enough for now for the datasets that we are testing on!
    // wanna scale more! maybe go to coordinate compression technique
    adjacency_list.resize(5e6); 
    vertices = 5e6;
    int u, v;
    while(file >> u >> v)
    {
        assert(u<5e6 && v<5e6);
        addEdge(u,v);
    }

    file.close();
    return true;
}
