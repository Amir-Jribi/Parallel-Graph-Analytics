# Parallel Breadth-First Search (BFS) with OpenMP

## Overview
This project implements the **Breadth-First Search (BFS)** algorithm in both **serial** and **parallel** versions using **C++** and **OpenMP**. The goal is to analyze performance improvements and scalability when traversing large-scale graphs using multi-threading.

The project also includes benchmarking on real-world datasets and an analysis of synchronization challenges in parallel graph traversal.

---

## Features
- Serial BFS implementation
- Parallel BFS using OpenMP
- Benchmarking on large real-world graph datasets
- Scalability analysis across multiple threads
- Identification of synchronization bottlenecks

---

## Datasets
Experiments were conducted using large graph datasets from the **SNAP (Stanford Network Analysis Platform)** collection, such as:
- Facebook Combined
- Web-Google
- Twitter (optional / extensible)

---

## Implementation Details

### Serial BFS
- Standard queue-based traversal
- Ensures correctness and serves as a performance baseline

### Parallel BFS (OpenMP)
- Parallelization of frontier expansion
- Use of OpenMP directives (`#pragma omp parallel`, `for`, etc.)
- Explores different synchronization strategies:
  - Critical sections (`#pragma omp critical`)
  - Atomic operations (compare and swap)

---

## Performance Analysis
- Compared execution time between serial and parallel versions
- Evaluated scalability with increasing thread counts
- Identified bottlenecks due to:
  - Thread contention
  - Synchronization overhead

---

## Build Instructions

### Requirements
- GNU compiler
- OpenMP support
- Make

### Compile
```bash
make all
