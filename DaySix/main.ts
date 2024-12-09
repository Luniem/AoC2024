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
const visitedPlacesWithLocation: Set<string> = new Set();
const bolders: Set<string> = new Set();

const startDate = new Date();

// add start location
visitedPlaces.add(getLocationKey(startPos));
let secondSolution = 0;
let currPosition = startPos;

function wouldEndUpInLoop(obs: [number, number][], places: Set<string>, startDirection: number, startPosition: [number, number]): boolean {
    let isOutOfBounds = false;

    while (!isOutOfBounds) {
        while (obs.some((obstacle) => obstacle[0] === startPosition[0] + directions[startDirection][0] && obstacle[1] === startPosition[1] + directions[startDirection][1])) {
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

    return false;
}

function test(obstacles: [number, number][], currPosition: [number, number], currentDirection: number) {
    while (!isOutOfBounds) {
        while (
            obstacles.some((obstacle) => obstacle[0] === currPosition[0] + directions[currentDirection][0] && obstacle[1] === currPosition[1] + directions[currentDirection][1])
        ) {
            currentDirection = (currentDirection + 1) % 4;
        }

        currPosition = [currPosition[0] + directions[currentDirection][0], currPosition[1] + directions[currentDirection][1]];

        isOutOfBounds = currPosition[0] < 0 || currPosition[1] < 0 || currPosition[0] >= lines.length || currPosition[1] >= lines[0].length;
        if (!isOutOfBounds) {
            visitedPlaces.add(getLocationKey(currPosition));
            visitedPlacesWithLocation.add(getLocationWithDirectionKey(currPosition, currentDirection));
        }

        // check what happens if place a obstacle in front
        const newObs: [number, number] = [currPosition[0] + directions[currentDirection][0], currPosition[1] + directions[currentDirection][1]]; // right in front of us
        if (wouldEndUpInLoop([...obstacles, newObs], new Set(visitedPlacesWithLocation), currentDirection, [...currPosition])) {
            bolders.add(getLocationKey(newObs));
        }
    }
}

test(obstacles, currPosition, currentDirection);

console.log(visitedPlaces.size);

const endDate = new Date();
console.log(endDate.getTime() - startDate.getTime());
console.log('finished', bolders.size);

function getLocationKey(location: [number, number]): string {
    return `${location[0]}-${location[1]}`;
}

function getLocationWithDirectionKey(location: [number, number], direction: number): string {
    return `${location[0]}-${location[1]}-${direction}`;
}
