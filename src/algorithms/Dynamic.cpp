//#include "Dynamic.h"
//
//#include <iostream>
//#include <cmath>
//
//using namespace std;
//
//
//void Dynamic::solve(AdjacencyMatrix& graph) {
//    this->size = graph.getSize();
//    this->routes.resize(this->size, vector<int>(this->size, 0));
//
//    vector<vector<int>> pathCostMemory(this->size, vector<int>((1<<this->size)-1, -1));
//    this->shortestPathLength = getMinWeight(pathCostMemory, 1, 0);
//    this->bestPath = findOptimalPath(pathCostMemory, {});
//}
//
//int Dynamic::getMinWeight(vector<vector<int>> &pathCostMemory, int mask, int startCity) {
//    if(mask == (1<<this->size)-1) return routes[startCity][0];
//    if(pathCostMemory[startCity][mask]!=-1) return pathCostMemory[startCity][mask];
//    int cost = INT_MAX;
//
//    for(int i = 0; i < this->size; i++){
//        if((mask & (1 << i)) == 0 && routes[startCity][i] != INT_MAX){
//            int newCostForGivenMask = routes[startCity][i] + getMinWeight(pathCostMemory, (mask ^ (1 << i)), i);
//            if(cost > newCostForGivenMask){
//                cost = newCostForGivenMask;
//            }
//        }
//    }
//
//    pathCostMemory[startCity][mask] = cost;
//    return cost;
//}
//
//vector<int> Dynamic::findOptimalPath(vector<vector<int>> pathCostMemory, vector<int> path){
//    int startNode = 0;
//    int mask = 1;
//    int startCity = startNode;
//    int totalCost = 0;
//    path.push_back(startCity);
//    for(int j=0; j<this->size-1; j++){
//        int newCity = 0;
//        int cost=INT_MAX;
//        for(int i=0; i<this->size; i++){
//            if(i!=startNode && (mask&(1<<i))==0){
//                if(routes[startCity][i]+pathCostMemory[i][mask|(1<<i)]<=cost){
//                    newCity=i;
//                    cost = routes[startCity][i]+pathCostMemory[i][mask|(1<<i)];
//                }
//            }
//        }
//        totalCost += routes[startCity][newCity];
//        path.push_back(newCity);
//        mask = mask^(1<<newCity);
//        startCity = newCity;
//    }
//    totalCost += routes[startCity][startNode];
//    cout<<"Minimal weight (path finder): "<<totalCost<<endl;
//    path.push_back(startNode);
//    return path;
//}
//
//std::string Dynamic::toString() {
//    std::string path = "";
//    for (int i = 0; i < bestPath.size() - 1; i++) {
//        path += std::to_string(bestPath[i]) + " -> ";
//    }
//
//    return path += std::to_string(bestPath.back());
//}
