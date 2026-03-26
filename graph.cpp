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

    std::vector<std::pair<int,int>> edges_list;
    int u, v;
    Compressor compressor;
    compressor.init();
    while(file >> u >> v)
    {
        edges_list.emplace_back(u, v);
        compressor.add(u);
        compressor.add(v);
    }
    compressor.run();
    vertices = compressor.n;
    adjacency_list.clear();
    adjacency_list.resize(vertices);

    for (auto& [u0, v0] : edges_list)
    {
        int cu = compressor.comp(u0);
        int cv = compressor.comp(v0);
        assert((cu < vertices) && (cv < vertices));
        addEdge(cu, cv);
    }

    file.close();
    return true;
}
