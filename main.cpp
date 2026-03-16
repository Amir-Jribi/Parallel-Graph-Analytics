#include <iostream>
#include <graph.h>
#include <cassert>
#include <omp.h>
#include <iomanip> // for setprecision

int bfsSerial(Graph &g, int start);
int bfsParallel(Graph &g, int start);

int main(){
  Graph g(6); // from 0 to 5
  g.addEdge(0,1);
  g.addEdge(1,2);
  g.addEdge(2,3);
  g.addEdge(3,4);
  g.addEdge(4,5);
  std::cout << g.vertices << " " << g.edges << std::endl;
  double start, end;
  start = omp_get_wtime();
  int v1 = bfsSerial(g, 0);
  end = omp_get_wtime();
  std::cout << std::fixed ;
  std::cout << std::setprecision(10) << "Time taken for Serial BFS = " << end-start << "s" << std::endl;
  start = omp_get_wtime();
  int v2 = bfsParallel(g,0);
  end = omp_get_wtime();
  std::cout << std::setprecision(10) << "Time taken for Parall BFS = " << end-start << "s" << std::endl;
//  assert(v1==v2);
  std::cout << "v1 = " << v1 << " v2 = " << v2 << std::endl;
  std::cout << "hello world" << std::endl; 

  Graph G(0);
  G.loadFromFile("graphs/facebook_combined.txt");
  std::cout << G.vertices << " " << G.edges << std::endl;

  start = omp_get_wtime();
  v1 = bfsSerial(G, 0);
  end = omp_get_wtime();
  std::cout << std::setprecision(10) << "Time taken for Serial BFS = " << end-start << "s" << std::endl;
  start = omp_get_wtime();
  v2 = bfsParallel(G,0);
  end = omp_get_wtime();
  std::cout << std::setprecision(10) << "Time taken for Parall BFS = " << end-start << "s" << std::endl;

  std::cout << "v1 = " << v1 << " v2 = " << v2 << std::endl;


  Graph gr(0);
  gr.loadFromFile("graphs/web-Google.txt");
  std::cout << gr.vertices << " " << gr.edges << std::endl;

  start = omp_get_wtime();
  v1 = bfsSerial(gr, 0);
  end = omp_get_wtime();
  std::cout << std::setprecision(10) << "Time taken for Serial BFS = " << end-start << "s" << std::endl;
  start = omp_get_wtime();
  v2 = bfsParallel(gr,0);
  end = omp_get_wtime();
  std::cout << std::setprecision(10) << "Time taken for Parall BFS = " << end-start << "s" << std::endl;

  std::cout << "v1 = " << v1 << " v2 = " << v2 << std::endl;
  
  return 0;
}
