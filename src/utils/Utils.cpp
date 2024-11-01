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
    ifstream input(filename, fstream::in);
    if(!input.good())
        throw std::invalid_argument("An error occurred while trying to open file with filename: " + filename);

    vector<vector<int>> numbers;
    string line;
    while (getline(input, line)) {
        if (line.empty()) break;
        auto params = split(line, " ");
        auto nums = extractInt(params);
        numbers.push_back(nums);
    }

    return numbers;
}
