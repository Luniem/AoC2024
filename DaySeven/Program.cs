using operators;

// read input and create equation-objects
string inputFile = @"/home/nico/projects/AoC2024/DaySeven/input.txt";
List<Equation> equations = InputReadFunctions.ReadAndCreateEquationsFromLines(inputFile);

long firstSolution = 0;
long secondSolution = 0;
DateTime start = DateTime.Now;

Operator[] firstSolutionOperators = [Operator.Add, Operator.Multiply];
Operator[] secondSolutionOperators = [Operator.Add, Operator.Multiply, Operator.Concatinate];

foreach(Equation equation in equations) {
    if(recursiveCalculate(equation, firstSolutionOperators)){
        firstSolution += equation.TestValue;
    }

    if(recursiveCalculate(equation, secondSolutionOperators)){
        secondSolution += equation.TestValue;
    }
}

Console.WriteLine(firstSolution);
Console.WriteLine(secondSolution);
Console.WriteLine(DateTime.Now - start);

// recursive function to calculate all possible equations and returns true when a single combination resolves correctly
bool recursiveCalculate(Equation equation, IEnumerable<Operator> operators) {
    foreach (Operator op in operators) {
        Equation equationCopy = new Equation(equation.TestValue, new List<long>(equation.Operands), equation.CurrentValue);
        equationCopy.CurrentValue = OperationExecutor.Apply(equationCopy.CurrentValue, equationCopy.Operands.First(), op);
        equationCopy.Operands.RemoveAt(0);

        // check if equation is finished
        if(equationCopy.IsFinished()){
            // check if equation resolves correctly
            if(equationCopy.ResolvesCorrectly()){
                return true;
            }

            // no need to further check this equation since it is finished and did not resolve correctly
            continue;
        }

        // check if we are already to high, so we can skip and dont need to evaluate further
        if(equationCopy.CurrentValue > equationCopy.TestValue){
            continue;
        }

        // for this resulting equation we try every operation again
        bool didResolve = recursiveCalculate(equationCopy, operators);

        if(didResolve){
            return true;
        }
    }

    return false;
    

    // Equation plusEquation = new Equation(equation.TestValue, new List<long>(equation.Operands), equation.CurrentValue);
    // plusEquation.AddValue();

    // // make copf of equation 2
    // Equation concatEquation = new Equation(equation.TestValue, new List<long>(equation.Operands), equation.CurrentValue);
    // concatEquation.concatinateValue();

    // // multiply value
    // equation.MultiplyValue();

    // // check if equation is finished
    // if(equation.isFinished()){
    //     if(equation.resolvesCorrectly()){
    //         return true;
    //     }

    //     if(plusEquation.resolvesCorrectly()){
    //         return true;
    //     }

    //     if(concatEquation.resolvesCorrectly()){
    //         return true;
    //     }

    //     return false;
    // }
    
    // //check if is too high at all possible equations already
    // if(equation.CurrentValue > equation.TestValue && plusEquation.CurrentValue > plusEquation.TestValue && concatEquation.CurrentValue > concatEquation.TestValue){
    //     return false;
    // }

    // // recursive call
    // return checkPossibleEquation(equation) || checkPossibleEquation(plusEquation) || checkPossibleEquation(concatEquation);
}