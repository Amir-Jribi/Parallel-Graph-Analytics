#!/bin/bash

g++ main.cpp graph.cpp -I.
g++ main.cpp bfs_serial.cpp bfs_parallel.cpp graph.cpp -fopenmp -I.

