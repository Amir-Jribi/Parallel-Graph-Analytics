#include <graph.h> // for graph usage
#include <vector> // for vector usage
#include <iostream> // for cout and endl
#include <omp.h>
#include <atomic>
#include <array>
#include <assert.h>
const int THREAD_BUF_LEN = 64;
int bfsParallel(Graph &g, int start, std::vector<int>& distance)
{

  int l = 0, r = 1;
  std::atomic<int> cur_len(1);
  std::vector<int> vlist(g.vertices);
  vlist[0] = start;
  std::vector<std::atomic<int>> visited(g.vertices);
  for (auto &v : visited) v.store(0);
  visited[start].store(1);
  distance[start] = 0;
  int nm = omp_get_num_threads();
  std::cout << "num threads before parallel region "  << nm << std::endl;
  while (l < r)
  {

    #pragma omp parallel default(none) shared(visited,cur_len,g,vlist,l,r,nm,distance)
    {
      int id = omp_get_thread_num();
      if (id == 0) nm = omp_get_num_threads();
      std::array<int,THREAD_BUF_LEN> nbuf; // local for each thread
      int kbuf = 0;
      #pragma omp for 
      for(int k = l; k < r; ++k)
      {
        const int v = vlist[k];

        for(int vo = 0; vo < size(g.adjacency_list[v]); ++vo)
        {
          const int j = g.adjacency_list[v][vo];
          int expected = 0;
          if (visited[j].compare_exchange_strong(expected,1))
          {
            distance[j] = distance[v] + 1; // this can be accessed only by one thread, there can be happen concurrent read for distance[v]
            if (kbuf < THREAD_BUF_LEN)
            {
              nbuf[kbuf++] = j;
            }
            else 
            {
              int old_len = cur_len.fetch_add(THREAD_BUF_LEN);
              assert(old_len + THREAD_BUF_LEN <= g.vertices);
              for (int vk = 0; vk < THREAD_BUF_LEN; ++vk)
              {
                vlist[old_len + vk] = nbuf[vk];
              }
              nbuf[0] = j;
              kbuf = 1;
            }
          }

        }
      }
      if (kbuf > 0)
      {
        int old_len = cur_len.fetch_add(kbuf);
        assert(old_len + kbuf <= g.vertices);
        for (int vk = 0; vk < kbuf; ++vk)
        {
          vlist[old_len + vk] = nbuf[vk];
        }
      }
      
    }
    l = r;
    r = cur_len.load();
  }


  std::cout << "num threads in parallel region was " << nm << std::endl;


  int counter = 0;
  for(int i=0;i<g.vertices;i++)
  {
     if (visited[i]) counter++;
  }
  return counter;
}
