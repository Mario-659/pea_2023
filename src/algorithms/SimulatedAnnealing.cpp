#include "SimulatedAnnealing.h"
#include <cmath>
#include <algorithm>
#include <chrono>
#include <random>

SimulatedAnnealing::SimulatedAnnealing(double initialCoolingRatio, int timeLimit, unsigned int seed)
        : coolingRatio(initialCoolingRatio), timeLimit(timeLimit), seed(seed) {}

void SimulatedAnnealing::solve(AdjacencyMatrix& graph) {
    std::mt19937 urbg {seed};
    verticesNumber = graph.getSize();
    temperature = getInitialTemperature(graph, urbg);
    path = getDefaultPath();
    int optimalCost = getPathCost(path, graph);


    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> measureTimes;
    while(true){
        std::vector<int>newPath = swapElementsInPath(verticesNumber, path, urbg);
        int newCost = getPathCost(newPath, graph);
        if(newCost<optimalCost){
            path = newPath;
            optimalCost = newCost;
            auto bestTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = bestTime - start;

        } else {
            double probability = exp(-abs(optimalCost-newCost)/temperature);
            double uniformDistributionRandomValue = std::uniform_real_distribution<double>(0, 1)(urbg);
            if(probability > uniformDistributionRandomValue){
                path = newPath;
                optimalCost = newCost;
            }
        }
        temperature *= coolingRatio;
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        int timeNow = int(elapsed.count());
        if(std::find(measureTimes.begin(), measureTimes.end(), timeNow) == measureTimes.end() && timeNow%20==0){
            measureTimes.push_back(timeNow);
        }
        if(elapsed.count() > timeLimit){
            break;
        }
    }

    shortestPathLength = optimalCost;
}

int SimulatedAnnealing::getPathCost(const std::vector<int>& pathInstance, const AdjacencyMatrix& graph) {
    if (pathInstance.empty()) return 0;

    int cost = 0;
    for (size_t i = 1; i < pathInstance.size(); ++i) {
        cost += graph.getEdgeWeight(pathInstance[i - 1], pathInstance[i]);
    }
    cost += graph.getEdgeWeight(pathInstance.back(), pathInstance[0]);
    return cost;
}

double SimulatedAnnealing::getInitialTemperature(AdjacencyMatrix& graph, std::mt19937& urbg) {
    int iterations = 10000;
    std::vector<int> samplePath = getDefaultPath();
    std::vector<int> oldPath;
    double averageCost = 0;
    for(int i=0;i<iterations; i++){
        oldPath = samplePath;
        samplePath = swapElementsInPath(verticesNumber, samplePath, urbg);
        averageCost += abs(getPathCost(samplePath, graph)- getPathCost(oldPath, graph));
    }
    return abs((averageCost/iterations)/log(0.99));
}

std::vector<int> SimulatedAnnealing::getDefaultPath() {
    std::vector<int> defaultPath(verticesNumber);
    std::iota(defaultPath.begin(), defaultPath.end(), 0);
    return defaultPath;
}

std::vector<int> SimulatedAnnealing::swapElementsInPath(int range, std::vector<int> oldPath, std::mt19937& urbg) {
    std::vector<int> newPath = std::move(oldPath);
    if (newPath.size() < 2) return newPath;

    std::uniform_int_distribution<int> dist(0, range - 1);

    int firstCityToSwap = dist(urbg);
    int secondCityToSwap = dist(urbg);
    while (firstCityToSwap == secondCityToSwap) {
        secondCityToSwap = dist(urbg);
    }

    std::iter_swap(newPath.begin() + firstCityToSwap, newPath.begin() + secondCityToSwap);
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
