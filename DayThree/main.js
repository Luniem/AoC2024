const fs = require('fs');

const program = fs.readFileSync('./input.txt', 'utf-8');

let firstSolution = 0;

const mulRegex = new RegExp('mul\\(\\d{1,3},\\d{1,3}\\)', 'g');
const doRegex = new RegExp('do\\(\\)', 'g');
const dontRegex = new RegExp("don\\'t\\(\\)", 'g');

program.match(mulRegex).forEach((mul) => {
    firstSolution += execMultiplication(mul);
});

console.log(`Solution first Star: ${firstSolution}`);

let secondSolution = 0;

const doIndizes = [];
const dontIndizes = [];

const filterIncludedIndizes = (indizes, matchIndex) => indizes.filter((index) => index < matchIndex).sort((a, b) => b - a)[0];

program.matchAll(doRegex).forEach((match) => addMatchIndexToList(match, doIndizes));
program.matchAll(dontRegex).forEach((match) => addMatchIndexToList(match, dontIndizes));

program.matchAll(mulRegex).forEach((match) => {
    const currIndex = match.index;

    const highestDoIndexBeforeMatch = filterIncludedIndizes(doIndizes, currIndex);
    const highestDontIndexBeforeMatch = filterIncludedIndizes(dontIndizes, currIndex);

    if (highestDoIndexBeforeMatch > highestDontIndexBeforeMatch || highestDontIndexBeforeMatch === undefined) {
        secondSolution += execMultiplication(match[0]);
    }
});

console.log(`Solution second Star: ${secondSolution}`);

function addMatchIndexToList(match, list) {
    return match ? list.push(match.index) : undefined;
}

function execMultiplication(multiplyString) {
    const [a, b] = multiplyString.match(/\d{1,3}/g);
    return a * b;
}
