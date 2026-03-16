#include <graph.h> // for graph usage
#include <vector> // for vector usage
#include <iostream> // for cout and endl
#include <omp.h>
int bfsParallel(Graph &g, int start)
{
  std::vector<bool> visited(g.vertices,false);
  std::vector<int> frontier;
  frontier.emplace_back(start);
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
                      for(int j=0;j<size(g.adjacency_list[frontier[i]]);j++) 
                      {
                        local_next.emplace_back(g.adjacency_list[frontier[i]][j]);
                      }
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

  int counter = 0;
  for(int i=0;i<g.vertices;i++)
  {
     if (visited[i]) counter++;
  }
  return counter;
}
