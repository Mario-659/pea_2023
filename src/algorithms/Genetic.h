#ifndef PEA_GENETIC_H
#define PEA_GENETIC_H

#include <set>
#include "TSPSolver.h"
#include "graphs/AdjacencyMatrix.h"
#include <chrono>
#include <vector>
#include <algorithm>

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

    //kryterium stopu
    int stop;

    //wspolczynniki
    int crossingFactor,mutationFactor;

    int populationSize;
    vector<Chromosome> population;

    //zmienne potrzebne do wykresow
    vector<long long> timeVector;
    vector<double> bladVector;

    vector<long long> bestTimeVector;
    vector<double> bestBladVector;
    
    int matrixSize; 

    double bladWzgledny;
    int opt = 1608;

    int calculateChromosomeLength(Chromosome chromosome, AdjacencyMatrix& adjacencyMatrix){
        int length = 0;
        for (int i = 0; i < matrixSize-1; i++) {
            length += adjacencyMatrix.getEdgeWeight(chromosome.genes[i], chromosome.genes[i+1]);
        }
        length += adjacencyMatrix.getEdgeWeight(chromosome.genes[matrixSize - 1], chromosome.genes[0]);
        return length;
    }

    int generateRandomInt(int min, int max) {
        return rand() % (max - min + 1) + min;
    }

    Chromosome generateRandomChromosome(AdjacencyMatrix& adjacencyMatrix) {
        bool* visited = new bool[matrixSize];
        Chromosome chromosome;

        int starting = generateRandomInt(0,matrixSize-1);

        for (int i = 0; i < matrixSize; i++) {
            visited[i] = false;
        }
        visited[starting] = true;
        chromosome.genes.push_back(starting);

        int nextCity;
        for (int i = 0; i < matrixSize - 1; i++) {
            do {
                nextCity = generateRandomInt(0,matrixSize-1);
            } while (visited[nextCity]);
            visited[nextCity] = true;
            chromosome.genes.push_back(nextCity);
        }
        delete[] visited;
        chromosome.value = calculateChromosomeLength(chromosome, adjacencyMatrix);

        std::set<int> mySet(chromosome.genes.begin(), chromosome.genes.end());
        if(chromosome.genes.size() == mySet.size()){
            return chromosome;
        }else{
            cout << "zle" << endl;
            throw exception();
        }
    }

    Chromosome inversionMutation(Chromosome chromosome, AdjacencyMatrix& matrix){
        int firstIndex;
        int secondIndex;
        do{
            firstIndex = generateRandomInt(0,matrixSize-1);
            secondIndex = generateRandomInt(0,matrixSize-1);
        }while(abs(firstIndex-secondIndex) < 2);
        if(firstIndex > secondIndex){
            int holder = firstIndex;
            firstIndex = secondIndex;
            secondIndex = holder;
        }

        Chromosome mutatedChromosome;
        for(int i = 0;  i < firstIndex; i++){
            mutatedChromosome.genes.push_back(chromosome.genes[i]);
        }

        for(int i = firstIndex, j =  secondIndex ;  i <= secondIndex; i++,j--){
            mutatedChromosome.genes.push_back(chromosome.genes[j]);
        }

        for(int i = secondIndex+1; i < matrixSize;i++){
            mutatedChromosome.genes.push_back(chromosome.genes[i]);
        }
        mutatedChromosome.value = calculateChromosomeLength(mutatedChromosome, matrix);


        set<int> mySet(mutatedChromosome.genes.begin(), mutatedChromosome.genes.end());
        if(mutatedChromosome.genes.size() == mySet.size()){
            return mutatedChromosome;
        }else{
            cout << "zle " << mutatedChromosome.genes.size() << " " << mySet.size() <<  endl;
            throw exception();
        }

    }

    Chromosome orderCrossover(Chromosome firstParent, Chromosome secondParent, int firstIndex, int secondIndex, AdjacencyMatrix& matrix){

        Chromosome newChromosome;
        for(int i = 0; i < matrixSize; i++){
            newChromosome.genes.push_back(-1);
        }

        vector<bool> taken(matrixSize,false);

        for(int i = firstIndex; i < secondIndex;i++){
            newChromosome.genes[i] = firstParent.genes[i];
            taken[newChromosome.genes[i]] = true;
        }


        int newChromosomePos = secondIndex;

        for(int i = secondIndex; i < matrixSize; i++){
            if(!taken[secondParent.genes[i]]){
                newChromosome.genes[newChromosomePos] = secondParent.genes[i];
                taken[secondParent.genes[i]] = true;
                if(newChromosomePos == matrixSize-1)
                    newChromosomePos = (newChromosomePos + 1) % matrixSize;
                else
                    newChromosomePos++;
            }
        }

        for(int i = 0; i <= firstIndex; i++){
            if(!taken[secondParent.genes[i]]){
                newChromosome.genes[newChromosomePos] = secondParent.genes[i];
                taken[secondParent.genes[i]] = true;
                if(newChromosomePos == matrixSize-1)
                    newChromosomePos = (newChromosomePos + 1) % matrixSize;
                else
                    newChromosomePos++;
            }
        }

        for(int i = secondIndex; i < matrixSize; i++){
            if(!taken[firstParent.genes[i]]){
                newChromosome.genes[newChromosomePos] = firstParent.genes[i];
                taken[firstParent.genes[i]] = true;
                if(newChromosomePos == matrixSize-1)
                    newChromosomePos = (newChromosomePos + 1) % matrixSize;
                else
                    newChromosomePos++;
            }
        }

        for(int i = 0; i <= firstIndex; i++) {
            if (!taken[firstParent.genes[i]]) {
                newChromosome.genes[newChromosomePos] = firstParent.genes[i];
                taken[firstParent.genes[i]] = true;
                if(newChromosomePos == matrixSize-1)
                    newChromosomePos = (newChromosomePos + 1) % matrixSize;
                else
                    newChromosomePos++;
            }
        }

        newChromosome.value = calculateChromosomeLength(newChromosome, matrix);

        set<int> mySet(newChromosome.genes.begin(), newChromosome.genes.end());
        if(newChromosome.genes.size() == mySet.size()){
            return newChromosome;
        }else{
            throw exception();
        }

    }

    vector<Chromosome> generateStartingPopulation(AdjacencyMatrix& adjacencyMatrix){
        vector<Chromosome> startingPopulation;
        for(int i = 0; i < populationSize; i++){
            startingPopulation.push_back(generateRandomChromosome(adjacencyMatrix));
            int chromosomeLength = calculateChromosomeLength(startingPopulation[i], adjacencyMatrix);
            if(chromosomeLength < bestChromosomeLength){
                bestChromosomeLength = chromosomeLength;
                bestChromosome = startingPopulation[i];
            }
        }
        return startingPopulation;
    }

    void selection(){
        sort(population.begin(), population.end(), [](const Chromosome& lhs, const Chromosome& rhs) {
            return lhs.value < rhs.value;
        });

        while (population.size() > populationSize){
            population.pop_back();
        }
    }

    void geneticAlgorithm(AdjacencyMatrix& matrix) {
        steady_clock::time_point start = steady_clock::now();
        steady_clock::duration duration;

        timeVector.clear();
        bladVector.clear();

        int crossoverStatus, crossoverFirstIndex;

        do {
            crossoverStatus = 0;
            crossoverFirstIndex = 0;
            for(int i = 0; i < population.size(); i++){
                int chance = generateRandomInt(1,100);

                if(chance < crossingFactor){
                    if(crossoverStatus == 0){
                        crossoverStatus = 1;
                        crossoverFirstIndex = i;
                    }else{
                        crossoverStatus = 0;
                        int firstIndex;
                        int secondIndex;
                        do{
                            firstIndex = generateRandomInt(0,matrixSize-1);
                            secondIndex = generateRandomInt(0,matrixSize-1);
                        }while(abs(firstIndex-secondIndex) < 2);
                        if(firstIndex > secondIndex){
                            int holder = firstIndex;
                            firstIndex = secondIndex;
                            secondIndex = holder;
                        }

                        Chromosome firstNewChromosome = orderCrossover(population[crossoverFirstIndex],population[i],firstIndex,secondIndex, matrix);

                        if(firstNewChromosome.value < bestChromosomeLength){
                            duration = steady_clock::now() - start;
                            timeToFindBest = duration_cast<microseconds>(duration).count();

                            timeVector.push_back(timeToFindBest);
                            bladVector.push_back(100.0*(bestChromosomeLength - opt) / (double)opt);

                            bestChromosome = firstNewChromosome;
                            bestChromosomeLength = firstNewChromosome.value;
                        }
                        population.push_back(firstNewChromosome);

                        Chromosome secondNewChromosome = orderCrossover(population[i],population[crossoverFirstIndex],firstIndex,secondIndex, matrix);
                        if(secondNewChromosome.value < bestChromosomeLength){
                            duration = steady_clock::now() - start;
                            timeToFindBest = duration_cast<microseconds>(duration).count();

                            timeVector.push_back(timeToFindBest);
                            bladVector.push_back(100.0*(bestChromosomeLength - opt) / (double)opt);

                            bestChromosome = secondNewChromosome;
                            bestChromosomeLength = secondNewChromosome.value;
                        }
                        population.push_back(secondNewChromosome);
                    }
                }else if(chance < crossingFactor + mutationFactor){
                    Chromosome mutatedChromosome = inversionMutation(population[i], matrix);
                    if(mutatedChromosome.value < bestChromosomeLength){
                        duration = steady_clock::now() - start;
                        timeToFindBest = duration_cast<microseconds>(duration).count();

                        timeVector.push_back(timeToFindBest);
                        bladVector.push_back(100.0*(bestChromosomeLength - opt) / (double)opt);

                        bestChromosome = mutatedChromosome;
                        bestChromosomeLength = mutatedChromosome.value;
                    }
                    population.push_back(mutatedChromosome);
                }
            }
            selection();

            duration = steady_clock::now() - start;
        } while (duration_cast<seconds>(duration).count() < static_cast<long long>(stop) * 1);
    }

    void solve(AdjacencyMatrix& graphMatrix) {
        bestChromosomeLength = INT_MAX;
        matrixSize = graphMatrix.getSize();
        population = generateStartingPopulation(graphMatrix);

        cout << "Dlugosc najlepszego chromosomu przed algorytmem: " << bestChromosomeLength << endl;

        for (int i = 0; i < graphMatrix.getSize(); i++) {
            cout << bestChromosome.genes[i] << "->";
        }
        cout << bestChromosome.genes[graphMatrix.getSize()] << endl;

        geneticAlgorithm(graphMatrix);

        cout << "Dlugosc najlepszego chromosomu po algorytmie: " << bestChromosomeLength << endl;
        for (int i = 0; i < graphMatrix.getSize(); i++) {
            cout << bestChromosome.genes[i] << "->";
        }
        cout << bestChromosome.genes[graphMatrix.getSize()] << endl;
        cout << "Czas potrzebny na znalezienie rozwiazania: " << timeToFindBest/1000000 << "s" << endl;
        bladWzgledny = abs(bestChromosomeLength - opt) / (double)opt * 100;
        cout << "Blad wzgledny " << bladWzgledny << "%" << endl;
    }
};


#endif //PEA_GENETIC_H
