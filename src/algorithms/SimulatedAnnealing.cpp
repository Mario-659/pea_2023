#include "SimulatedAnnealing.h"
#include "Greedy.h"
#include <cmath>
#include <chrono>

SimulatedAnnealing::SimulatedAnnealing(double initialCoolingRatio, int timeLimit)
        : coolingRatio(initialCoolingRatio), timeLimit(timeLimit) {}

void SimulatedAnnealing::solve(AdjacencyMatrix &graph) {
    verticesNumber = graph.getSize();
    temperature = getInitialTemperature(graph);
    std::cout << "Initial temperature: " << temperature << std::endl;

    initialTemperature = temperature;
    path = getDefaultPath(graph);
    int optimalCost = getPathCost(path, graph);

//    std::vector<double> probabilities;

    std::random_device rd;
    std::mt19937 urbg{rd()};

    auto bestTime = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::high_resolution_clock::now();

    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start) < timeLimit) {
        // generate new random path
        std::vector<int> newPath = swapElementsInPath(verticesNumber, path);
        int newCost = getPathCost(newPath, graph);

        // accept better path
        if (newCost < optimalCost) {
            path = newPath;
            optimalCost = newCost;
            bestTime = std::chrono::high_resolution_clock::now();
        } else {

            double probability = exp(-abs(optimalCost - newCost) / temperature);
            double uniformDistributionRandomValue = std::uniform_real_distribution<double>(0, 1)(urbg);

//            probabilities.push_back(probability);

            // accept worse path based on probability
            if (probability > uniformDistributionRandomValue) {
                path = newPath;
                optimalCost = newCost;
            }
        }

        temperature *= coolingRatio;
    }

    std::cout << "Final temperature: " << temperature << std::endl;

//    for (int i=0; i < 100; i++) {
//        std::cout << "Probability[i]: " << probabilities[i] << std::endl;
//    }
//
//    for (int i=probabilities.size()-1; i > probabilities.size() - 100; i--) {
//        std::cout << "Probability[i]: " << probabilities[i] << std::endl;
//    }

    optimalSolutionTime = std::chrono::duration_cast<std::chrono::milliseconds>(bestTime - start);
    finalTemperature = temperature;
    shortestPathLength = optimalCost;
}

int SimulatedAnnealing::getPathCost(const std::vector<int> &pathInstance, const AdjacencyMatrix &graph) {
    if (pathInstance.empty()) return 0;

    int cost = 0;
    for (size_t i = 1; i < pathInstance.size(); ++i) {
        cost += graph.getEdgeWeight(pathInstance[i - 1], pathInstance[i]);
    }
    cost += graph.getEdgeWeight(pathInstance.back(), pathInstance[0]);
    return cost;
}

double SimulatedAnnealing::getInitialTemperature(AdjacencyMatrix &graph) {
    int iterations = 10000;
    std::vector<int> samplePath = getDefaultPath(graph);
    std::vector<int> oldPath;
    double averageCost = 0;
    for (int i = 0; i < iterations; i++) {
        oldPath = samplePath;
        samplePath = swapElementsInPath(verticesNumber, samplePath);
        averageCost += abs(getPathCost(samplePath, graph) - getPathCost(oldPath, graph));
    }
    return abs((averageCost / iterations) / log(0.99));
}

std::vector<int> SimulatedAnnealing::getDefaultPath(AdjacencyMatrix& adjacencyMatrix) {
    Greedy greedy;
    greedy.solve(adjacencyMatrix);
    return greedy.path;
}

std::vector<int> SimulatedAnnealing::swapElementsInPath(int range, std::vector<int> oldPath) {
    std::vector<int> newPath = std::move(oldPath);

    // generate random cities to swap
    int firstCityToSwap = rand() % range;
    int secondCityToSwap = rand() % range;
    while (firstCityToSwap == secondCityToSwap) {
        secondCityToSwap = rand() % range;
    }

    // swap cities
    iter_swap(newPath.begin() + firstCityToSwap, newPath.begin() + secondCityToSwap);

    return newPath;
}

void SimulatedAnnealing::setTimeLimit(std::chrono::seconds timeLimit) {
    this->timeLimit = timeLimit;
};

void SimulatedAnnealing::setCoolingRatio(double coolRatio) {
    this->coolingRatio = coolRatio;
};

std::string SimulatedAnnealing::toString() {
    std::ostringstream oss;
    oss << "Shortest Path Length: " << shortestPathLength << "\nPath: ";
    for (int node: path) {
        oss << node << " -> ";
    }
    oss << path[0]; // Close the cycle
    return oss.str();
}
