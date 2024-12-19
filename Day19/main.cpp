#include <iostream>
#include <fstream> 
#include <vector>
#include <unordered_map>
using namespace std;

int canBeConstructed(string leftDesign, vector<string> &towelList, unordered_map<string, int> &solutions) {
    // check in set if we already have the solution for this string and return the 
    if (solutions.find(leftDesign) != solutions.end()) {
        return solutions[leftDesign];
    }

    if(leftDesign.empty()) {
        return 1;
    }

    int count = 0;

    for (int i = 0; i < towelList.size(); i++) {
        string towel = towelList[i];

        if(leftDesign.find(towel) == 0) {
            string newDesign = leftDesign.substr(towel.size());
            count += canBeConstructed(newDesign, towelList, solutions);
        }
    }

    // add to solution
    solutions[leftDesign] = count;

    return count;
}

int main() {
    int firstSolution = 0;
    int secondSolution = 0;

    string line;
    ifstream inputFile("./input.txt");

    vector<string> towelList;
    vector<string> designList;

    bool hitEmptyLine = false;

    // go over file line by line
    while (getline (inputFile, line)) {
        if(line.empty()) {
            hitEmptyLine = true;
            continue;
        }

        if (!hitEmptyLine) {
            while (line.find(",") != string::npos) {
                int commaIndex = line.find(",");
                string towel = line.substr(0, commaIndex);
                towelList.push_back(towel);
                line = line.substr(commaIndex + 2);
            }

            towelList.push_back(line);
        } else {
            designList.push_back(line);
        }
    }

    // close file
    inputFile.close();

    unordered_map<string, int> solutions = unordered_map<string, int>();
    // we have every towel as single but w. so we just check if we can create the w somehow
    for (int i = 0; i < designList.size(); i++) {
        string design = designList[i];

        secondSolution += canBeConstructed(design, towelList, solutions);
    }

    cout << "Solution first Star: " << firstSolution << endl;
    cout << "Solution second Star: " << secondSolution << endl;
}