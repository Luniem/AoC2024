namespace operators {

    public enum Operator {
        Add,
        Multiply,
        Concatinate
    }

    public static class OperationExecutor {

        public static long Apply(long a, long b, Operator op) {
            switch (op) {
                case Operator.Add:
                    return a + b;
                case Operator.Multiply:
                    return a * b;
                case Operator.Concatinate:
                    return long.Parse(a.ToString() + b.ToString());
                default:
                    throw new Exception("Unknown operator");
            }
        }
    }
}