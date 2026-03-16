#include <graph.h>
#include <iostream> // for std::cout and std::endl
#include <vector>
#include <map>
#include <fstream> // for std::ifstream
#include <algorithm> // required for std::sort and std::unique
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
    int u, v;
    std::map<int,std::vector<int>> m;
    std::vector<int> nodes;
    std::map<int,int> comp;
    while(file >> u >> v)
    {
        m[u].emplace_back(v);
        nodes.emplace_back(u);
        nodes.emplace_back(v);
    }
    sort(nodes.begin(),nodes.end());
    nodes.resize(unique(nodes.begin(),nodes.end())-nodes.begin()); // remove duplicate numbers
    adjacency_list.resize(nodes.size()); // resize to match the number of vertices
    vertices = nodes.size();
    
    for(int i=0;i<size(nodes);i++)
    {
        comp[nodes[i]] = i;
    }
    for(auto [par,vec]:m)
    {
        for(auto ch:vec)
        {
           addEdge(comp[par],comp[ch]); 
        }
    }
    file.close();
    return true;
}
