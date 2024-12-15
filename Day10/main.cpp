#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
using namespace std;

string get_location(int y, int x) {
    return to_string(y) + "," + to_string(x);
}

// make sure to pass visitedTrailEnds by reference so it is same set by all recursive calls
int get_possible_paths(vector<vector<int>> grid, int currentY, int currentX, vector<tuple<int, int>>& directions, unordered_set<string>& visitedTrailEnds) {
    int currentHeight = grid[currentY][currentX];
    bool isTrailEnd = currentHeight + 1 == 9;

    int distinctPaths = 0;

    // try out every direction
    for (int i = 0; i < directions.size(); i++) {
        // calc new y,x
        int newY = currentY + get<0>(directions[i]);
        int newX = currentX + get<1>(directions[i]);

        // check if we are still in bound and if the next height is the current height + 1
        if(newY >= 0 && newY < grid.size() && newX >= 0 && newX < grid[newY].size() && grid[newY][newX] == currentHeight + 1) {
            if(isTrailEnd) {
                // we reached a trail end - we found a distinct path
                distinctPaths +=  1;

                // check if there was already another path that ended at the same trail end
                if(auto iter = visitedTrailEnds.find(get_location(newY, newX)); iter == visitedTrailEnds.end()) {
                    visitedTrailEnds.insert(get_location(newY, newX));
                }
            } else {
                // keep going recursively
                distinctPaths += get_possible_paths(grid, newY, newX, directions, visitedTrailEnds);
            }
        }
    }

    return distinctPaths;
}

int main() {
    string line;
    ifstream inputFile("./input.txt");

    vector<vector<int>> grid;
    unordered_set<string> trailheads;
    vector<tuple<int, int>> directions = {
        {-1, 0}, //top
        {0, 1}, //right
        {1, 0}, //down
        {0, -1} //left
    };

    int firstSolution = 0;
    int secondSolution = 0;

    // go over file line by line
    while (getline (inputFile, line)) {
        vector<int> lineList;

        for (int i = 0; i < line.size(); i++) {
            lineList.push_back(line[i] - '0');
        }

        grid.push_back(lineList);
    }

    // get trailheads
    for (int y = 0; y < grid.size(); y++) {
        for(int x = 0; x < grid[y].size(); x++) {
            if (grid[y][x] == 0) {
                trailheads.insert(get_location(y, x));
            }
        }
    }

    // get all possible paths
    for (auto it = trailheads.begin(); it != trailheads.end(); it++) {
        string location = *it;
        int y = stoi(location.substr(0, location.find(",")));
        int x = stoi(location.substr(location.find(",") + 1));

        unordered_set<string> visitedTrailEnds;
        secondSolution += get_possible_paths(grid, y, x, directions, visitedTrailEnds);
        firstSolution += visitedTrailEnds.size();
    }

    // close file
    inputFile.close();

    cout << "Solution first Star: " << firstSolution << endl;
    cout << "Solution second Star: " << secondSolution << endl;
}