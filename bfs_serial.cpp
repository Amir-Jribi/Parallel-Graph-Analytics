#include <graph.h> // for graph usage
#include <vector> // for vector usage
#include <queue> // for queue usage
#include <iostream> // for cout and endl
#include <cassert>  // for assert 
int bfsSerial(Graph &g, int start,std::vector<int>& distance)
{
//  std::cout << "hello world for bfs serial function" << std::endl;
//return;
  std::vector<int> visited(g.vertices,0);
  std::queue<int> q;
  q.push(start);
  visited[start] = 1;
  distance[start] = 0;
  while(!q.empty())
  {
    int u = q.front();
    assert(u<=g.vertices);
    q.pop();
    for(auto ch:g.adjacency_list[u])
    {
      if (!visited[ch])
      {
        distance[ch] = distance[u] + 1;
        q.push(ch);
        visited[ch] = 1;
      }
    }
  }
  int counter = 0;
  for(int i=0;i<g.vertices;i++)
  {
     if (visited[i]) counter++;
  }
  return counter;
}
