#ifndef PEA_GENETIC_H
#define PEA_GENETIC_H

#include <set>
#include "TSPSolver.h"
#include "graphs/AdjacencyMatrix.h"
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
using namespace std::chrono;

class Chromosome {
public:
    vector<int> genes;
    int value;

    Chromosome() : value(0) {}

    ~Chromosome() {}
};

class Genetic {
public:
    Chromosome bestChromosome;
    int bestChromosomeLength;
    long long timeToFindBest;

    enum MutationStrategy {
        SWAP, INVERSE
    };

    MutationStrategy mutationStrategy = MutationStrategy::INVERSE;

    // time limit in seconds
    int timeLimit;

    int crossingFactor, mutationFactor;

    int populationSize;
    vector<Chromosome> population;

    // zmienne potrzebne do wykresow
    vector<long long> timeVector;
    vector<double> bladVector;

    vector<long long> bestTimeVector;
    vector<double> bestBladVector;

    steady_clock::time_point start;

    int matrixSize;

    double bladWzgledny;
    int opt = 1608;

    void validateBestChromosome(Chromosome chromosome) {
        if (chromosome.value >= bestChromosomeLength) {
            return;
        }

        steady_clock::duration duration;
        duration = steady_clock::now() - start;
        timeToFindBest = duration_cast<microseconds>(duration).count();

        timeVector.push_back(timeToFindBest);
        bladVector.push_back(100.0 * (bestChromosomeLength - opt) / (double) opt);

        bestChromosome = chromosome;
        bestChromosomeLength = chromosome.value;
    }

    int calculateChromosomeLength(Chromosome chromosome, AdjacencyMatrix &adjacencyMatrix) {
        int length = 0;
        for (int i = 0; i < matrixSize - 1; i++) {
            length += adjacencyMatrix.getEdgeWeight(chromosome.genes[i], chromosome.genes[i + 1]);
        }
        length += adjacencyMatrix.getEdgeWeight(chromosome.genes[matrixSize - 1], chromosome.genes[0]);
        return length;
    }

    int generateRandomInt(int min, int max) {
        return rand() % (max - min + 1) + min;
    }

    Chromosome generateRandomChromosome(AdjacencyMatrix &adjacencyMatrix) {
        Chromosome chromosome;

        std::vector<int> cities(matrixSize);
        std::iota(cities.begin(), cities.end(), 0); // fill with 0, 1, 2
        std::shuffle(cities.begin(), cities.end(), std::mt19937(std::random_device{}()));

        chromosome.genes = cities;
        chromosome.value = calculateChromosomeLength(chromosome, adjacencyMatrix);

        return chromosome;
    }

    Chromosome inversionMutation(Chromosome chromosome, AdjacencyMatrix &matrix) {
        int firstIndex;
        int secondIndex;
        do {
            firstIndex = generateRandomInt(0, matrixSize - 1);
            secondIndex = generateRandomInt(0, matrixSize - 1);
        } while (abs(firstIndex - secondIndex) < 2);
        if (firstIndex > secondIndex) {
            int holder = firstIndex;
            firstIndex = secondIndex;
            secondIndex = holder;
        }

        Chromosome mutatedChromosome;

        // copy first part
        for (int i = 0; i < firstIndex; i++) {
            mutatedChromosome.genes.push_back(chromosome.genes[i]);
        }

        // reverse part of the path
        for (int i = firstIndex, j = secondIndex; i <= secondIndex; i++, j--) {
            mutatedChromosome.genes.push_back(chromosome.genes[j]);
        }

        // copy rest of the path
        for (int i = secondIndex + 1; i < matrixSize; i++) {
            mutatedChromosome.genes.push_back(chromosome.genes[i]);
        }


        mutatedChromosome.value = calculateChromosomeLength(mutatedChromosome, matrix);
        return mutatedChromosome;
    }

    Chromosome swapMutation(Chromosome chromosome, AdjacencyMatrix &matrix) {
        int firstIndex, secondIndex;
        do {
            firstIndex = generateRandomInt(0, matrixSize - 1);
            secondIndex = generateRandomInt(0, matrixSize - 1);
        } while (firstIndex == secondIndex);

        Chromosome mutatedChromosome = chromosome;
        std::swap(mutatedChromosome.genes[firstIndex], mutatedChromosome.genes[secondIndex]);

        mutatedChromosome.value = calculateChromosomeLength(mutatedChromosome, matrix);
        return mutatedChromosome;
    }

    Chromosome orderCrossover(Chromosome firstParent, Chromosome secondParent, int firstIndex, int secondIndex,
                              AdjacencyMatrix &matrix) {

        // Create a new chromosome and initialize all genes to -1
        Chromosome newChromosome;
        for (int i = 0; i < matrixSize; i++) {
            newChromosome.genes.push_back(-1);
        }

        // Vector to track which cities (genes) have already been added to the new chromosome
        vector<bool> taken(matrixSize, false);

        // Copy the segment between firstIndex and secondIndex from the first parent to the new chromosome
        for (int i = firstIndex; i < secondIndex; i++) {
            newChromosome.genes[i] = firstParent.genes[i];
            taken[newChromosome.genes[i]] = true; // Mark these genes as taken
        }

        // Start filling the rest of the new chromosome from the second parent
        int newChromosomePos = secondIndex;

        // Add genes from the second parent, starting from the secondIndex, wrapping around if necessary
        for (int i = secondIndex; i < matrixSize; i++) {
            if (!taken[secondParent.genes[i]]) {
                newChromosome.genes[newChromosomePos] = secondParent.genes[i];
                taken[secondParent.genes[i]] = true; // Mark this gene as taken
                if (newChromosomePos == matrixSize - 1)
                    newChromosomePos = (newChromosomePos + 1) % matrixSize; // Wrap around to the beginning
                else
                    newChromosomePos++;
            }
        }

        // Continue adding genes from the second parent, starting from the beginning up to firstIndex
        for (int i = 0; i <= firstIndex; i++) {
            if (!taken[secondParent.genes[i]]) {
                newChromosome.genes[newChromosomePos] = secondParent.genes[i];
                taken[secondParent.genes[i]] = true;
                if (newChromosomePos == matrixSize - 1)
                    newChromosomePos = (newChromosomePos + 1) % matrixSize;
                else
                    newChromosomePos++;
            }
        }

        // Fill the remaining slots with genes from the first parent, starting from secondIndex to the end
        for (int i = secondIndex; i < matrixSize; i++) {
            if (!taken[firstParent.genes[i]]) {
                newChromosome.genes[newChromosomePos] = firstParent.genes[i];
                taken[firstParent.genes[i]] = true;
                if (newChromosomePos == matrixSize - 1)
                    newChromosomePos = (newChromosomePos + 1) % matrixSize;
                else
                    newChromosomePos++;
            }
        }

        // Finally, add genes from the first parent, starting from the beginning up to firstIndex
        for (int i = 0; i <= firstIndex; i++) {
            if (!taken[firstParent.genes[i]]) {
                newChromosome.genes[newChromosomePos] = firstParent.genes[i];
                taken[firstParent.genes[i]] = true;
                if (newChromosomePos == matrixSize - 1)
                    newChromosomePos = (newChromosomePos + 1) % matrixSize;
                else
                    newChromosomePos++;
            }
        }

        newChromosome.value = calculateChromosomeLength(newChromosome, matrix);
        return newChromosome;
    }


    vector<Chromosome> generateStartingPopulation(AdjacencyMatrix &adjacencyMatrix) {
        vector<Chromosome> startingPopulation;
        for (int i = 0; i < populationSize; i++) {
            startingPopulation.push_back(generateRandomChromosome(adjacencyMatrix));

            int chromosomeLength = startingPopulation[i].value;
            if (chromosomeLength < bestChromosomeLength) {
                bestChromosomeLength = chromosomeLength;
                bestChromosome = startingPopulation[i];
            }
        }

        return startingPopulation;
    }

    void rankSelection() {
        sort(population.begin(), population.end(), [](const Chromosome &lhs, const Chromosome &rhs) {
            return lhs.value < rhs.value;
        });

        while (population.size() > populationSize) {
            population.pop_back();
        }
    }

    void geneticAlgorithm(AdjacencyMatrix &matrix) {
        start = steady_clock::now();
        steady_clock::duration duration;

        timeVector.clear();
        bladVector.clear();

        int crossoverFirstIndex;
        bool crossoverFirstChild;

        do {
            crossoverFirstChild = false;
            crossoverFirstIndex = 0;
            for (int i = 0; i < population.size(); i++) {
                int chance = generateRandomInt(1, 100);

                if (chance < crossingFactor) {
                    if (!crossoverFirstChild) {
                        crossoverFirstIndex = i;
                        crossoverFirstChild = true;
                    } else {
                        crossoverFirstChild = false;

                        // generate first and second index for crossover separated by at least two indices
                        int firstIndex, secondIndex;
                        do {
                            firstIndex = generateRandomInt(0, matrixSize - 1);
                            secondIndex = generateRandomInt(0, matrixSize - 1);
                        } while (abs(firstIndex - secondIndex) < 2);

                        if (firstIndex > secondIndex) {
                            std::swap(firstIndex, secondIndex);
                        }

                        Chromosome firstChildChromosome = orderCrossover(population[crossoverFirstIndex], population[i],
                                                                         firstIndex, secondIndex, matrix);

                        validateBestChromosome(firstChildChromosome);
                        population.push_back(firstChildChromosome);

                        Chromosome secondChildChromosome = orderCrossover(population[i], population[crossoverFirstIndex],
                                                                          firstIndex, secondIndex, matrix);

                        validateBestChromosome(secondChildChromosome);
                        population.push_back(secondChildChromosome);
                    }
                } else if (chance < crossingFactor + mutationFactor) {
                    Chromosome mutatedChromosome;
                    if (mutationStrategy == MutationStrategy::INVERSE) {
                        mutatedChromosome = inversionMutation(population[i], matrix);
                    } else {
                        mutatedChromosome = swapMutation(population[i], matrix);
                    }

                    validateBestChromosome(mutatedChromosome);
                    population.push_back(mutatedChromosome);
                }
            }

            rankSelection();

            duration = steady_clock::now() - start;
        } while (duration_cast<seconds>(duration).count() < static_cast<long long>(timeLimit) * 1);
    }

    void solve(AdjacencyMatrix &graphMatrix) {
        bestChromosomeLength = INT_MAX;
        matrixSize = graphMatrix.getSize();
        population = generateStartingPopulation(graphMatrix);

        cout << "Dlugosc najlepszego chromosomu przed algorytmem: " << bestChromosomeLength << endl;
        for (auto city : bestChromosome.genes) {
            std::cout << city << " -> ";
        }
        std::cout << bestChromosome.genes[0] << std::endl;
        geneticAlgorithm(graphMatrix);
        cout << "Dlugosc najlepszego chromosomu po algorytmie: " << bestChromosomeLength << endl;
        for (auto city : bestChromosome.genes) {
            std::cout << city << " -> ";
        }
        std::cout << bestChromosome.genes[0] << std::endl;
//
//        cout << "Czas potrzebny na znalezienie rozwiazania: " << timeToFindBest / 1000000 << "s" << endl;
//        bladWzgledny = abs(bestChromosomeLength - opt) / (double) opt * 100;
//        cout << "Blad wzgledny " << bladWzgledny << "%" << endl;
    }
};


#endif //PEA_GENETIC_H
