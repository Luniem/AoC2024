import { readFileSync } from 'fs';
import { CPU } from './CPU';

const input = readFileSync('input.txt', 'utf-8').trim().split('\n');

// const registerA = parseInt(input[0].split(': ')[1]);
const registerB = parseInt(input[1].split(': ')[1]);
const registerC = parseInt(input[2].split(': ')[1]);

const program = input[4].split(': ')[1].split(',').map(Number);

let regA = 5000000000 - 1;

let cpu;

do {
    regA++;
    cpu = new CPU(regA, registerB, registerC, program, true);

    while (!cpu.isProgramHalting()) {
        cpu.nextInstruction();
    }
} while (!cpu.isOutputEqualProgram());

console.log('Program copies on: ', regA);
