#include <graph.h> // for graph usage
#include <vector> // for vector usage
#include <iostream> // for cout and endl
#include <omp.h>
void bfsParallel(Graph &g, int start)
{
  std::vector<bool> visited(g.vertices+1,false);
  std::vector<int> frontier;
  frontier.emplace_back(start);
  visited[start] = 1;
  while(!frontier.empty())
  {
      std::vector<int> next_frontier;
     #pragma omp parallel
      {
          std::vector<int> local_next;
          #pragma omp for nowait
          for(int i=0;i<frontier.size();i++)
          {
              #pragma omp critical
              {
                  if (!visited[frontier[i]])
                  {
                      visited[frontier[i]] = true;
                      local_next.emplace_back(frontier[i]);
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
}
