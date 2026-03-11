#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
public:
  int vertices;
  int edges;
  std::vector<std::vector<int>> adjacency_list;
  
  Graph(int vertices);
  void addEdge(int u, int v);
};

#endif // GRAPH_H
