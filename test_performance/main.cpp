#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// prints to csv files size, density, type, time
int main() {
    vector<int> densities({20, 60, 99});
    vector<int> sampleSizes({10, 25, 50, 65, 75, 90, 100});

    cout.precision(30);
}

void runSample(vector<int> densities, vector<int> sampleSizes) {
    ofstream file;
    file.precision(17);
//    SampleTSP tspTest;
    file.open("sample.csv");
    for (auto dens : densities)
        for (auto sample : sampleSizes) {
//            tspTest.runKruskalTest(sample, dens);
//            std::cout << sample << "," << dens << "," << "matrix," << tspTest.getMatrixResult() << "\n";
//            std::cout << sample << "," << dens << "," << "list," << tspTest.getListResult() << "\n";
//            file << fixed << sample << "," << dens << "," << "matrix," << tspTest.getMatrixResult() << "\n";
//            file << fixed << sample << "," << dens << "," << "list," << tspTest.getListResult() << "\n";
        }
    file.close();
}
