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
#include "algorithms/Genetic.h"

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
    output_file << fixed << "sample" << "," << "timeLimit" << "," << "strategy" << "optimalSolutionTime" << "," << "optimalSolutionValue" << "," << "bestKnownSolution" << "," << "relativeError" << "\n";

    std::vector<std::string> graphFilenames = {"ftv55.atsp", "ftv170.atsp", "rbg358.atsp"};
    std::vector<int> bestKnownSolutions = {1608, 2755, 1163};
    std::vector<std::chrono::seconds> measuringTimes = {std::chrono::seconds(60), std::chrono::seconds(120), std::chrono::seconds(240)};
    std::vector<string> neighborhoodStrategies = {"swap", "insert", "reverse"};

    std::vector<int> bestPathFtv55;
    std::vector<int> bestPathFtv170;
    std::vector<int> bestPathRgb358;

    int bestSolutionFtv55 = INT_MAX;
    int bestSolutionFtv170 = INT_MAX;
    int bestSolutionRgb358 = INT_MAX;

    int iterations = 10;
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

                if (instance == graphFilenames[0]) {
                    if (ts.getShortestPathLength() < bestSolutionFtv55) {
                        bestSolutionFtv55 = ts.getShortestPathLength();
                        bestPathFtv55 = ts.bestPath;
                    }
                } else if (instance == graphFilenames[2]) {
                    if (ts.getShortestPathLength() < bestSolutionFtv170) {
                        bestSolutionFtv170 = ts.getShortestPathLength();
                        bestPathFtv170 = ts.bestPath;
                    }
                } else {
                    if (ts.getShortestPathLength() < bestSolutionRgb358) {
                        bestSolutionRgb358 = ts.getShortestPathLength();
                        bestPathRgb358 = ts.bestPath;
                    }
                }

                double error = static_cast<double>(ts.getShortestPathLength() - bestKnownSolutions[i]) / bestKnownSolutions[i] * 100;

//                cout        << "TS -- instance: " << instance << " -- strategy: " << strategy << " -- time limit (s): " << timeLimit.count() << "  -- found shortest path len: " << ts.getShortestPathLength() << " -- best known solution: " << bestKnownSolutions[i] << " -- error (%): " << fixed << setprecision(2) << error << "\n";
//                output_file << "TS -- instance: " << instance << " -- strategy: " << strategy << " -- time limit (s): " << timeLimit.count() << "  -- found shortest path len: " << ts.getShortestPathLength() << " -- best known solution: " << bestKnownSolutions[i] << " -- error (%): " << fixed << setprecision(2) << error << "\n";

                output_file << fixed << instance << "," << timeLimit.count() << "," << strategy << ts.optimalSolutionTime.count() << "," << ts.getShortestPathLength() << "," << bestKnownSolutions[i] << "," << error << "\n";
            }
        }
    }

    output_file.close();

    savePathToFile(bestPathFtv55, "ftv55-bestpath.txt");
    savePathToFile(bestPathFtv170, "ftv170-bestpath.txt");
    savePathToFile(bestPathRgb358, "rgb358-bestpath.txt");
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

void runGeneticInvPerformance() {
    ofstream output_file("inv_genetic_results.csv");
    output_file.precision(17);
    cout.precision(17);

    output_file << fixed << "populationSize" << ";" << "timeLimit" << ";" << "optimalSolutionTime(s)" << ";" << "optimalSolutionValue" << ";" << "bestKnownSolution" << ";" << "relativeError" << "\n";
    cout        << fixed << "populationSize" << ";" << "timeLimit" << ";" << "optimalSolutionTime(s)" << ";" << "optimalSolutionValue" << ";" << "bestKnownSolution" << ";" << "relativeError" << "\n";

    std::string graphFilename = "ftv170.atsp";
    int bestKnownSolution = 2755;
    int timeLimit = 180;
    AdjacencyMatrix* matrix = loadFromFileAtsp(graphFilename);

    std::vector<int> populationSizes = {500, 1000, 2000};
    std::vector<int> bestPathFtv170;

    std::vector<double> errorsOfBestSolution;
    std::vector<long long> timesOfBestSolution;

    int bestSolution = INT_MAX;
    int iterations = 10;

    Genetic genetic;
    genetic.crossingFactor = 80;
    genetic.mutationFactor = 1;
    genetic.timeLimit = timeLimit;
    genetic.opt = bestKnownSolution;

    for (auto populationSize : populationSizes) {
        bestSolution = INT_MAX;

        for (int iter = 0; iter < iterations; iter++) {
            cout << "population: " << populationSize << " -- iteration: " << iter + 1 << " -- out of " << iterations << endl;

            genetic.mutationStrategy = Genetic::INVERSE;
            genetic.populationSize = populationSize;
            genetic.solve(*matrix);
            cout << "done";

            double error = static_cast<double>(genetic.bestChromosomeLength - bestKnownSolution) / bestKnownSolution * 100;
            output_file << fixed << populationSize << ";" << timeLimit << ";" << genetic.timeToFindBest << ";" << genetic.bestChromosomeLength << ";" << bestKnownSolution << ";" << error << "\n";
            cout        << fixed << populationSize << ";" << timeLimit << ";" << genetic.timeToFindBest << ";" << genetic.bestChromosomeLength << ";" << bestKnownSolution << ";" << error << "\n";

            if (genetic.bestChromosomeLength < bestSolution) {
                bestSolution = genetic.bestChromosomeLength;

                errorsOfBestSolution.clear();
                for (auto measuredError : genetic.relativeErrors) {
                    errorsOfBestSolution.push_back(measuredError);
                }

                timesOfBestSolution.clear();
                for (auto timeMeasurement : genetic.newSolutionFoundTimes) {
                    timesOfBestSolution.push_back(timeMeasurement);
                }

                bestPathFtv170 = genetic.bestChromosome.genes;
            }
        }

        ofstream out_file_times("inv" + to_string(populationSize) + "_genetic_time_vector" + to_string(bestSolution) + ".csv");
        out_file_times << "time(microseconds);error\n";
        std::cout << "timesOfBestSolution.size()" << timesOfBestSolution.size() << endl;

        for (int i = 0; i < timesOfBestSolution.size(); i++) {
            out_file_times << timesOfBestSolution[i] << ";" << errorsOfBestSolution[i] << endl;
        }
        out_file_times.close();

        savePathToFile(bestPathFtv170, "inv" + to_string(populationSize) + "_genetic-ftv170-bestpath.txt");
    }

    output_file.close();
}

void runGeneticSwapPerformance() {
    ofstream output_file("swap_genetic_results.csv");
    output_file.precision(17);
    cout.precision(17);

    output_file << fixed << "populationSize" << ";" << "timeLimit" << ";" << "optimalSolutionTime(s)" << ";" << "optimalSolutionValue" << ";" << "bestKnownSolution" << ";" << "relativeError" << "\n";
    cout        << fixed << "populationSize" << ";" << "timeLimit" << ";" << "optimalSolutionTime(s)" << ";" << "optimalSolutionValue" << ";" << "bestKnownSolution" << ";" << "relativeError" << "\n";

    std::string graphFilename = "ftv170.atsp";
    int bestKnownSolution = 2755;
    int timeLimit = 180;
    AdjacencyMatrix* matrix = loadFromFileAtsp(graphFilename);

    std::vector<int> populationSizes = {500, 1000, 2000};
    std::vector<int> bestPathFtv170;

    std::vector<double> errorsOfBestSolution;
    std::vector<long long> timesOfBestSolution;

    int bestSolution = INT_MAX;
    int iterations = 10;

    Genetic genetic;
    genetic.crossingFactor = 80;
    genetic.mutationFactor = 1;
    genetic.timeLimit = timeLimit;
    genetic.opt = bestKnownSolution;

    for (auto populationSize : populationSizes) {
        bestSolution = INT_MAX;

        for (int iter = 0; iter < iterations; iter++) {
            cout << "population: " << populationSize << " -- iteration: " << iter + 1 << " -- out of " << iterations << endl;

            genetic.mutationStrategy = Genetic::SWAP;
            genetic.populationSize = populationSize;
            genetic.solve(*matrix);
            cout << "done";

            double error = static_cast<double>(genetic.bestChromosomeLength - bestKnownSolution) / bestKnownSolution * 100;
            output_file << fixed << populationSize << ";" << timeLimit << ";" << genetic.timeToFindBest << ";" << genetic.bestChromosomeLength << ";" << bestKnownSolution << ";" << error << "\n";
            cout        << fixed << populationSize << ";" << timeLimit << ";" << genetic.timeToFindBest << ";" << genetic.bestChromosomeLength << ";" << bestKnownSolution << ";" << error << "\n";

            if (genetic.bestChromosomeLength < bestSolution) {
                bestSolution = genetic.bestChromosomeLength;

                errorsOfBestSolution.clear();
                for (auto measuredError : genetic.relativeErrors) {
                    errorsOfBestSolution.push_back(measuredError);
                }

                timesOfBestSolution.clear();
                for (auto timeMeasurement : genetic.newSolutionFoundTimes) {
                    timesOfBestSolution.push_back(timeMeasurement);
                }

                bestPathFtv170 = genetic.bestChromosome.genes;
            }
        }

        ofstream out_file_times("swap" + to_string(populationSize) + "_genetic_time_vector" + to_string(bestSolution) + ".csv");
        out_file_times << "time(microseconds);error\n";
        std::cout << "timesOfBestSolution.size()" << timesOfBestSolution.size() << endl;

        for (int i = 0; i < timesOfBestSolution.size(); i++) {
            out_file_times << timesOfBestSolution[i] << ";" << errorsOfBestSolution[i] << endl;
        }
        out_file_times.close();

        savePathToFile(bestPathFtv170, "swap" + to_string(populationSize) + "_genetic-ftv170-bestpath.txt");
    }

    output_file.close();
}

void runSMPerformance() {
    ofstream output_file("sm_results.csv");
    output_file.precision(17);
    cout.precision(17);

    output_file << fixed << "sample" << ";" << "coolingRatio" << ";" << "expTk" << ";" << "timeLimit" << ";" << "optimalSolutionTime(s)" << ";" << "optimalSolutionValue" << ";" << "bestKnownSolution" << ";" << "relativeError" << ";initialTemp" << ";" << "finalTemp" << "\n";

    std::vector<std::string> graphFilenames = {"ftv55.atsp", "ftv170.atsp", "rbg358.atsp"};
    std::vector<int> bestKnownSolutions = {1608, 2755, 1163};
    std::vector<std::chrono::seconds> measuringTimes = {std::chrono::seconds(60), std::chrono::seconds(120), std::chrono::seconds(240)};
    std::vector<double> coolingRatios = {0.9999999, 0.99999995, 0.999999925};

    std::vector<int> bestPathFtv55;
    std::vector<int> bestPathFtv170;
    std::vector<int> bestPathRgb358;

    int bestSolutionFtv55 = INT_MAX;
    int bestSolutionFtv170 = INT_MAX;
    int bestSolutionRgb358 = INT_MAX;

    int iterations = 10;

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

                if (instance == graphFilenames[0]) {
                    if (sm.getShortestPathLength() < bestSolutionFtv55) {
                        bestSolutionFtv55 = sm.getShortestPathLength();
                        bestPathFtv55 = sm.path;
                    }
                } else if (instance == graphFilenames[1]) {
                    if (sm.getShortestPathLength() < bestSolutionFtv170) {
                        bestSolutionFtv170 = sm.getShortestPathLength();
                        bestPathFtv170 = sm.path;
                    }
                } else {
                    if (sm.getShortestPathLength() < bestSolutionRgb358) {
                        bestSolutionRgb358 = sm.getShortestPathLength();
                        bestPathRgb358 = sm.path;
                    }
                }


                double error = static_cast<double>(sm.getShortestPathLength() - bestKnownSolutions[i]) / bestKnownSolutions[i] * 100;

                cout        << fixed << instance << ";" <<  coolingRatio  << ";" <<  exp(-1.0 / (1.0 * sm.finalTemperature)) << ";" <<  timeLimit.count() << ";" << sm.optimalSolutionTime.count() << ";" << sm.getShortestPathLength() << ";" << bestKnownSolutions[i] << ";" << error << ";" << sm.initialTemperature << ";" << sm.finalTemperature << "\n";
                output_file << fixed << instance << ";" <<  coolingRatio  << ";" <<  exp(-1.0 / (1.0 * sm.finalTemperature)) << ";" <<  timeLimit.count() << ";" << 1.0 * sm.optimalSolutionTime.count() / 1000 << ";" << sm.getShortestPathLength() << ";" << bestKnownSolutions[i] << ";" << error << ";" << sm.initialTemperature << ";" << sm.finalTemperature << "\n";
            }
        }
    }

    output_file.close();

    savePathToFile(bestPathFtv55, "sm-ftv55-bestpath.txt");
    savePathToFile(bestPathFtv170, "sm-ftv170-bestpath.txt");
    savePathToFile(bestPathRgb358, "sm-rgb358-bestpath.txt");
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
//    runTSPerformance();
//    runGreedyTest();
    runGeneticInvPerformance();
    runGeneticSwapPerformance();

    return 0;
}
