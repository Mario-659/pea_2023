#include "TabuSearch.h"


using namespace std;

void TabuSearch::readDataFromFile(string fileName) {
    ifstream input_file(fileName);
    if(!input_file.is_open()){
        cout<<"Nie udalo sie otworzyc pliku!"<<endl;
        return;
    }
    input_file>>verticesNumber;
    vector<vector<int>> newRoutes(verticesNumber, vector<int>(verticesNumber, 0));
    for(int i=0; i<verticesNumber; i++){
        for(int j=0;j<verticesNumber;j++){
            input_file>>newRoutes[i][j];
        }
    }

    routes = newRoutes;
    cout<<verticesNumber<<endl;
    input_file.close();
    for(int i=0; i<verticesNumber; i++){
        for(int j=0;j<verticesNumber;j++){
            cout<<newRoutes[i][j]<<" ";
        }
        cout<<endl;
    }

}

int TabuSearch::getPathCost(vector<int> pathInstance) {
    int cost = 0;
    for(int i=1; i<pathInstance.size(); i++){
        cost += routes[pathInstance[i-1]][pathInstance[i]];
    }
    cost += routes[pathInstance[pathInstance.size()-1]][pathInstance[0]];
    return cost;
}

vector<int> TabuSearch::getDefaultTabuPath(){
    vector<int> newPath = {};
    for(int i=0; i<verticesNumber; i++){
        newPath.push_back(i);
    }
    return newPath;
}


vector<int> TabuSearch::generateRandomPath(){
    std::random_device rd;
    std::mt19937 generator(rd());
    vector<int> randomPath = getDefaultTabuPath();
    shuffle(randomPath.begin(), randomPath.end(), generator);
    return randomPath;
}

void TabuSearch::solveTSPUsingTabuSearch() {
    vector<vector<int>> tabuTable(verticesNumber, vector<int>(verticesNumber, 0));
    vector<int> currentPath = getDefaultTabuPath();
    int currentCost = getPathCost(currentPath);
    int bestCost = currentCost;
    vector<int> bestPath = currentPath;
    auto start = std::chrono::high_resolution_clock::now();
    int iterations = verticesNumber;
    int punishment = 10*verticesNumber;
    vector<int> measureTimes;
    while(true){
        currentPath = generateRandomPath();
        for(int i=0; i<iterations; i++){
            int bestNextCost = INT_MAX;
            int bestK, bestL = -1;
            for(int k = 0; k<verticesNumber-1; k++){
                for(int l=k+1; l<verticesNumber; l++){
                    swap(currentPath[k], currentPath[l]);
                    currentCost = getPathCost(currentPath);
                    if(currentCost<bestNextCost && tabuTable[k][l]==0){
                        bestNextCost = currentCost;
                        bestK = k;
                        bestL = l;
                    }
                    swap(currentPath[k], currentPath[l]);
                }
            }
            swap(currentPath[bestK], currentPath[bestL]);
            tabuTable[bestK][bestL] = punishment;
            if(bestNextCost<bestCost){
                bestCost = getPathCost(currentPath);
                bestPath = currentPath;
                auto bestTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = bestTime - start;
            }
            for(int k=0; k<verticesNumber; k++){
                for(int l=0; l<verticesNumber; l++){
                    if(tabuTable[k][l]>0) tabuTable[k][l]-=1;
                }
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        if(elapsed.count() > timeLimit){
            break;
        }
    }
    cout<<"Best cost: "<<bestCost<<endl;
    for(int i: bestPath){
        cout<<i<<" ";
    }
}
