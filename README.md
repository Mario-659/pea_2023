# Traveling Salesman Problem (TSP) Solver

This repository contains a C++ implementation of various methods to solve the Traveling Salesman Problem (TSP). It provides both **exact algorithms** (Brute Force, Branch and Bound, Dynamic Programming) and **metaheuristics** (Tabu Search, Simulated Annealing, Genetic Algorithm) to find (or approximate) the shortest possible route that visits each city exactly once and returns to the origin city.

## Features

1. **Exact Algorithms**:
    - **Brute Force**  
      Enumerates all permutations of the cities.
    - **Branch and Bound**  
      Uses a tree-based search with pruning based on a lower bound.
    - **Dynamic Programming**  
      Exploits memoization to avoid recomputing subproblems.

2. **Metaheuristics**:
    - **Tabu Search**  
      Uses a tabu list to avoid cycling and local minima, with intensification/diversification steps.
    - **Simulated Annealing**  
      Gradually cools temperature while randomly exploring the solution space.
    - **Genetic Algorithm**  
      Uses a population of solutions with crossover and mutation operators.
    - **Greedy**  
      Constructs a quick path by repeatedly choosing the nearest neighbor.

3. **Other**:
    - `AdjacencyMatrix` for graph representation.
    - A custom `Heap` for Branch and Bound priority queues.

4. **Testing**:  
   A Google Test suite is included (see `test` and `test_performance` directories).

---

## Building the Project

**Prerequisites**:
- A C++17 compatible compiler
- [CMake](https://cmake.org/) version >= 3.21

**Steps**:

1. **Create a build directory** and configure:
   ```bash
   mkdir build && cd build
   cmake ..
   ```
   By default, this will download and build GoogleTest (if not found on your system) and configure the project.

2. **Build**:
   ```bash
   cmake --build .
   ```
   This will produce the main executable (e.g., `PEA_run` on Linux/macOS or `PEA_run.exe` on Windows) in the `build/src` directory, along with test executables in `build/test` and `build/test_performance`.

---

## Running the Program

After building, **run** the main executable:

```bash
# From the 'build' directory
./src/PEA_run
```

The program will display the **Tabu/Metaheuristics Menu** by default (as `startTSMenu()` is called in `main.cpp`).

### Switching Between Menus

Inside `main.cpp`, you will see:
```cpp
// startSPMenu();  // exact algorithms menu
startTSMenu();    // metaheuristics menu
```
If you want to use the **exact algorithms** (Brute Force, Branch and Bound, Dynamic), comment out `startTSMenu();` and uncomment `startSPMenu();` (and rebuild).

---

## File Format

### ATSP Format (example)
```
ATSP
DIMENSION: 5
EDGE_WEIGHT_SECTION
0 14 4 9 1
14 0 5 2 10
4 5 0 7 9
9 2 7 0 3
1 10 9 3 0
```
After loading, the program constructs the adjacency matrix. Instances and descriptions of this file format can be found on [Heideberg-Uni site](http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/index.html);

### Custom Format (example)
```
5
0 14 4 9 1
14 0 5 2 10
4 5 0 7 9
9 2 7 0 3
1 10 9 3 0
```
Where:
- **First line** is the size (number of vertices).
- Subsequent lines represent the adjacency matrix rows.
