import { readFileSync } from "fs";
import { CPU } from "./CPU";

const input = readFileSync("input.txt", "utf-8").trim().split("\n");

const registerA = parseInt(input[0].split(": ")[1]);
const registerB = parseInt(input[1].split(": ")[1]);
const registerC = parseInt(input[2].split(": ")[1]);
const program = input[4].split(": ")[1].split(",").map(Number);

// first solution
const firstCPU = new CPU(registerA, registerB, registerC, program);
firstCPU.run();
console.log("First solution: ", firstCPU.getOutput());

// second solution
let cpu;
const multipliers: number[] = new Array(program.length).fill(-1);

for (let i = program.length - 1; i >= 0; i--) {
    do {
        multipliers[i]++;
        cpu = new CPU(getMultiplierValue(), registerB, registerC, program);
        cpu.run();
    } while (!cpu?.isOutputEqProgram(i) && multipliers[i] < 8);

    if (multipliers[i] >= 8) {
        // go back, try another combi
        multipliers[i] = -1;
        i += 2;
        continue;
    }
}

const multiplierValue = getMultiplierValue();
console.log("Second solution: ", multiplierValue);

function getMultiplierValue(): number {
    return multipliers
        .map((val, i) => Math.pow(8, i) * val)
        .filter((x) => x > 0)
        .reduce((acc, val) => acc + val, 0);
}
