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
