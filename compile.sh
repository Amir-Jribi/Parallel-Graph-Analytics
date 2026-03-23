#!/bin/bash

for t in 1 2 4 8 16
do
   export OMP_NUM_THREADS=$t
   g++ main.cpp graph.cpp bfs_serial.cpp bfs_parallel.cpp -fopenmp -I.
   ./a.out
done


g++ main.cpp bfs_serial.cpp bfs_parallel.cpp graph.cpp -g -std=c++17 -fopenmp -I.

# add -fsanitize=thread in compilation flags
#structured bindings only available with -std=c++17 or -std=gnu++17
#     for(auto [par,vec]:m)
