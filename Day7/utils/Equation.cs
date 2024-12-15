public class Equation {
    public long TestValue { get; set; }
    public List<long> Operands { get; set; }

    public long CurrentValue { get; set; }

    public Equation(long testValue, List<long> operands): this(testValue, operands, 0) {
    }

    public Equation(long testValue, List<long> operands, long currentValue){
        TestValue = testValue;
        Operands = operands;
        CurrentValue = currentValue;
    }

    public bool ResolvesCorrectly(){
        return CurrentValue == TestValue;
    }

    public bool IsFinished(){
        return Operands.Count == 0;
    }
}