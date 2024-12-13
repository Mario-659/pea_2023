#include <iostream>
#include <chrono>

#include "graphs/AdjacencyMatrix.h"
#include "utils/Utils.h"
#include "stdexcept"
#include "algorithms/BruteForce.h"
#include "algorithms/BranchAndBound.h"
#include "algorithms/Dynamic.h"
#include "algorithms/TabuSearch.h"
#include "algorithms/Greedy.h"
#include "algorithms/SimulatedAnnealing.h"

using namespace std;

// reads data from file as graph, assumes first line in file stands for graph size
void loadFromFileDir(string filename);
void loadFromFileAtsp(string filename);

AdjacencyMatrix* matrixGraph = nullptr;

void displayGraphs();

void startTSMenu() {
    matrixGraph = nullptr;
    chrono::high_resolution_clock::time_point t1, t2;
    TabuSearch ts;
    SimulatedAnnealing sm;
    string input;
    while(true){
        cout << R"(Wybierz opcje:
                   1. Wczytaj z pliku
                   2. Wyswietl
                   3. Podaj wartosc kryterium stopu
                   4. Podaj definicje sasiedztwa dla tabu search
                   5. Uruchom algorytm tabu search
                   6. Podaj wspolczynnik zmiany temperatury
                   7. Uruchom algorytm symulowanego wyzarzania
                   8. Oblicz metoda zachlanna
                   9. Zapisz sciezke do pliku .txt
                   10. Wczytaj sciezke z pliku .txt i oblicz droge
                   0. Zakoncz)";
        cout << "\nInput: ";
        cin >> input;
        int option = stoi(input);
        switch (option) {
            case 1:
                cout << "Podaj nazwe pliku: ";
                cin >> input;
                try {
                    loadFromFileAtsp(input);
                    std::cout << "\n";
                    displayGraphs();
                } catch (std::invalid_argument &e) {
                    cout << "Nie znaleziono pliku\n";
                }
                break;
            case 2:
                displayGraphs();
                break;
            case 3:
                cout << "Podaj kryterium stopu w sekundach: ";
                cin >> input;
                ts.setTimeLimit(std::chrono::seconds(std::stoi(input)));
                sm.setTimeLimit(std::chrono::seconds(std::stoi(input)));
                break;
            case 4:
                cout << "Podaj definicje sasiedztwa (1 - swap, 2 - inverse, 3 - insert): ";
                cin >> input;
                switch (stoi(input)) {
                    case 1:
                        ts.setStrategy(TabuSearch::SWAP);
                        break;
                    case 2:
                        ts.setStrategy(TabuSearch::REVERSE);
                        break;
                    case 3:
                        ts.setStrategy(TabuSearch::INSERT);
                        break;
                }
                break;
            case 5:
                {
                    t1 = chrono::high_resolution_clock::now();
                    ts.solve(*matrixGraph);
                    t2 = chrono::high_resolution_clock::now();
                    auto result = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
                    std::cout << "\nShortest path: " << ts.toString() << "\n" <<
                              "Koszt sciezki: " << ts.getShortestPathLength() << "\n" <<
                              "Czas wykonania w nanosekundach: " << result << std::endl;
                }
                break;
            case 6:
                cout << "Podaj wspolczynnik zmiany temperatury: ";
                cin >> input;
                sm.setCoolingRatio(stod(input));
                break;
            case 7:
            {
                t1 = chrono::high_resolution_clock::now();
                sm.solve(*matrixGraph);
                t2 = chrono::high_resolution_clock::now();
                auto result = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
                std::cout << "\nShortest path: " << sm.toString() << "\n" <<
                          "Koszt sciezki: " << sm.getShortestPathLength() << "\n" <<
                          "Czas wykonania w nanosekundach: " << result << std::endl;
            }
                break;
            case 8:
            {
                    Greedy greedy;
                    t1 = chrono::high_resolution_clock::now();
                    greedy.solve(*matrixGraph);
                    t2 = chrono::high_resolution_clock::now();
                    auto result = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
                    std::cout << "\nShortest path: " << greedy.toString() << "\n" <<
                              "Koszt sciezki: " << greedy.getShortestPathLength() << "\n" <<
                              "Czas wykonania w nanosekundach: " << result << std::endl;
                }
                break;
            case 9:
                return;
            case 10:
                return;
            case 0:
                return;
            default:
                cout << "Nieprawidlowy numer" << endl;
        }
    }
}

void startSPMenu() {
    matrixGraph = nullptr;
    string input;
    chrono::high_resolution_clock::time_point t1, t2;
    while(true){
        cout << R"(Wybierz opcje:
                   1. Wczytaj z pliku
                   2. Losowy graf
                   5. Wyswietl
                   6. Brute force
                   7. Branch and Bound
                   8. Dynamic
                   9. Zakoncz)";
        cout << "\nInput: ";
        cin >> input;
        int option = stoi(input);
        switch (option) {
            case 1:
                cout << "Podaj nazwe pliku: ";
                cin >> input;
                try {
                    loadFromFileDir(input);
                    std::cout << "\n";
                    displayGraphs();
                } catch (std::invalid_argument &e) {
                    cout << "Nie znaleziono pliku\n";
                }
                break;
            case 2:
                int numV;
                cout << "Podaj liczbe wierzcholkow: ";
                cin >> numV;

                matrixGraph = new AdjacencyMatrix(numV);
                matrixGraph->generateRandomMatrix(0, 100);
                displayGraphs();
                break;

            case 5:
                displayGraphs();
                break;
            case 6:
            {
                BruteForce bruteForce;
                t1 = chrono::high_resolution_clock::now();
                bruteForce.solve(*matrixGraph);
                t2 = chrono::high_resolution_clock::now();
                auto result = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
                std::cout << "\nShortest path: " << bruteForce.toString() << "\n" <<
                          "Koszt sciezki: " << bruteForce.getShortestPathLength() << "\n" <<
                "Czas wykonania w nanosekundach: " << result << std::endl;
            }
            break;
            case 7:
            {
                BranchAndBound branchAndBound;
                t1 = chrono::high_resolution_clock::now();
                branchAndBound.solve(*matrixGraph);
                t2 = chrono::high_resolution_clock::now();
                auto result = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
                std::cout << "\nShortest path: " << branchAndBound.toString() << "\n" <<
                          "Koszt sciezki: " << branchAndBound.getShortestPathLength() << "\n" <<
                "Czas wykonania w nanosekundach: " << result << std::endl;
            }
            break;
            case 8:
            {
                Dynamic dynamic;
                t1 = chrono::high_resolution_clock::now();
                dynamic.solve(*matrixGraph);
                t2 = chrono::high_resolution_clock::now();
                auto result = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
                std::cout << "\nShortest path: " << dynamic.toString() << "\n" <<
                          "Koszt sciezki: " << dynamic.getShortestPathLength() << "\n" <<
                "Czas wykonania w nanosekundach: " << result << std::endl;
            }
            break;
            case 9:
                return;
            default:
                cout << "Nieprawidlowy numer" << endl;
        }
    }
}

int main(){
//    startSPMenu();
    startTSMenu();
    return 0;
}

void loadFromFileDir(string filename) {
    vector<vector<int>> nums = utils::readFromFile(filename);

    if (nums.size() < 2)
        throw std::invalid_argument("invalid path");

    int size = nums[0][0];

    // remove line where the size is defined
    nums.erase(nums.begin());

    matrixGraph = new AdjacencyMatrix(size);
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < nums.size(); j++) {
                matrixGraph->setEdge(i, j, nums[i][j]);
        }
    }
}

void loadFromFileAtsp(string filename) {
    ifstream  myFile(filename);
    if (myFile.fail()) {
        cout << "Podano bledna sciezke do pliku!" << endl;
        return;
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
}

void displayGraphs() {
    cout << matrixGraph->toString() << endl;
}

