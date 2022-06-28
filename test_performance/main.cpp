#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "MSTTest.h"
#include "PathTest.h"

#define HEADER "graphSize,density,time\n"

using namespace std;

void runDijkstraTest(vector<int> densities, vector<int> sampleSizes);
void runBellmanTest(vector<int> densities, vector<int> sampleSizes);
void runPrimTest(vector<int> densities, vector<int> sampleSizes);
void runKruskalTest(vector<int> densities, vector<int> sampleSizes);


// prints to csv files size, density, type, time
int main() {
    vector<int> densities({20, 60, 99});
    vector<int> sampleSizes({10, 25, 50, 65, 75, 90, 100});

    cout.precision(30);

    runDijkstraTest(densities, sampleSizes);
    cout << "\n\nDijkstra test completed\n\n";

    runKruskalTest(densities, sampleSizes);
    cout << "\n\nKruskal test completed\n\n";

    runPrimTest(densities, sampleSizes);
    cout << "\n\nPrim test completed\n\n";

    runBellmanTest(densities, sampleSizes);
    cout << "\n\nBellman test completed\n\n";
}

void runKruskalTest(vector<int> densities, vector<int> sampleSizes) {
    ofstream file;
    file.precision(17);
    MSTTest mstTest;
    file.open("kruskal.csv");
    for (auto dens : densities)
        for (auto sample : sampleSizes) {
            mstTest.runKruskalTest(sample, dens);
            std::cout << sample << "," << dens << "," << "matrix," << mstTest.getMatrixResult() << "\n";
            std::cout << sample << "," << dens << "," << "list," << mstTest.getListResult() << "\n";
            file << fixed << sample << "," << dens << "," << "matrix," << mstTest.getMatrixResult() << "\n";
            file << fixed << sample << "," << dens << "," << "list," << mstTest.getListResult() << "\n";
        }
    file.close();
}

void runPrimTest(vector<int> densities, vector<int> sampleSizes) {
    ofstream file;
    file.precision(17);
    MSTTest mstTest;
    file.open("prim.csv");
    for (auto dens : densities)
        for (auto sample : sampleSizes) {
            mstTest.runPrimTest(sample, dens);
            std::cout << sample << "," << dens << "," << "matrix," << mstTest.getMatrixResult() << "\n";
            std::cout << sample << "," << dens << "," << "list," << mstTest.getListResult() << "\n";
            file << fixed << sample << "," << dens << "," << "matrix," << mstTest.getMatrixResult() << "\n";
            file << fixed << sample << "," << dens << "," << "list," << mstTest.getListResult() << "\n";
        }
    file.close();
}

void runBellmanTest(vector<int> densities, vector<int> sampleSizes) {
    ofstream file;
    file.precision(17);
    PathTest pathTest;
    file.open("belmann.csv");
    for (auto dens : densities)
        for (auto sample : sampleSizes) {
            pathTest.runBellmanTest(sample, dens);
            std::cout << sample << "," << dens << "," << "matrix," << pathTest.getMatrixResult() << "\n";
            std::cout << sample << "," << dens << "," << "list," << pathTest.getListResult() << "\n";
            file << fixed << sample << "," << dens << "," << "matrix," << pathTest.getMatrixResult() << "\n";
            file << fixed << sample << "," << dens << "," << "list," << pathTest.getListResult() << "\n";
        }
    file.close();
}

void runDijkstraTest(vector<int> densities, vector<int> sampleSizes) {
    ofstream file;
    file.precision(17);
    PathTest pathTest;
    file.open("dijkstra.csv");
    for (auto dens : densities)
        for (auto sample : sampleSizes) {
            pathTest.runDijkstraTest(sample, dens);
            std::cout << sample << "," << dens << "," << "matrix," << pathTest.getMatrixResult() << "\n";
            std::cout << sample << "," << dens << "," << "list," << pathTest.getListResult() << "\n";
            file << fixed << sample << "," << dens << "," << "matrix," << pathTest.getMatrixResult() << "\n";
            file << fixed << sample << "," << dens << "," << "list," << pathTest.getListResult() << "\n";
        }
    file.close();
}
