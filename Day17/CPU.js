"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.CPU = void 0;
var CPU = /** @class */ (function () {
    function CPU(registerA, registerB, registerC, program, haltOnDifferentOutput) {
        if (haltOnDifferentOutput === void 0) { haltOnDifferentOutput = false; }
        this.haltOnDifferentOutput = haltOnDifferentOutput;
        this.program = [];
        this.registerA = 0;
        this.registerB = 0;
        this.registerC = 0;
        this.instructionPointer = 0;
        this.output = [];
        this.program = program;
        this.registerA = registerA;
        this.registerB = registerB;
        this.registerC = registerC;
    }
    CPU.prototype.nextInstruction = function () {
        if (this.isProgramHalting()) {
            throw new Error('Program has already halted');
        }
        var instruction = this.program[this.instructionPointer];
        switch (instruction) {
            case 0:
                this.adv();
                break;
            case 1:
                this.bxl();
                break;
            case 2:
                this.bst();
                break;
            case 3:
                this.jnz();
                break;
            case 4:
                this.bxc();
                break;
            case 5:
                this.out();
                break;
            case 6:
                this.bdv();
                break;
            case 7:
                this.cdv();
                break;
            default:
                throw new Error('Invalid instruction');
        }
    };
    CPU.prototype.getOutput = function () {
        return this.output.join(',');
    };
    CPU.prototype.isProgramHalting = function () {
        if (this.haltOnDifferentOutput && !this.isOutputStillOnTrack()) {
            return true;
        }
        return this.instructionPointer >= this.program.length;
    };
    CPU.prototype.adv = function () {
        this.registerA = Math.trunc(this.registerA / Math.pow(2, this.getComboOperand()));
        this.moveInstructionPointer();
    };
    CPU.prototype.bxl = function () {
        this.registerB = this.registerB ^ this.getLiteralOperand();
        this.moveInstructionPointer();
    };
    CPU.prototype.bst = function () {
        this.registerB = this.getComboOperand() % 8;
        this.moveInstructionPointer();
    };
    CPU.prototype.jnz = function () {
        if (this.registerA === 0) {
            this.moveInstructionPointer();
            return;
        }
        this.jumpInstructionPointer(this.getLiteralOperand());
    };
    CPU.prototype.bxc = function () {
        this.registerB = this.registerB ^ this.registerC;
        this.moveInstructionPointer();
    };
    CPU.prototype.out = function () {
        this.output.push(this.getComboOperand() % 8);
        this.moveInstructionPointer();
    };
    CPU.prototype.bdv = function () {
        this.registerB = Math.trunc(this.registerA / Math.pow(2, this.getComboOperand()));
        this.moveInstructionPointer();
    };
    CPU.prototype.cdv = function () {
        this.registerC = Math.trunc(this.registerA / Math.pow(2, this.getComboOperand()));
        this.moveInstructionPointer();
    };
    CPU.prototype.getLiteralOperand = function () {
        return this.program[this.instructionPointer + 1];
    };
    CPU.prototype.getComboOperand = function () {
        var operand = this.program[this.instructionPointer + 1];
        if (operand < 4) {
            return operand;
        }
        switch (operand) {
            case 4:
                return this.registerA;
            case 5:
                return this.registerB;
            case 6:
                return this.registerC;
            default:
                throw new Error('Reserved Combo Operand.');
        }
    };
    CPU.prototype.moveInstructionPointer = function () {
        this.instructionPointer += 2;
    };
    CPU.prototype.jumpInstructionPointer = function (newIndex) {
        this.instructionPointer = newIndex;
    };
    CPU.prototype.isOutputEqualProgram = function () {
        if (this.output.length !== this.program.length) {
            return false;
        }
        return this.isOutputStillOnTrack();
    };
    CPU.prototype.isOutputStillOnTrack = function () {
        for (var i = 0; i < this.output.length; i++) {
            if (this.output[i] !== this.program[i]) {
                return false;
            }
        }
        return true;
    };
    return CPU;
}());
exports.CPU = CPU;
