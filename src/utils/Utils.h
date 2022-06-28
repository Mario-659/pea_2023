#ifndef SDIZO_2_UTILS_H
#define SDIZO_2_UTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <random>
#include <set>

#include "../graphs/AdjacencyList.h"
#include "../graphs/AdjacencyMatrix.h"

namespace utils{
    /**
     * Read int values from file
     *
     * If couldn't read file returns empty vector
     * @param filename name of the file
     * @return vector of lines of values in filename
     */
    std::vector<std::vector<int>> readFromFile(std::string filename);

    /**
     * Create vector with random int values in range <min, max>
     *
     * @return Vector with random values
     */
    std::vector<int> getRandVect(int size, int min, int max);

    void generateRandomDirectedGraphs(AdjacencyMatrix*& matrix, AdjacencyList*& list, int size, int density);

    void generateRandomUndirectedGraphs(AdjacencyMatrix*& matrix, AdjacencyList*& list, int size, int density);
}




#endif //SDIZO_2_UTILS_H
