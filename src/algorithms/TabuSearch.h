#ifndef PEA_TABUSEARCH_H
#define PEA_TABUSEARCH_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <typeinfo>
#include <chrono>

using namespace std;

class TabuSearch {
public:
    int verticesNumber = 48;
    int timeLimit = 5;
    vector<vector<int>> routes;
    vector<int> path;

    void readDataFromFile(string fileName);
    int getPathCost(vector<int> pathInstance);
    vector<int> getDefaultTabuPath();
    vector<int> generateRandomPath();
    void solveTSPUsingTabuSearch();
};

#endif //PEA_TABUSEARCH_H
