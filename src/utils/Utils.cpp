#include "Utils.h"

using namespace std;

vector<string> split(string text, const string& delimiter) {
    vector<string> arr;
    size_t pos = 0;
    string token;

    while ((pos = text.find(delimiter)) != string::npos) {
        token = text.substr(0, pos);
        if(!token.empty()) arr.push_back(token);
        text.erase(0, pos + delimiter.length());
    }
    if(!text.empty()) arr.push_back(text);

    reverse(arr.begin(), arr.end());
    return arr;
}

vector<int> extractInt(vector<string> params){
    vector<int> nums;

    for (auto p : params) {
        nums.push_back(stoi(p));
    }

    reverse(nums.begin(), nums.end());
    return nums;
}

vector<vector<int>> utils::readFromFile(string filename) {
    vector<vector<int>> lines;

    ifstream input(filename, fstream::in);
    if(!input.good()) return lines;

    string line;
    while (getline(input, line)) {
        if (line.empty()) break;
        auto params = split(line, " ");
        auto nums = extractInt(params);
        lines.push_back(nums);
    }
    return lines;
}

vector<int> utils::getRandVect(int size, int min, int max) {
    random_device rd;
    mt19937_64 generator(rd());
    uniform_int_distribution<int> distribution(min, max);
    vector<int> values;
    for (int i=0; i<size; i++) {
        values.push_back(distribution(generator));
    }
    return values;
}

void utils::generateRandomUndirectedGraphs(AdjacencyMatrix *&matrix, int size, int density) {
    matrix = new AdjacencyMatrix(size);

    // https://www.baeldung.com/cs/graphs-max-number-of-edges
    int maxEdges = size * (size-1) / 2;

    if (density == 99) {
        random_device rd;
        mt19937_64 generator(rd());

        // 1% to remove
        int numOfEdgesToRemove = int(0.01 * maxEdges);
        uniform_int_distribution<int> distribution(0, maxEdges-1);
        set<int> toRemove;
        while (numOfEdgesToRemove > 0) {
            toRemove.insert(distribution(generator));
            numOfEdgesToRemove--;
        }
        // random p
        vector<int> weights = getRandVect(maxEdges, 1, 100);
        // 99% density
        int counter = 0;
        for (int i=0; i<size; i++) {
            for(int j=i+1; j<size; j++) {
                // if index in toRemove omit
                if(toRemove.find(counter) != toRemove.end()) {
                    counter++;
                    continue;
                }
                matrix->addUndEdge(i, j, weights[counter]);
                counter++;
            }
        }
        return;
    }

    // create tree (weight from 1 to 100)
    for (int i=0; i<size-1; i++) {
        int weight = (rand() % 100) + 1;
        matrix->addUndEdge(i, i + 1, weight);
    }

    int edgesToAdd = int(0.01 * density * maxEdges);

    // adding the rest of the edges
    while (edgesToAdd > 0) {
        int weight = (rand() % 100) + 1;
        int start = rand() % size;
        int end = rand() % size;

        if(matrix->getEdge(start, end) == NO_EDGE) {
            matrix->addUndEdge(start, end, weight);
            edgesToAdd--;
        }
    }
}

void utils::generateRandomDirectedGraphs(AdjacencyMatrix*& matrix, int size, int density) {
    matrix = new AdjacencyMatrix(size);

    // https://www.baeldung.com/cs/graphs-max-number-of-edges
    int maxEdges = size * (size-1);

    if (density == 99) {
        random_device rd;
        mt19937_64 generator(rd());

        // 1% to remove
        int numOfEdgesToRemove = int(0.01 * maxEdges);
        uniform_int_distribution<int> distribution(0, maxEdges-1);
        set<int> toRemove;
        while (numOfEdgesToRemove > 0) {
            toRemove.insert(distribution(generator));
            numOfEdgesToRemove--;
        }
        // random p
        vector<int> weights = getRandVect(size*size, 1, 100);
        // 99% density
        int counter = 0;
        for (int i=0; i<size; i++) {
            for(int j=0; j<size; j++) {
                // don't point to itself
                if(i == j) continue;
                // if index in toRemove omit
                if(toRemove.find(counter) != toRemove.end()) {
                    counter++;
                    continue;
                }
                matrix->addEdge(i, j, weights[counter]);
                counter++;
            }
        }
        return;
    }

    // create tree (weight from 1 to 100)
    for (int i=0; i<size-1; i++) {
        int weight = (rand() % 100) + 1;
        matrix->addEdge(i, i + 1, weight);
    }

    int edgesToAdd = int(0.01 * density * maxEdges);

    // adding the rest of the edges
    while (edgesToAdd > 0) {
        int weight = (rand() % 100) + 1;
        int start = rand() % size;
        int end = rand() % size;

        if(matrix->getEdge(start, end) == NO_EDGE) {
            matrix->addEdge(start, end, weight);
            edgesToAdd--;
        }
    }
}
