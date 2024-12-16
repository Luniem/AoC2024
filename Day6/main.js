"use strict";
var __spreadArray = (this && this.__spreadArray) || function (to, from, pack) {
    if (pack || arguments.length === 2) for (var i = 0, l = from.length, ar; i < l; i++) {
        if (ar || !(i in from)) {
            if (!ar) ar = Array.prototype.slice.call(from, 0, i);
            ar[i] = from[i];
        }
    }
    return to.concat(ar || Array.prototype.slice.call(from));
};
Object.defineProperty(exports, "__esModule", { value: true });
var fs = require("fs");
var lines = fs.readFileSync('/home/nico/projects/AoC2024/Day6/input.txt', 'utf-8').split('\n');
var startPos = [0, 0];
var obstacles = [];
for (var y = 0; y < lines.length; y++) {
    var line = lines[y];
    for (var x = 0; x < line.length; x++) {
        var element = line[x];
        if (element === '#') {
            obstacles.push([y, x]);
        }
        else if (element === '^') {
            startPos = [y, x];
        }
    }
}
var directions = [
    [-1, 0],
    [0, 1],
    [1, 0],
    [0, -1],
];
var currentDirection = 0;
var isOutOfBounds = false;
var visitedPlaces = new Set();
var visitedPlacesWithLocation = new Set();
var bolders = new Set();
var startDate = new Date();
// add start location
visitedPlaces.add(getLocationKey(startPos));
var currPosition = startPos;
function wouldEndUpInLoop(obs, places, startDirection, startPosition) {
    var isOutOfBounds = false;
    while (!isOutOfBounds) {
        while (obs.some(function (obstacle) { return obstacle[0] === startPosition[0] + directions[startDirection][0] && obstacle[1] === startPosition[1] + directions[startDirection][1]; })) {
            startDirection = (startDirection + 1) % 4;
        }
        startPosition = [startPosition[0] + directions[startDirection][0], startPosition[1] + directions[startDirection][1]];
        isOutOfBounds = startPosition[0] < 0 || startPosition[1] < 0 || startPosition[0] >= lines.length || startPosition[1] >= lines[0].length;
        if (isOutOfBounds) {
            return false;
        }
        if (places.has(getLocationWithDirectionKey(startPosition, startDirection))) {
            return true;
        }
        places.add(getLocationWithDirectionKey(startPosition, startDirection));
    }
}
function process_map(obstacles, currPosition, currentDirection) {
    while (!isOutOfBounds) {
        while (obstacles.some(function (obstacle) { return obstacle[0] === currPosition[0] + directions[currentDirection][0] && obstacle[1] === currPosition[1] + directions[currentDirection][1]; })) {
            currentDirection = (currentDirection + 1) % 4;
        }
        currPosition = [currPosition[0] + directions[currentDirection][0], currPosition[1] + directions[currentDirection][1]];
        isOutOfBounds = currPosition[0] < 0 || currPosition[1] < 0 || currPosition[0] >= lines.length || currPosition[1] >= lines[0].length;
        if (!isOutOfBounds) {
            visitedPlaces.add(getLocationKey(currPosition));
            visitedPlacesWithLocation.add(getLocationWithDirectionKey(currPosition, currentDirection));
        }
        // check what happens if place a obstacle in front
        var newObs = [currPosition[0] + directions[currentDirection][0], currPosition[1] + directions[currentDirection][1]]; // right in front of us
        // check if this obstacle is already there as a real obstacle
        if (wouldEndUpInLoop(__spreadArray(__spreadArray([], obstacles, true), [newObs], false), new Set(visitedPlacesWithLocation), currentDirection, __spreadArray([], currPosition, true))) {
            bolders.add(getLocationKey(newObs));
        }
    }
}
// process the map
process_map(obstacles, currPosition, currentDirection);
var endDate = new Date();
console.log('First solution: ', visitedPlaces.size);
console.log('Second solution: ', bolders.size);
console.log('Needed Time: ', endDate.getTime() - startDate.getTime());
function getLocationKey(location) {
    return "".concat(location[0], "-").concat(location[1]);
}
function getLocationWithDirectionKey(location, direction) {
    return "".concat(location[0], "-").concat(location[1], "-").concat(direction);
}
