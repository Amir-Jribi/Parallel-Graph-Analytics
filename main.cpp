#include <iostream>
#include <graph.h>

void bfsSerial(Graph &g, int start);

int main(){
  Graph g(5);
  g.addEdge(1,2);
  g.addEdge(2,3);
  g.addEdge(3,4);
  g.addEdge(4,5);
  std::cout << g.vertices << " " << g.edges << std::endl;
  bfsSerial(g, 1);
  std::cout << "hello world" << std::endl; 
  return 0;
}
