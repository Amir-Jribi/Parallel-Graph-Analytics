#include <graph.h>


Graph::Graph(int vertices): vertices(vertices), edges(0)
{
  adjacency_list.resize(vertices+1); // resize(vertices) will cause to seg fault , as we didnt allocate enough space
}

void Graph::addEdge(int u, int v)
{
  adjacency_list[u].emplace_back(v);
  edges++;
}
