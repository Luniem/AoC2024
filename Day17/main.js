"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var fs_1 = require("fs");
var CPU_1 = require("./CPU");
var input = (0, fs_1.readFileSync)('input.txt', 'utf-8').trim().split('\n');
// const registerA = parseInt(input[0].split(': ')[1]);
var registerB = parseInt(input[1].split(': ')[1]);
var registerC = parseInt(input[2].split(': ')[1]);
var program = input[4].split(': ')[1].split(',').map(Number);
var regA = 5000000000 - 1;
var cpu;
do {
    regA++;
    cpu = new CPU_1.CPU(regA, registerB, registerC, program, true);
    while (!cpu.isProgramHalting()) {
        cpu.nextInstruction();
    }
} while (!cpu.isOutputEqualProgram());
console.log('Program copies on: ', regA);
