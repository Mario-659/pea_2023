#include "SimulatedAnnealing.h"

void SimulatedAnnealing::readDataFromFile(string fileName) {
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

int SimulatedAnnealing::getPathCost(vector<int> pathInstance) {
    int cost = 0;
    for(int i=1; i<pathInstance.size(); i++){
        cost += routes[pathInstance[i-1]][pathInstance[i]];
    }
    cost += routes[pathInstance[pathInstance.size()-1]][pathInstance[0]];
    return cost;
}

vector<int> SimulatedAnnealing::getDefaultPath(int range){
    vector<int> newPath = {};
    for(int i=0; i<range; i++){
        newPath.push_back(i);
    }
    return newPath;
}

vector<int> SimulatedAnnealing::swapElementsInPath(int range, vector<int> oldPath){
    vector<int> newPath = std::move(oldPath);
    int firstCityToSwap = rand()%range;
    int secondCityToSwap =rand()%range;
    while(firstCityToSwap==secondCityToSwap){
        secondCityToSwap = rand()%range;
    }
    iter_swap(newPath.begin() + firstCityToSwap, newPath.begin() + secondCityToSwap);
    return newPath;
}

void SimulatedAnnealing::solveTSPUsingSimulatedAnnealing() {
    temperature = getInitialTemperature();
    path = getDefaultPath(verticesNumber);
    cout<<"Temperatura poczatkowa: "<<temperature<<endl;
    auto start = std::chrono::high_resolution_clock::now();
    int optimalCost= getPathCost(path);
    auto const seed = 123456789;
    std::mt19937 urbg {seed};
    vector<int> measureTimes;
    while(true){
        vector<int>newPath = swapElementsInPath(verticesNumber, path);
        int newCost = getPathCost(newPath);
        if(newCost<optimalCost){
            path = newPath;
            optimalCost = newCost;
            auto bestTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = bestTime - start;

        } else {
            double probability = exp(-abs(optimalCost-newCost)/temperature);
            double uniformDistributionRandomValue = uniform_real_distribution<double>(0, 1)(urbg);
            if(probability > uniformDistributionRandomValue){
                path = newPath;
                optimalCost = newCost;
            }
        }
        temperature *= coolingRatio;
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        int timeNow = int(elapsed.count());
        if(std::find(measureTimes.begin(), measureTimes.end(), timeNow) == measureTimes.end() && timeNow%20==0){
            measureTimes.push_back(timeNow);
            cout<<optimalCost<<endl;
        }
        if(elapsed.count() > timeLimit){
            break;
        }
    }
    cout<<"path: "<<endl;
    for(int i : path){
        cout<<i<<" ";
    }
    cout<<path[0]<<endl;
    cout<<"Total cost: "<<getPathCost(path)<<endl;
    cout<<"Final temperature: "<<temperature<<endl;
    cout<<endl<<endl;
}

double SimulatedAnnealing::getInitialTemperature() {
    int iterations = 10000;
    vector<int> samplePath = getDefaultPath(verticesNumber);
    vector<int> oldPath;
    double averageCost = 0;
    for(int i=0;i<iterations; i++){
        oldPath = samplePath;
        samplePath = swapElementsInPath(verticesNumber, samplePath);
        averageCost += abs(getPathCost(samplePath)- getPathCost(oldPath));
    }
    return abs((averageCost/iterations)/log(0.99));
}
