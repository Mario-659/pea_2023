#include <iostream>
#include <chrono>

#include "graphs/AdjacencyMatrix.h"
#include "utils/Utils.h"
#include "stdexcept"
#include "algorithms/BruteForce.h"
#include "algorithms/BranchAndBound.h"
#include "algorithms/Dynamic.h"

using namespace std;

// reads data from file as graph, assumes first line in file stands for graph size
void loadFromFileDir(string filename);

AdjacencyMatrix* matrixGraph = nullptr;

void displayGraphs();

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
    startSPMenu();
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

void displayGraphs() {
    cout << matrixGraph->toString() << endl;
}

