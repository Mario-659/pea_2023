#include <iostream>

#include "graphs/AdjacencyMatrix.h"
#include "utils/Utils.h"

using namespace std;

// reads data from file as undirected graph
void loadFromFileUnd(string filename);
// reads data from file as directed graph
void loadFromFileDir(string filename);

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
                cout << "Podaj nazwe pliku";
                cin >> input;
                loadFromFileDir(input);
                displayGraphs();
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

void loadFromFileUnd(string filename) {
    vector<vector<int>> nums = utils::readFromFile(filename);
    vector<int> firsLine = nums[0];
    int validLines = firsLine[0];
    int size = firsLine[1];
    matrixGraph = new AdjacencyMatrix(size);
    for (int i=1; i<=validLines; i++) {
        matrixGraph->addUndEdge(nums[i][0], nums[i][1], nums[i][2]);
    }
}

void loadFromFileDir(string filename) {
    vector<vector<int>> nums = utils::readFromFile(filename);
    vector<int> firsLine = nums[0];
    int validLines = firsLine[0];
    int size = firsLine[1];
    matrixGraph = new AdjacencyMatrix(size);
    for (int i=1; i<=validLines; i++) {
        matrixGraph->addEdge(nums[i][0], nums[i][1], nums[i][2]);
    }
}

void displayGraphs() {
    cout << matrixGraph->toString() << endl;
}

