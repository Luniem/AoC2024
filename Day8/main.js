const fs = require('fs');

const lines = fs.readFileSync('input.txt', { encoding: 'utf-8' }).split('\n');

const maxX = lines[0].length - 1;
const maxY = lines.length - 1;

const antennas = new Map();
const antinodes1 = new Set();
const antinodes2 = new Set();

// get all the antennas and put them into a map
for (let y = 0; y < lines.length; y++) {
    const line = lines[y];
    for (let x = 0; x < line.length; x++) {
        const char = line[x];

        if (char !== '.') {
            if (antennas.has(char)) {
                antennas.get(char).push({ x, y });
            } else {
                antennas.set(char, [{ x, y }]);
            }
        }
    }
}

antennas.values().forEach((antennas) => {
    for (let i = 0; i < antennas.length; i++) {
        for (let j = 0; j < antennas.length; j++) {
            // if the same => skip
            if (i === j) continue;

            const antenna1 = antennas[i];
            const antenna2 = antennas[j];
            const delta = { x: antenna1.x - antenna2.x, y: antenna1.y - antenna2.y };

            //first star
            let newNode = { x: antenna1.x + delta.x, y: antenna1.y + delta.y };
            if (!isOOB(newNode)) {
                antinodes1.add(createPositionKey(newNode));
            }

            // second start - start adding the delta from antenna2 - this will convert antenna to antinode automatically
            newNode = { x: antenna2.x + delta.x, y: antenna2.y + delta.y };

            while (!isOOB(newNode)) {
                antinodes2.add(createPositionKey(newNode));
                newNode = { x: newNode.x + delta.x, y: newNode.y + delta.y };
            }
        }
    }
});

console.log(`Solution first Star: ${antinodes1.size}`);
console.log(`Solution second Star: ${antinodes2.size}`);

function createPositionKey(node) {
    return `${node.x},${node.y}`;
}

function isOOB(node) {
    return node.x < 0 || node.x > maxX || node.y < 0 || node.y > maxY;
}
