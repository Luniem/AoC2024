#include <iostream>
#include <fstream> 
#include <vector>
using namespace std;

int getDistance(int a, int b) {
    int difference = abs(a - b);
    return difference;
}

bool descendingCompare(int a, int b) {
    return a > b;
}

// bubble sort through list
void sortList(vector<int> &list) {
    for (int i = list.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (descendingCompare(list[j], list[j + 1]))
            {
                int temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

int main() {
    string line;
    ifstream inputFile("./input.txt");

    string delimiter = "   ";

    vector<int> leftList;
    vector<int> rightList;

    // go over file line by line
    while (getline (inputFile, line)) {
        int leftNumber = stoi(line.substr(0, line.find(delimiter)), 0, 10);
        int rightNumber = stoi(line.substr(line.find(delimiter) + 3), 0, 10);

        // add numbers to list
        leftList.push_back(leftNumber);
        rightList.push_back(rightNumber);
    }

    // close file
    inputFile.close();

    // make sure lists have the same length
    if (leftList.size() != rightList.size()) {
        cout << "Lists are not the same length" << endl;
        return 1;
    }

    //sort lists
    sortList(leftList);
    sortList(rightList);

    // calculate distances for every index
    int firstSolution = 0;
    for (int i = 0; i < leftList.size(); i++) {
        firstSolution += getDistance(leftList[i], rightList[i]);
    }

    cout << "Solution first Star: " << firstSolution << endl;

    int secondSolution = 0;
    for (int i = 0; i < leftList.size(); i++) {
        int currValue = leftList[i];
        int appearances = 0;

        for (int j = 0; j < rightList.size(); j++) {
            if (rightList[j] == currValue) {
                appearances++;
            }
        }

        secondSolution += appearances * currValue;
    }

    cout << "Solution second Star: " << secondSolution << endl;
}