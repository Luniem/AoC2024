using System.ComponentModel.DataAnnotations;

List<Node> grid = new List<Node>();

int width = 70;
int height = 70;

for (int y = 0; y <= height; y++) {
    for (int x = 0; x <= width; x++) {
        grid.Add(new Node(x, y));
    }
}

string inputFile = @"C:\Users\NIKZ\projects\AoC2024\Day18\input.txt";
string[] bytes = File.ReadAllLines(inputFile);

int currentlyTakenPushDowns = 0;
int shouldTakenPushDowns = 1024;
pushOrRemoveBytes(bytes, currentlyTakenPushDowns, shouldTakenPushDowns);
currentlyTakenPushDowns = shouldTakenPushDowns;

Node start = grid.First(n => n.X == 0 && n.Y == 0);
Node end = grid.First(n => n.X == width && n.Y == height);
isEndReachable(grid, start, end);

Console.WriteLine(end.Cost);

// binary search until we find the right amount of push downs
bool found = false;

int min = shouldTakenPushDowns;
int max = bytes.Count();

while (!found) {
    // binary search until we found result
    shouldTakenPushDowns = min + (max - min) / 2;
    pushOrRemoveBytes(bytes, currentlyTakenPushDowns, shouldTakenPushDowns);
    currentlyTakenPushDowns = shouldTakenPushDowns;

    if (isEndReachable(grid, start, end)) {
        min = currentlyTakenPushDowns;
    } else {
        max = currentlyTakenPushDowns;
    }

    if (Math.Abs(min - max ) <= 1) {
        found = true;
        Console.WriteLine(bytes[min]);
    }
}

void pushOrRemoveBytes(string[] bytes, int currentlyTakenPushDowns, int shouldTakenPushDowns) {
    bool shouldAdd = shouldTakenPushDowns < currentlyTakenPushDowns;

    for (int i = Math.Min(shouldTakenPushDowns, currentlyTakenPushDowns); i < Math.Max(shouldTakenPushDowns, currentlyTakenPushDowns); i++) {
        string pushDownByte = bytes[i];
        string[] parts = pushDownByte.Split(",");

        int x = int.Parse(parts[0]);
        int y = int.Parse(parts[1]);

        if(shouldAdd) {
            grid.Add(new Node(x, y));
        } else {
            Node node = grid.First(n => n.X == x && n.Y == y);
            grid.Remove(node);
        }
    }
    
}

bool isEndReachable(List<Node> nodes, Node start, Node end) {
    // reset whole grid
    foreach (Node n in grid) {
        n.Cost = int.MaxValue;
        n.Previous = null;
    }

    Queue<Node> queue = new Queue<Node>();
    start.Cost = 0;
    queue.Enqueue(start);

    // dijkstra algorithm
    while (queue.Count > 0) {
        Node current = queue.Dequeue();
        List<Node> neighbors = new List<Node>();

        if (current.X > 0) {
            Node? left = grid.FirstOrDefault(n => n.X == current.X - 1 && n.Y == current.Y);
            if (left != null){
                neighbors.Add(left);
            }
        }
        if (current.X < width) {
            Node? right = grid.FirstOrDefault(n => n.X == current.X + 1 && n.Y == current.Y);
            if (right != null){
                neighbors.Add(right);
            }
        }
        if (current.Y > 0) {
            Node? up = grid.FirstOrDefault(n => n.X == current.X && n.Y == current.Y - 1);
            if(up != null){
                neighbors.Add(up);
            }
        }
        if (current.Y < height) {
            Node? down = grid.FirstOrDefault(n => n.X == current.X && n.Y == current.Y + 1);
            if(down != null){
                neighbors.Add(down);
            }
        }

        foreach (Node neighbor in neighbors) {
            int newCost = current.Cost + 1;
            if (newCost < neighbor.Cost) {
                neighbor.Cost = newCost;
                neighbor.Previous = current;
                queue.Enqueue(neighbor);
            }
        }
    }

    return end.Cost != int.MaxValue;
}