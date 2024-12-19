public class Node {
    public int X { get; set; }
    public int Y { get; set; }

    public int Cost { get; set; }
    public Node? Previous { get; set; }

    public Node(int x, int y) {
        X = x;
        Y = y;
        Cost = int.MaxValue;
    }


}