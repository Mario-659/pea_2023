#include <iostream>

#include "graphs/AdjacencyMatrix.h"
#include "utils/Utils.h"
#include "stdexcept"

using namespace std;

// reads data from file as graph
void loadFromFileDir(string filename, bool directed=true);

AdjacencyMatrix* matrixGraph = nullptr;

void displayGraphs();

void startSPMenu() {
    matrixGraph = nullptr;

    string input;
    while(true){
        cout << R"(Wybierz opcje:
                   1. Wczytaj z pliku
                   2. Losowy graf
                   5. Wyswietl
                   6. Wroc)";
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
                int numV, dens;
                cout << "Podaj liczbe wierzcholkow: ";
                cin >> numV;
                cout << "Podaj gestosc: ";
                cin >> dens;
                utils::generateRandomDirectedGraphs(matrixGraph, numV, dens);
                displayGraphs();
                break;

            case 5:
                displayGraphs();
                break;
            case 6:
                // return to prev menu options
                return;
            default:
                cout << "Nieprawidlowy numer" << endl;
        }
    }
}

int main(){
    string input;
    do{
        cout << R"(Wybierz problem:
                  1. Najkrotsza droga w grafie
                  2. Wyjdz)";
        cout << "\nInput: ";
        cin >> input;
        if(input == "1") {
            startSPMenu();
        }
    } while(input != "2");
    return 0;
}

void loadFromFileDir(string filename, bool directed) {
    vector<vector<int>> nums = utils::readFromFile(filename);
    if (nums.size() < 2) throw std::invalid_argument("invalid path");
    vector<int> firstLine = nums[0];
    int size = firstLine[0];
    nums.erase(nums.begin()); // remove line where the size is defined
    matrixGraph = new AdjacencyMatrix(size);
    for (int i=0; i<nums.size(); i++) {
        for (int j=0; j<nums.size(); j++) {
            if (directed)
                matrixGraph->addEdge(i, j, nums[i][j]);
            else
                matrixGraph->addUndEdge(i, j, nums[i][j]);
        }
    }
}

void displayGraphs() {
    cout << matrixGraph->toString() << endl;
}

