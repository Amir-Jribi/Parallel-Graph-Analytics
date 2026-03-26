#include <iostream>
#include <graph.h>
#include <assert.h>
#include <omp.h>
#include <iomanip> // for setprecision

int bfsSerial(Graph &g, int start, std::vector<int>& distance);
int bfsParallel(Graph &g, int start, std::vector<int>& distance);

int main(){
  double start, end;
  int v1,v2;


  // Graph gr(0);
  // gr.loadFromFile("graphs/web-Google.txt");
  // std::cout << gr.vertices << " " << gr.edges << std::endl;
  // start = omp_get_wtime();
  // v1 = bfsSerial(gr, 0);
  // end = omp_get_wtime();
  // std::cout << std::setprecision(10) << "Time taken for Serial BFS = " << end-start << "s" << std::endl;
  // start = omp_get_wtime();
  // v2 = bfsParallel(gr,0);
  // end = omp_get_wtime();
  // std::cout << std::setprecision(10) << "Time taken for Parall BFS = " << end-start << "s" << std::endl;

  // std::cout << "v1 = " << v1 << " v2 = " << v2 << std::endl;
  
  // std::cout << "------------------------------" << std::endl;

  Graph g(0);
  g.loadFromFile("graphs/soc-LiveJournal1.txt");
  std::vector<int> d1(g.vertices), d2(g.vertices);
  std::cout << g.vertices << " " << g.edges << std::endl;
  start = omp_get_wtime();
  v1 = bfsSerial(g, 0, d1);
  end = omp_get_wtime();
  std::cout << std::setprecision(10) << "Time taken for Serial BFS = " << end-start << "s" << std::endl;
  start = omp_get_wtime();
  v2 = bfsParallel(g, 0, d2);
  end = omp_get_wtime();
  std::cout << std::setprecision(10) << "Time taken for Parall BFS = " << end-start << "s" << std::endl;
  for(int i=0; i < g.vertices; ++i)
  {
    assert(d1[i]==d2[i]);
  }
  std::cout << "v1 = " << v1 << " v2 = " << v2 << std::endl;
  return 0;
}
