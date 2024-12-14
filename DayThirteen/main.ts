import fs from 'fs';

const lines = fs.readFileSync('./input.txt', 'utf-8').toString().split('\n');

const costButtonA = 3;
const costButtonB = 1;

let currentLine = 0;
let firstSolution = 0;
let secondSolution = 0;

while (currentLine < lines.length) {
    firstSolution += calculateCheapestPresses(currentLine, 0);
    secondSolution += calculateCheapestPresses(currentLine, 10000000000000);
    currentLine += 4;
}

function calculateCheapestPresses(lineIndex: number, addedValue: number): number {
    // do something with the current line
    const aButton = lines[lineIndex].substring(10);
    const bButton = lines[lineIndex + 1].substring(10);

    const splittedA = aButton.split(', ');
    const splittedB = bButton.split(', ');

    const aX = parseInt(splittedA[0].split('+')[1]);
    let aY = parseInt(splittedA[1].split('+')[1]);

    const bX = parseInt(splittedB[0].split('+')[1]);
    let bY = parseInt(splittedB[1].split('+')[1]);

    const searchedValues = lines[lineIndex + 2].substring(7);
    const splittedSearch = searchedValues.split(', ');
    const searchedX = parseInt(splittedSearch[0].split('=')[1]) + addedValue;
    let searchedY = parseInt(splittedSearch[1].split('=')[1]) + addedValue;

    // create a factor so when subtracting equation 1 from 2 we are losing y and can solve for x
    const factor = bX / bY;

    // correct the values
    aY *= factor;
    searchedY *= factor;

    // now we can solve for x
    const aTerm = aX - aY;
    const searchedTerm = searchedX - searchedY;

    const precision = 3;
    // correct possible floating point errors
    const aPresses = +(searchedTerm / aTerm).toFixed(precision);
    const bPresses = +((searchedX - aX * aPresses) / bX).toFixed(precision);
    if (Number.isInteger(aPresses) && Number.isInteger(bPresses)) {
        return aPresses * costButtonA + bPresses * costButtonB;
    }

    return 0;
}

console.log('First solution: ', firstSolution);
console.log('Second solution: ', secondSolution);

function greatestCommonDivisor(a: number, b: number): number {
    if (b === 0) {
        return a;
    }
    return greatestCommonDivisor(b, a % b);
}
