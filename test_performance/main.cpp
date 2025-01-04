#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "utils/Utils.h"
#include "algorithms/Dynamic.h"
#include "algorithms/BruteForce.h"
#include "algorithms/BranchAndBound.h"
#include "algorithms/TabuSearch.h"
#include "algorithms/SimulatedAnnealing.h"

using namespace std;

void savePathToFile(std::vector<int> path, const std::string& filename) {
    ofstream outfile(filename);

    if (!outfile.is_open()) {
        std::cout << "Nie mozna otworzyc pliku." << endl;
        return;
    }

    outfile << path.size() << endl;
    for (int i : path) {
        outfile << i << endl;;
    }
    outfile << path[0] << endl;
    outfile.close();
}

AdjacencyMatrix* loadFromFileAtsp(string filename) {
    AdjacencyMatrix* matrixGraph;


    ifstream  myFile(filename);
    if (myFile.fail()) {
        cout << "Podano bledna sciezke do pliku!" << endl;
        exit(-1);
    }
    string line;

    getline(myFile, line);
    getline(myFile, line);
    getline(myFile, line);

    string temp;
    myFile >> temp;
    int tempInt;
    myFile >> tempInt;
    int numberOfCities = tempInt;

    getline(myFile, line);
    getline(myFile, line);
    getline(myFile, line);
    getline(myFile, line);

    matrixGraph = new AdjacencyMatrix(numberOfCities);
    for (int i = 0; i < numberOfCities; i++) {
        for (int j = 0; j < numberOfCities; j++) {
            int value;
            myFile >> value;
            matrixGraph->setEdge(i, j, value);
        }
    }

    myFile.close();

    return matrixGraph;
}

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


void runTSPerformance() {
    ofstream output_file("ts_results.csv");
    output_file.precision(17);
//    output_file << fixed << "sample" << "," << "algorithm" << ","  << "coolingRatio" << "," << "expTk" << "," << "timeLimit" << "," << "optimalSolutionTime" << "," << "optimalSolutionValue" << "," << "bestKnownSolution" << "," << "relativeError" << ",initialTemp" << "," << "finalTemp" << "\n";

    std::vector<std::string> graphFilenames = {"ftv55.atsp", "ftv170.atsp", "rbg358.atsp"};
    std::vector<int> bestKnownSolutions = {1608, 2755, 1163};
    std::vector<std::chrono::seconds> measuringTimes = {std::chrono::seconds(60), std::chrono::seconds(120), std::chrono::seconds(240)};
    std::vector<string> neighborhoodStrategies = {"swap", "insert", "reverse"};

    std::vector<int> bestPath;
    int bestSolution = INT_MAX;

    int iterations = 1;

    TabuSearch ts;

    for (int iter = 0; iter < iterations; iter++) {
        cout << "\n\nIteration: " << iter << endl;
        for (int i = 0; i < graphFilenames.size(); i++) {
            for (auto strategy : neighborhoodStrategies) {
                string instance = graphFilenames[i];
                chrono::seconds timeLimit = measuringTimes[i];

                AdjacencyMatrix* matrix = loadFromFileAtsp(instance);

                ts.setTimeLimit(timeLimit);

                if (strategy == "swap") {
                    ts.setStrategy(TabuSearch::SWAP);
                } else if (strategy == "insert") {
                    ts.setStrategy(TabuSearch::INSERT);
                } else {
                    ts.setStrategy(TabuSearch::REVERSE);
                }

                ts.solve(*matrix);

                if (ts.getShortestPathLength() < bestSolution) {
                    bestSolution = ts.getShortestPathLength();
                    bestPath = ts.bestPath;
                }

                double error = static_cast<double>(ts.getShortestPathLength() - bestKnownSolutions[i]) / bestKnownSolutions[i] * 100;

                cout        << "TS -- instance: " << instance << " -- strategy: " << strategy << " -- time limit (s): " << timeLimit.count() << "  -- found shortest path len: " << ts.getShortestPathLength() << " -- best known solution: " << bestKnownSolutions[i] << " -- error (%): " << fixed << setprecision(2) << error << "\n";
                output_file << "TS -- instance: " << instance << " -- strategy: " << strategy << " -- time limit (s): " << timeLimit.count() << "  -- found shortest path len: " << ts.getShortestPathLength() << " -- best known solution: " << bestKnownSolutions[i] << " -- error (%): " << fixed << setprecision(2) << error << "\n";
            }
        }
    }

    output_file.close();
}


void runGreedyTest() {
    std::vector<std::string> graphFilenames = {"ftv55.atsp", "ftv170.atsp", "rbg358.atsp"};
    std::vector<int> bestKnownSolutions = {1608, 2755, 1163};

    Greedy greedy;

    for (int i = 0; i < graphFilenames.size(); i++) {
        string instance = graphFilenames[i];
        AdjacencyMatrix* matrix = loadFromFileAtsp(instance);
        greedy.solve(*matrix);

        double error = static_cast<double>(greedy.getShortestPathLength() - bestKnownSolutions[i]) / bestKnownSolutions[i] * 100;

        cout << "Greedy -- instance: " << instance << " -- found shortest path len: " << greedy.getShortestPathLength() << " -- best known solution: " << bestKnownSolutions[i] << " -- error (%): " << fixed << setprecision(2) << error << "\n";
    }
}

void runSMPerformance() {
    ofstream output_file("sm_results.csv");
    output_file.precision(17);
    output_file << fixed << "sample" << "," << "algorithm" << ","  << "coolingRatio" << "," << "expTk" << "," << "timeLimit" << "," << "optimalSolutionTime" << "," << "optimalSolutionValue" << "," << "bestKnownSolution" << "," << "relativeError" << ",initialTemp" << "," << "finalTemp" << "\n";

    std::vector<std::string> graphFilenames = {"ftv55.atsp", "ftv170.atsp", "rbg358.atsp"};
    std::vector<int> bestKnownSolutions = {1608, 2755, 1163};
    std::vector<std::chrono::seconds> measuringTimes = {std::chrono::seconds(60), std::chrono::seconds(120), std::chrono::seconds(240)};
    std::vector<double> coolingRatios = {0.99999999, 0.99999975, 0.99999925};

    std::vector<int> bestPath;
    int bestSolution = INT_MAX;

    int iterations = 5;

    SimulatedAnnealing sm;

    for (int iter = 0; iter < iterations; iter++) {
        cout << "\n\nIteration: " << iter << endl;
        for (int i = 0; i < graphFilenames.size(); i++) {
            for (auto coolingRatio : coolingRatios) {
                string instance = graphFilenames[i];
                chrono::seconds timeLimit = measuringTimes[i];

                AdjacencyMatrix* matrix = loadFromFileAtsp(instance);

                cout << "SM - " << instance << "| time limit: " << timeLimit.count() << "s | cooling ratio: " << coolingRatio << endl;

                sm.setTimeLimit(timeLimit);
                sm.setCoolingRatio(coolingRatio);
                sm.solve(*matrix);

                if (sm.getShortestPathLength() < bestSolution) {
                    bestSolution = sm.getShortestPathLength();
                    bestPath = sm.path;
                }

                cout        << scientific << instance << "," << "SM"        << ","  <<  coolingRatio  << "," <<  exp(-1 / sm.finalTemperature) << "," <<  timeLimit.count() << "," << sm.optimalSolutionTime.count() << "," << sm.getShortestPathLength() << "," << bestKnownSolutions[i] << "," << abs(bestKnownSolutions[i] - sm.getShortestPathLength()) / bestKnownSolutions[i] << "," << sm.initialTemperature << "," << sm.finalTemperature << "\n";
                output_file << scientific << instance << "," << "SM"        << ","  <<  coolingRatio  << "," <<  exp(-1 / sm.finalTemperature) << "," <<  timeLimit.count() << "," << sm.optimalSolutionTime.count() << "," << sm.getShortestPathLength() << "," << bestKnownSolutions[i] << "," << abs(bestKnownSolutions[i] - sm.getShortestPathLength()) / bestKnownSolutions[i] << "," << sm.initialTemperature << "," << sm.finalTemperature << "\n";
            }
        }
    }

    output_file.close();
    savePathToFile(bestPath, "ftv55-bestpath.txt");
}


void runAssertion(int graphSize) {
    BruteForce bruteForce;
    BranchAndBound branchAndBound;
    Dynamic dynamic;
    TabuSearch tabuSearch;
    SimulatedAnnealing simAnnealing(0.999999, 15);

    int numberOfRuns = (graphSize >= 13) ? 10 : 100;

    for (int i = 0; i < numberOfRuns; i++) {
        AdjacencyMatrix* matrixGraph = new AdjacencyMatrix(graphSize);
        matrixGraph->generateRandomMatrix(0, 100);

        cout << "graphSize: " << graphSize << endl;

        auto matrixCopy1 = matrixGraph->copy();
        auto matrixCopy2 = matrixGraph->copy();
        auto matrixCopy3 = matrixGraph->copy();
        auto matrixCopy4 = matrixGraph->copy();
        auto matrixCopy5 = matrixGraph->copy();

        cout << "\n" << endl;

        branchAndBound.solve(*matrixCopy1);
        cout << "BaB " <<  " cost: " << branchAndBound.getShortestPathLength() << ", path: " << branchAndBound.toString() << endl;

        bruteForce    .solve(*matrixCopy2);
        cout << "B F " <<  " cost: " << bruteForce.getShortestPathLength()   << ", path: " << bruteForce.toString()  << endl;

        dynamic       .solve(*matrixCopy3);
        cout << "Dyn " <<  " cost: " << dynamic.getShortestPathLength()     << ", path: " << dynamic.toString()   << endl;

        tabuSearch    .solve(*matrixCopy4);
        cout << "Tab " <<  " cost: " << tabuSearch.getShortestPathLength()   << ", path: " << tabuSearch.toString()  << endl;

        simAnnealing  .solve( *matrixCopy5);
        cout << "Sim " <<  " cost: " << simAnnealing.getShortestPathLength()  << ", path: " << simAnnealing.toString() << endl;
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

//        long long bruteForceResult = runBruteForceTest(sample, dens);
        long long branchAndBoundResult = runBranchAndBoundTest(sample, dens);
        long long dynamicResult = runDynamicProgrammingTest(sample, dens);

//        cout                 << sample << "," << dens << ",BruteForce," << bruteForceResult << "\n";
        cout                 << sample << "," << dens << ",BranchAndBound," << branchAndBoundResult << "\n";
        cout                 << sample << "," << dens << ",Dynamic," << dynamicResult << "\n";

//        output_file << fixed << sample << "," << dens << ",BruteForce," << bruteForceResult << "\n";
        output_file << fixed << sample << "," << dens << ",BranchAndBound," << branchAndBoundResult << "\n";
        output_file << fixed << sample << "," << dens << ",Dynamic," << dynamicResult << "\n";
    }

    output_file.close();
}

int main() {
//    runSMPerformance();
    runTSPerformance();
//    runGreedyTest();

    return 0;
}
