#ifndef PEA_UTILS_H
#define PEA_UTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <random>
#include <set>

#include "../graphs/AdjacencyMatrix.h"

namespace utils {
    /**
     * Read int values from file
     *
     * Throws std::invalid_argument when encounters
     * error while opening file
     *
     * @param filename name of the file
     * @return vector of lines of values in filename
     */
    std::vector<std::vector<int>> readFromFile(std::string filename);
}

#endif //PEA_UTILS_H
