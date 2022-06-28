#include <iostream>

#include "graphs/AdjacencyList.h"
#include "graphs/AdjacencyMatrix.h"
#include "algorithms/Prim.h"
#include "algorithms/Kruskal.h"
#include "algorithms/Dijkstra.h"
#include "algorithms/BellmanFord.h"
#include "utils/Utils.h"

using namespace std;

// reads data from file as undirected graph
void loadFromFileUnd(string filename);
// reads data from file as directed graph
void loadFromFileDir(string filename);

AdjacencyList* listGraph = nullptr;
AdjacencyMatrix* matrixGraph = nullptr;

void displayGraphs();

void startSPMenu() {
    listGraph = nullptr;
    matrixGraph = nullptr;
    Dijkstra dijkstra;
    BellmanFord bellman;

    string input;
    while(true){
        cout << R"(Wybierz opcje:
                   1. Wczytaj z pliku
                   2. Losowy graf
                   3. Dijkstra
                   4. Bellman Ford
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
                utils::generateRandomDirectedGraphs(matrixGraph, listGraph, numV, dens);
                displayGraphs();
                break;
            case 3:
                cout << "Podaj poczatkowy wierzcholek: ";
                cin >> numV;
                dijkstra.shortestPath(*listGraph, numV);
                cout << "Graph as a list representation:" << endl;
                cout << dijkstra.toString() << endl;

                dijkstra.shortestPath(*matrixGraph, numV);
                cout << "Graph as a matrix representation:" << endl;
                cout << dijkstra.toString() << endl;
                break;

            case 4:
                cout << "Podaj poczatkowy wierzcholek: ";
                cin >> numV;
                bellman.shortestPath(*listGraph, numV);
                cout << "Graph as a list representation:" << endl;
                cout << bellman.toString() << endl;

                dijkstra.shortestPath(*matrixGraph, numV);
                cout << "Graph as a matrix representation:" << endl;
                cout << bellman.toString() << endl;
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

void startMSTMenu() {
    listGraph = nullptr;
    matrixGraph = nullptr;
    Prim prim;
    Kruskal kruskal;

    string input;
    while(true){
        cout << R"(Wybierz opcje:
                   1. Wczytaj z pliku
                   2. Losowy graf
                   3. Prim
                   4. Kruskal
                   5. Wyswietl
                   6. Wroc)";
        cout << "\nInput: ";
        cin >> input;
        int option = stoi(input);
        switch (option) {
            case 1:
                cout << "Podaj nazwe pliku";
                cin >> input;
                loadFromFileUnd(input);
                displayGraphs();
                break;
            case 2:
                int numV, dens;
                cout << "Podaj liczbe wierzcholkow: ";
                cin >> numV;
                cout << "Podaj gestosc: ";
                cin >> dens;
                utils::generateRandomUndirectedGraphs(matrixGraph, listGraph, numV, dens);
                displayGraphs();
                break;
            case 3:
                prim.mst(*listGraph);
                cout << "Graph as a list representation:" << endl;
                cout << prim.toString() << endl;

                prim.mst(*matrixGraph);
                cout << "Graph as a matrix representation:" << endl;
                cout << prim.toString() << endl;
                break;

            case 4:
                kruskal.mst(*listGraph);
                cout << "Graph as a list representation:" << endl;
                cout << prim.toString() << endl;

                kruskal.mst(*matrixGraph);
                cout << "Graph as a matrix representation:" << endl;
                cout << prim.toString() << endl;
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
                  1. Minimalne drzewo rozpinajace
                  2. Najkrotsza droga w grafie
                  3. Wyjdz)";
        cout << "\nInput: ";
        cin >> input;
        if(input == "1") {
            startMSTMenu();
        }
        else if(input == "2") {
            startSPMenu();
        }
    } while(input != "3");
    return 0;
}

void loadFromFileUnd(string filename) {
    vector<vector<int>> nums = utils::readFromFile(filename);
    vector<int> firsLine = nums[0];
    int validLines = firsLine[0];
    int size = firsLine[1];
    listGraph = new AdjacencyList(size);
    matrixGraph = new AdjacencyMatrix(size);
    for (int i=1; i<=validLines; i++) {
        listGraph->addUndEdge(nums[i][0], nums[i][1], nums[i][2]);
        matrixGraph->addUndEdge(nums[i][0], nums[i][1], nums[i][2]);
    }
}

void loadFromFileDir(string filename) {
    vector<vector<int>> nums = utils::readFromFile(filename);
    vector<int> firsLine = nums[0];
    int validLines = firsLine[0];
    int size = firsLine[1];
    listGraph = new AdjacencyList(size);
    matrixGraph = new AdjacencyMatrix(size);
    for (int i=1; i<=validLines; i++) {
        listGraph->addEdge(nums[i][0], nums[i][1], nums[i][2]);
        matrixGraph->addEdge(nums[i][0], nums[i][1], nums[i][2]);
    }
}

void displayGraphs() {
    cout << listGraph->toString() << endl;
    cout << matrixGraph->toString() << endl;
}

