#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <algorithm>
#include <vector>
class Graph {
public:
  int vertices;
  int edges;
  std::vector<std::vector<int>> adjacency_list;
  Graph(int vertices);
  void addEdge(int u, int v);
  bool loadFromFile(const std::string &filename);
  struct Compressor
  {
    std::vector<int> values;
    int n;
    void init()
    {
      values.clear();
      n = 0;
    }
    void add(int x){
      values.push_back(x);
    }
    void run()
    {
      std::sort(values.begin(),values.end());
      values.resize(std::unique(values.begin(),values.end())-values.begin());
      n = values.size();
    }
    int comp(int val)
    {
      return std::lower_bound(values.begin(),values.end(),val)-values.begin();
    }
    int decomp(int pos)
    {
      return values[pos];
    }
  }; // end of Compressor
};




#endif // GRAPH_H
