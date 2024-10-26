#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "utils/Utils.h"
#include "algorithms/BruteForce.h"

using namespace std;

long long runBruteForceTest(int graphSize, int density) {
    long long matrixResult = 0;

    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;

    BruteForce bruteForce;

    int numberOfRuns = 50;

    for (int i=0; i<numberOfRuns; i++) {
        AdjacencyMatrix* matrixGraph = new AdjacencyMatrix(graphSize);

        utils::generateRandomUndirectedGraphs(matrixGraph, graphSize, density);

        cout << "\rGraph size: " << graphSize << ", density: " << density << ", iteration: " << i;

        t1 = chrono::high_resolution_clock::now();

        bruteForce.findShortestPath(*matrixGraph);

        t2 = chrono::high_resolution_clock::now();
        auto result = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        matrixResult += result;
    }

    return matrixResult / numberOfRuns;
}

void runSample(vector<int> densities, vector<int> sampleSizes) {
    ofstream output_file;
    output_file.precision(17);
    output_file.open("sample.csv");

//    cout                 << "sample" << "," << "density" << "," << "averageTimeInNanoseconds" << "\n";
    output_file << fixed << "sample" << "," << "density" << "," << "averageTimeInNanoseconds" << "\n";

    for (auto dens : densities)
        for (auto sample : sampleSizes) {
            long long result = runBruteForceTest(sample, dens);

//            cout                 << sample << "," << dens << "," << result << "\n";
            output_file << fixed << sample << "," << dens << "," << result << "\n";
        }
    output_file.close();
}

// prints to csv files size, density, type, time
int main() {
    vector<int> densities({20, 60, 99});
    vector<int> sampleSizes({4, 5, 6, 7, 8, 9, 10, 11});

    cout.precision(30);

    runSample(densities, sampleSizes);
}
