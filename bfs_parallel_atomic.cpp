#include <graph.h> // for graph usage
#include <vector> // for vector usage
#include <iostream> // for cout and endl
#include <omp.h>
#include <atomic>
int bfsParallel(Graph &g, int start)
{
  std::vector<std::atomic<int>> visited(g.vertices);
  for (auto &v : visited) v.store(0);
  std::vector<int> frontier;
  frontier.emplace_back(start);
  visited[start].store(1);
  int nm = omp_get_num_threads();
  std::cout << "num threads before parallel region "  << nm << std::endl;
  while(!frontier.empty())
  {
      std::vector<int> next_frontier;
     #pragma omp parallel default(none) shared(visited,frontier,g,next_frontier,nm)
      {
          int id = omp_get_thread_num();
          if (id == 0) nm = omp_get_num_threads();
          std::vector<int> local_next;
          #pragma omp for nowait
          for(int i=0;i<frontier.size();i++)
          {
              int node = frontier[i]; 
              for (int child:g.adjacency_list[node]) 
              {
                 int expected = 0;
                 if (visited[child].compare_exchange_strong(expected,1))
                 {
                    local_next.push_back(child);
                 }
              }

          }
          #pragma omp critical 
          {
              next_frontier.insert(next_frontier.end(),local_next.begin(),local_next.end());

          }
      }
      frontier = next_frontier;
  }
  std::cout << "num threads in parallel region was " << nm << std::endl;


  int counter = 0;
  for(int i=0;i<g.vertices;i++)
  {
     if (visited[i]) counter++;
  }
  return counter;
}
