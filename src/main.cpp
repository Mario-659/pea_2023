#include <iostream>

#include "graphs/AdjacencyList.h"
#include "graphs/AdjacencyMatrix.h"
#include "algorithms/Prim.h"

#include "utils/Utils.h"

using namespace std;

void loadFromFile(string filename);

AdjacencyList* listGraph = nullptr;
AdjacencyMatrix* matrixGraph = nullptr;

void displayGraphs();

void randGraphs(int size, int density);

void startMSTMenu() {
    listGraph = nullptr;
    matrixGraph = nullptr;
    Prim prim;

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
                loadFromFile(input);
                displayGraphs();
                break;
            case 2:
                int numV, dens;
                cout << "Podaj liczbe wierzcholkow: ";
                cin >> numV;
                cout << "Podaj gestosc: ";
                cin >> dens;
                randGraphs(numV, dens);
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
                  1. Minimalne drzewo rozpinajace (MST)
                  2. Wyjdz)";
        cout << "\nInput: ";
        cin >> input;
        if(input == "1") {
            startMSTMenu();
        }
    } while(input != "2");
    return 0;
}

void loadFromFile(string filename) {
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

void randGraphs(int size, int density) {
    listGraph = new AdjacencyList(size);
    matrixGraph = new AdjacencyMatrix(size);

    // create tree (weight from 1 to 100)
    for (int i=0; i<size-1; i++) {
        int weight = (rand() % 100) + 1;
        listGraph->addEdge(i, i+1, weight);
        matrixGraph->addEdge(i, i+1, weight);
    }

    // https://www.baeldung.com/cs/graphs-max-number-of-edges
    int maxEdges = size * (size-1) / 2;
    int availableEdges = maxEdges - size - 1;
    int edgesToAdd = int(0.01 * density * maxEdges);
    if (availableEdges < edgesToAdd) return;

    edgesToAdd -= size - 1;

    // adding the rest of the edges
    for (int i=0; i<edgesToAdd; i++) {
        int weight = (rand() % 100) + 1;
        int start = rand() % size;
        int end = rand() % size;

        if(matrixGraph->getEdge(start, end) == NO_EDGE) {
            matrixGraph->addEdge(start, end, weight);
            listGraph->addEdge(start, end, weight);
        }
    }
//    matrixGraph = new AdjacencyMatrix(size);
//    listGraph = new AdjacencyList(size);
//
//    //Maksymalna ilość wierzchołków to suma ciągu arytmetycznego an = n.
//    int maxEdges = static_cast<int>(density / 100.0f * (((size + 1) / 2.0f) * size));
//    int edgeCount = 0;
//    //Generujemy drzewo rozpinające.
//    for (int i = 0; i < size - 1; i++)
//    {
//        //Dla problemu minimalnego drzewa rozpinającego krawędzie są nieskierowane.
//        int weight = (rand() % maxEdges) + 1;
//        matrixGraph->addEdge(i, i + 1, weight);
////        matrix->addEdge(i + 1, i, weight);
//
//        listGraph->addEdge(i, i + 1, weight);
////        list->addEdge(i + 1, i, weight);
//        edgeCount++;
//    }
//
//    //Dodajemy pozostałe krawędzie (zawsze zostanie wygenerowane chociaż drzewo rozpinające).
//    while (edgeCount < maxEdges)
//    {
//        int start = rand() % size;
//        int end = rand() % size;
//        int weight = (rand() % maxEdges) + 1;
//
//        if (matrixGraph->getEdge(start, end) == 0)
//        {
//            matrix->addEdge(start, end, weight);
//            matrix->addEdge(end, start, weight);
//
//            list->addEdge(start, end, weight);
//            list->addEdge(end, start, weight);
//            edgeCount++;
//        }
//    }
}
