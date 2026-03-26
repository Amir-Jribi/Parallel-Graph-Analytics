#include <graph.h> // for graph usage
#include <vector> // for vector usage
#include <iostream> // for cout and endl
#include <omp.h>
int bfsParallel(Graph &g, int start)
{
  std::vector<int> visited(g.vertices,0);
  std::vector<int> frontier;
  frontier.emplace_back(start);
  visited[start] = true;
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
                if (!visited[child]) // this can be read by multiple threads, would cause a problem ?, if multiple nodes have an edge with the child node !
                {
                    #pragma omp critical 
                    {
                        if (!visited[child])
                         {
                             visited[child] = 1;
                             local_next.emplace_back(child);
                         }

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
  std::cout << "num threads in parallel region was " << nm << std::endl;


  int counter = 0;
  for(int i=0;i<g.vertices;i++)
  {
     if (visited[i]) counter++;
  }
  return counter;
}