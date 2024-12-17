export class CPU {
    public program: number[] = [];

    public registerA: number = 0;
    public registerB: number = 0;
    public registerC: number = 0;

    public instructionPointer: number = 0;

    public output: number[] = [];

    constructor(registerA: number, registerB: number, registerC: number, program: number[], private haltOnDifferentOutput: boolean = false) {
        this.program = program;
        this.registerA = registerA;
        this.registerB = registerB;
        this.registerC = registerC;
    }

    nextInstruction(): void {
        if (this.isProgramHalting()) {
            throw new Error('Program has already halted');
        }

        const instruction = this.program[this.instructionPointer];
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
    }

    public getOutput(): string {
        return this.output.join(',');
    }

    public isProgramHalting(): boolean {
        if (this.haltOnDifferentOutput && !this.isOutputStillOnTrack()) {
            return true;
        }

        return this.instructionPointer >= this.program.length;
    }

    private adv() {
        this.registerA = Math.trunc(this.registerA / Math.pow(2, this.getComboOperand()));

        this.moveInstructionPointer();
    }

    private bxl() {
        this.registerB = this.registerB ^ this.getLiteralOperand();

        this.moveInstructionPointer();
    }

    private bst() {
        this.registerB = this.getComboOperand() % 8;

        this.moveInstructionPointer();
    }

    private jnz() {
        if (this.registerA === 0) {
            this.moveInstructionPointer();
            return;
        }

        this.jumpInstructionPointer(this.getLiteralOperand());
    }

    private bxc() {
        this.registerB = this.registerB ^ this.registerC;

        this.moveInstructionPointer();
    }

    private out() {
        this.output.push(this.getComboOperand() % 8);

        this.moveInstructionPointer();
    }

    private bdv() {
        this.registerB = Math.trunc(this.registerA / Math.pow(2, this.getComboOperand()));

        this.moveInstructionPointer();
    }

    private cdv() {
        this.registerC = Math.trunc(this.registerA / Math.pow(2, this.getComboOperand()));

        this.moveInstructionPointer();
    }

    private getLiteralOperand() {
        return this.program[this.instructionPointer + 1];
    }

    private getComboOperand() {
        const operand = this.program[this.instructionPointer + 1];

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
    }

    private moveInstructionPointer() {
        this.instructionPointer += 2;
    }

    private jumpInstructionPointer(newIndex: number) {
        this.instructionPointer = newIndex;
    }

    public isOutputEqualProgram(): boolean {
        if (this.output.length !== this.program.length) {
            return false;
        }

        return this.isOutputStillOnTrack();
    }

    private isOutputStillOnTrack(): boolean {
        for (let i = 0; i < this.output.length; i++) {
            if (this.output[i] !== this.program[i]) {
                return false;
            }
        }

        return true;
    }
}
