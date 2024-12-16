const { assert } = require('console');
const fs = require('fs');

const lines = fs.readFileSync('input.txt', 'utf-8').split('\n');

const grid = new Set();

let start = [0, 0];
let end = [0, 0];

for (let y = 0, x = 0; y < lines.length; y++) {
    for (let x = 0; x < lines[y].length; x++) {
        if (lines[y][x] !== '#') {
            switch (lines[y][x]) {
                case 'S':
                    start = [x, y];
                    break;
                case 'E':
                    end = [x, y];
                    break;
                default:
                    break;
            }
            grid.add(getSetKey(x, y));
        }
    }
}

let leastCost = Number.POSITIVE_INFINITY;
let endRoutes = [];

checkNextOptions(start[0], start[1], 1, 0, 0, new Map(), '');

let uniqueVisitedTiles = new Set();
endRoutes.forEach((route) => {
    const tiles = route.split('->');
    tiles.forEach((tile) => {
        uniqueVisitedTiles.add(tile);
    });
});

console.log('First solution: ', leastCost);
console.log('Second solution: ', uniqueVisitedTiles.size);

function checkNextOptions(currentX, currentY, directionX, directionY, currentCost, alreadyVisited, visitedTilesPath) {
    const currentKey = getSetKey(currentX, currentY);
    visitedTilesPath += currentKey + '->';

    // check if this is a valid node
    if (!grid.has(currentKey) || currentCost > leastCost) {
        return Number.POSITIVE_INFINITY;
    }

    // if we already visited this node and the cost was lower, we can return
    if (alreadyVisited.has(currentKey) && alreadyVisited.get(currentKey) < currentCost) {
        return Number.POSITIVE_INFINITY;
    }

    // if we are on the end node, we can return
    if (currentX === end[0] && currentY === end[1]) {
        const correctedPath = visitedTilesPath.substring(0, visitedTilesPath.length - 2);

        if (currentCost < leastCost) {
            leastCost = currentCost;
            endRoutes = [correctedPath];
        } else if (currentCost === leastCost) {
            endRoutes.push(correctedPath);
        }

        return currentCost;
    }

    alreadyVisited.set(getSetKey(currentX, currentY), currentCost);

    // check going straight
    const straight = checkNextOptions(currentX + directionX, currentY + directionY, directionX, directionY, currentCost + 1, alreadyVisited, visitedTilesPath);

    // check going on one of the sides
    const oneSide = checkNextOptions(currentX + directionY, currentY + directionX, directionY, directionX, currentCost + 1001, alreadyVisited, visitedTilesPath);

    // check going right
    const otherSide = checkNextOptions(
        currentX + directionY * -1,
        currentY + directionX * -1,
        directionY * -1,
        directionX * -1,
        currentCost + 1001,
        alreadyVisited,
        visitedTilesPath
    );

    const fastestWay = Math.min(straight, oneSide, otherSide);

    if (straight !== Math.min(straight, oneSide, otherSide)) {
        alreadyVisited.set(currentKey, alreadyVisited.get(currentKey) + 1000);
    }

    return fastestWay;
}

function getSetKey(x, y) {
    return `${x},${y}`;
}

class Node {
    constructor(x, y, cost) {
        this.x = x;
        this.y = y;
        this.cost = cost;
        this.previous;
    }
}
