#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
public:
  int vertices;
  int edges;
  std::vector<std::vector<int>> adjacency_list;
  struct Compressor{
	// compressor 0 based
	vector<int> values;
	int n;
	void init(){
		values.clear();
		n=0;
	}
	void add(int x){
		values.push_back(x);
	}
	void run(){
		sort(values.begin(),values.end());
		values.resize(unique(values.begin(),values.end())-values.begin());
		n=size(values);
	}
	int comp(int val){
		return lower_bound(values.begin(),values.end(),val)-values.begin();
	}
	int decomp(int pos){
		return values[pos];
	}
  };  
  Graph(int vertices);
  void addEdge(int u, int v);
};

#endif // GRAPH_H
