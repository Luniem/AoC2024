using System.Reflection;


public static class InputReadFunctions {

    public static List<Equation> ReadAndCreateEquationsFromLines(string inputFilePath) {
        string[] lines = File.ReadAllLines(inputFilePath);

        List<Equation> equations = new List<Equation>();

        foreach(string line in lines){
            string[] parts = line.Split(":");
            string testValue = parts[0];
            string[] operands = parts[1].Trim().Split(" ");

            long testValueInt = long.Parse(testValue);
            List<long> operandsInt = new List<long>();
            foreach(string operand in operands){
                operandsInt.Add(long.Parse(operand));
            }

            equations.Add(new Equation(testValueInt, operandsInt));
        }  

        return equations;
    }
}