import * as fs from 'fs';

const lines = fs.readFileSync('/home/nico/projects/AoC2024/DaySix/input.txt', 'utf-8').split('\n');

let startPos: [number, number] = [0, 0];
const obstacles: [number, number][] = [];

for (let y = 0; y < lines.length; y++) {
    const line = lines[y];
    for (let x = 0; x < line.length; x++) {
        const element = line[x];
        if (element === '#') {
            obstacles.push([y, x]);
        } else if (element === '^') {
            startPos = [y, x];
        }
    }
}

const directions = [
    [-1, 0],
    [0, 1],
    [1, 0],
    [0, -1],
];

let currentDirection = 0;
let isOutOfBounds = false;

const visitedPlaces: Set<string> = new Set();

// add start location
visitedPlaces.add(getLocationKey(startPos));
let currPosition = startPos;

while (!isOutOfBounds) {
    while (obstacles.some((obstacle) => obstacle[0] === currPosition[0] + directions[currentDirection][0] && obstacle[1] === currPosition[1] + directions[currentDirection][1])) {
        currentDirection = (currentDirection + 1) % 4;
    }

    currPosition = [currPosition[0] + directions[currentDirection][0], currPosition[1] + directions[currentDirection][1]];

    isOutOfBounds = currPosition[0] < 0 || currPosition[1] < 0 || currPosition[0] >= lines.length || currPosition[1] >= lines[0].length;
    if (!isOutOfBounds) {
        visitedPlaces.add(getLocationKey(currPosition));
    }
}

console.log(visitedPlaces.size);

const visitedPlacesWithLocation: Set<string> = new Set();

//brutoforce our way through this ==> just try all position once, when we enter a same position with the same location, we stuck in a loop
let secondSolution = 0;

for (let y = 0; y < lines.length; y++) {
    console.log(y);
    for (let x = 0; x < lines[0].length; x++) {
        let currentPosition = startPos;
        const newObstacles: [number, number][] = [...obstacles, [y, x]];
        currentDirection = 0;
        isOutOfBounds = false;
        visitedPlacesWithLocation.clear();
        visitedPlacesWithLocation.add(getLocationKey(currentPosition));

        if (y == 6 && x == 6) {
            debugger;
        }

        while (!isOutOfBounds) {
            while (
                newObstacles.some(
                    (obstacle) => obstacle[0] === currentPosition[0] + directions[currentDirection][0] && obstacle[1] === currentPosition[1] + directions[currentDirection][1]
                )
            ) {
                currentDirection = (currentDirection + 1) % 4;
            }

            currentPosition = [currentPosition[0] + directions[currentDirection][0], currentPosition[1] + directions[currentDirection][1]];

            isOutOfBounds = currentPosition[0] < 0 || currentPosition[1] < 0 || currentPosition[0] >= lines.length || currentPosition[1] >= lines[0].length;
            if (!isOutOfBounds) {
                const locationKey = getLocationWithDirectionKey(currentPosition, currentDirection);
                if (visitedPlacesWithLocation.has(locationKey)) {
                    break;
                } else {
                    visitedPlacesWithLocation.add(locationKey);
                }
            }
        }

        if (!isOutOfBounds) {
            secondSolution++;
        }
    }
}

console.log(secondSolution);

function getLocationKey(location: [number, number]): string {
    return `${location[0]}-${location[1]}`;
}

function getLocationWithDirectionKey(location: [number, number], direction: number): string {
    return `${location[0]}-${location[1]}-${direction}`;
}
