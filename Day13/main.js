"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var fs_1 = require("fs");
var lines = fs_1.default.readFileSync('./testInput.txt', 'utf-8').toString().split('\n');
var costButtonA = 3;
var costButtonB = 1;
var firstSolution = 0;
// one strategy could be to just try to press the Button A as less as possible since it is more expensive
var currentLine = 0;
while (currentLine < lines.length) {
    // do something with the current line
    var aButton = lines[currentLine].substring(10);
    var bButton = lines[currentLine + 1].substring(10);
    var splittedA = aButton.split(', ');
    var splittedB = bButton.split(', ');
    var aX = parseInt(splittedA[0].split('+')[1]);
    var aY = parseInt(splittedA[1].split('+')[1]);
    var bX = parseInt(splittedB[0].split('+')[1]);
    var bY = parseInt(splittedB[1].split('+')[1]);
    var searchedValues = lines[currentLine + 2].substring(7);
    var splittedSearch = searchedValues.split(', ');
    var searchedX = parseInt(splittedSearch[0].split('=')[1]) + 10000000000000;
    var searchedY = parseInt(splittedSearch[1].split('=')[1]) + 10000000000000;
    // try with 0 a presses than with 1 a press and so on until we find a solution or the amount of a presses is too high
    var aPresses = 0;
    while (aPresses * aX <= searchedX && aPresses * aY <= searchedY) {
        var xAfterA = searchedX - aPresses * aX;
        var yAfterA = searchedY - aPresses * aY;
        // check if we can reach the searched values with the b button
        if (xAfterA % bX === 0 && yAfterA % bY === 0) {
            // check if it takes the same amount of b presses to reach the searched values
            if (xAfterA / bX === yAfterA / bY) {
                // we found a solution
                var bPresses = xAfterA / bX;
                firstSolution += aPresses * costButtonA + bPresses * costButtonB;
                break;
            }
        }
        aPresses++;
    }
    currentLine += 4;
}
console.log('First solution: ', firstSolution);
