#include <iostream>
#include <fstream> 
#include <vector>
using namespace std;

bool canBeConstructed(string leftDesign, vector<string> &towelList) {
    if(leftDesign.empty()) {
        return true;
    }

    for (int i = 0; i < towelList.size(); i++) {
        string towel = towelList[i];

        if(leftDesign.find(towel) == 0) {
            string newDesign = leftDesign.substr(towel.size());
            if(canBeConstructed(newDesign, towelList)) {
                return true;
            }
        }
    }

    return false;
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

    // we have every towel as single but w. so we just check if we can create the w somehow
    for (int i = 0; i < designList.size(); i++) {
        string design = designList[i];

        if(canBeConstructed(design, towelList)) {
            firstSolution++;
        }
    }

    cout << "Solution first Star: " << firstSolution << endl;
    cout << "Solution second Star: " << secondSolution << endl;
}