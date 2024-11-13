#include "SimulatedAnnealing.h"
#include <cmath>
#include <algorithm>
#include <chrono>

SimulatedAnnealing::SimulatedAnnealing(double initialCoolingRatio, int timeLimit)
        : coolingRatio(initialCoolingRatio), timeLimit(timeLimit) {}

void SimulatedAnnealing::solve(AdjacencyMatrix& graph) {
    verticesNumber = graph.getSize();
    temperature = getInitialTemperature();
    path = getDefaultPath();

    int optimalCost = getPathCost(path);
    auto start = std::chrono::high_resolution_clock::now();

    while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() < timeLimit) {
        std::vector<int> newPath = swapElementsInPath(path);
        int newCost = getPathCost(newPath);

        if (newCost < optimalCost || exp(-(newCost - optimalCost) / temperature) > std::generate_canonical<double, 10>(std::mt19937{std::random_device{}()})) {
            path = newPath;
            optimalCost = newCost;
        }

        temperature *= coolingRatio;
    }

    shortestPathLength = optimalCost;
}

int SimulatedAnnealing::getPathCost(const std::vector<int>& pathInstance) {
    int cost = 0;
    for (int i = 1; i < pathInstance.size(); ++i) {
        cost += routes[pathInstance[i - 1]][pathInstance[i]];
    }
    cost += routes[pathInstance.back()][pathInstance[0]];
    return cost;
}

double SimulatedAnnealing::getInitialTemperature() {
    double avgCostChange = 0;
    std::vector<int> path = getDefaultPath();
    for (int i = 0; i < 10000; ++i) {
        std::vector<int> newPath = swapElementsInPath(path);
        avgCostChange += std::abs(getPathCost(newPath) - getPathCost(path));
        path = std::move(newPath);
    }
    return avgCostChange / 10000 / log(0.99);
}

std::vector<int> SimulatedAnnealing::getDefaultPath() {
    std::vector<int> defaultPath(verticesNumber);
    std::iota(defaultPath.begin(), defaultPath.end(), 0);
    return defaultPath;
}

std::vector<int> SimulatedAnnealing::swapElementsInPath(const std::vector<int>& oldPath) {
    std::vector<int> newPath = oldPath;
    std::swap(newPath[rand() % verticesNumber], newPath[rand() % verticesNumber]);
    return newPath;
}

std::string SimulatedAnnealing::toString() {
    std::string result;
    for (const int& city : path) {
        result += std::to_string(city) + " -> ";
    }
    result += "0";
    return result;
}
