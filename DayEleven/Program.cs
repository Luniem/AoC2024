using stonesCalc;

string input = @"/home/nico/projects/AoC2024/DayEleven/input.txt";
string numbersString = File.ReadAllText(input);

StonesCalc stonesCalc = new StonesCalc(numbersString);

int firstSolutionSteps = 25;
int secondSolutionSteps = 75;
for(int i = 0; i < firstSolutionSteps; i++) {
    stonesCalc.Blink();
    secondSolutionSteps--;
}

Console.WriteLine("First Solution: " + stonesCalc.GetStonesCount());

for(int i = 0; i < secondSolutionSteps; i++) {
    stonesCalc.Blink();
}

Console.WriteLine("Second Solution: " + stonesCalc.GetStonesCount());