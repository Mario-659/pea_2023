#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "utils/Utils.h"
#include "algorithms/Dynamic.h"
#include "algorithms/BruteForce.h"
#include "algorithms/BranchAndBound.h"

using namespace std;

long long runBruteForceTest(int graphSize, int density) {
    long long matrixResult = 0;
    chrono::high_resolution_clock::time_point t1, t2;
    BruteForce bruteForce;

    int numberOfRuns = (graphSize >= 13) ? 10 : 100;

    for (int i = 0; i < numberOfRuns; i++) {
        AdjacencyMatrix* matrixGraph = new AdjacencyMatrix(graphSize);
        matrixGraph->generateRandomMatrix(1, 100);

        cout << "\rBranch and Bound - Graph size: " << graphSize << ", density: " << density << ", iteration: " << i + 1;

        t1 = chrono::high_resolution_clock::now();
        bruteForce.solve(*matrixGraph);
        t2 = chrono::high_resolution_clock::now();

        auto result = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        matrixResult += result;

        delete matrixGraph;
    }

    return matrixResult / numberOfRuns;
}

long long runBranchAndBoundTest(int graphSize, int density) {
    long long matrixResult = 0;
    chrono::high_resolution_clock::time_point t1, t2;
    BranchAndBound branchAndBound;

    int numberOfRuns = (graphSize >= 13) ? 10 : 100;

    for (int i = 0; i < numberOfRuns; i++) {
        AdjacencyMatrix* matrixGraph = new AdjacencyMatrix(graphSize);
        matrixGraph->generateRandomMatrix(1, 100);

        cout << "\rBruteForce - Graph size: " << graphSize << ", density: " << density << ", iteration: " << i + 1;

        t1 = chrono::high_resolution_clock::now();
        branchAndBound.solve(*matrixGraph);
        t2 = chrono::high_resolution_clock::now();

        auto result = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        matrixResult += result;

        delete matrixGraph;
    }

    return matrixResult / numberOfRuns;
}


void runAssertion(int graphSize) {
    BruteForce bruteForce;
    BranchAndBound branchAndBound;
    Dynamic dynamic;

    int numberOfRuns = (graphSize >= 13) ? 10 : 100;

    for (int i = 0; i < numberOfRuns; i++) {
        AdjacencyMatrix* matrixGraph = new AdjacencyMatrix(graphSize);
        matrixGraph->generateRandomMatrix(0, 100);

        cout << "graphSize: " << graphSize << endl;

        auto matrixCopy1 = matrixGraph->copy();
        auto matrixCopy2 = matrixGraph->copy();
        auto matrixCopy3 = matrixGraph->copy();

        branchAndBound.solve(*matrixCopy1);
        bruteForce.solve(*matrixCopy2);
        dynamic.solve(*matrixCopy3);

        cout << "\n" << endl;
        cout << "BaB " <<  " cost: " << branchAndBound.getShortestPathLength() << endl;
        cout << "B F " <<  " cost: " << bruteForce.getShortestPathLength() << endl;
        cout << "Dyn " <<  " cost: " << dynamic.getShortestPathLength() << endl;
    }
}

long long runDynamicProgrammingTest(int graphSize, int density) {
    long long matrixResult = 0;
    chrono::high_resolution_clock::time_point t1, t2;
    Dynamic dynamic;

    int numberOfRuns = (graphSize >= 13) ? 10 : 100;

    for (int i = 0; i < numberOfRuns; i++) {
        AdjacencyMatrix* matrixGraph = new AdjacencyMatrix(graphSize);
        matrixGraph->generateRandomMatrix(1, 100);

        cout << "\rDynamic Programming - Graph size: " << graphSize << ", density: " << density << ", iteration: " << i + 1;

        t1 = chrono::high_resolution_clock::now();
        dynamic.solve(*matrixGraph);
        t2 = chrono::high_resolution_clock::now();

        auto result = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        matrixResult += result;

        delete matrixGraph;
    }

    return matrixResult / numberOfRuns;
}

void runSample(vector<int> sampleSizes) {
    ofstream output_file("sample.csv");
    output_file.precision(17);

    cout                 << "sample" << "," << "density" << "," << "algorithm" << "," << "averageTimeInNanoseconds" << "\n";
    output_file << fixed << "sample" << "," << "density" << "," << "algorithm" << "," << "averageTimeInNanoseconds" << "\n";

    int dens = 100;
    for (auto sample : sampleSizes) {
//        runAssertion(sample);

        long long bruteForceResult = runBruteForceTest(sample, dens);
        long long branchAndBoundResult = runBranchAndBoundTest(sample, dens);
        long long dynamicResult = runDynamicProgrammingTest(sample, dens);

        cout                 << sample << "," << dens << ",BruteForce," << bruteForceResult << "\n";
        cout                 << sample << "," << dens << ",BranchAndBound," << branchAndBoundResult << "\n";
        cout                 << sample << "," << dens << ",Dynamic," << dynamicResult << "\n";

        output_file << fixed << sample << "," << dens << ",BruteForce," << bruteForceResult << "\n";
        output_file << fixed << sample << "," << dens << ",BranchAndBound," << branchAndBoundResult << "\n";
        output_file << fixed << sample << "," << dens << ",Dynamic," << dynamicResult << "\n";
    }

    output_file.close();
}

int main() {
    vector<int> sampleSizes({4, 5, 6, 7, 8, 9, 10, 11, 12, 13});

    cout.precision(30);
    runSample(sampleSizes);
//    runAssertion(10);

    return 0;
}
