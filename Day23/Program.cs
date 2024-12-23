string input = @"C:\Users\NIKZ\projects\AoC2024\Day23\input.txt";
string[] connectionsStrings = File.ReadAllLines(input);

Dictionary<string, List<string>> connections = new Dictionary<string, List<string>>();

foreach(string connection in connectionsStrings) {
    string[] parts = connection.Split("-");
    string a = parts[0];
    string b = parts[1];

    if(!connections.ContainsKey(a)) {
        connections[a] = new List<string>();
    }

    if(!connections.ContainsKey(b)) {
        connections[b] = new List<string>();
    }

    connections[a].Add(b);
    connections[b].Add(a);
}

HashSet<string> setsWithTComputers = new HashSet<string>();

List<KeyValuePair<string, List<string>>> connectionsOfTComputers = connections.Where(g => g.Key.StartsWith("t")).ToList();
foreach(var connectionOfT in connectionsOfTComputers) {
    for(int i = 0; i < connectionOfT.Value.Count; i++) {
        for(int j = i + 1; j < connectionOfT.Value.Count; j++) {
            string a = connectionOfT.Value[i];
            string b = connectionOfT.Value[j];

            if(connections[a].Contains(b)) {
                List<string> conns = new List<string> {connectionOfT.Key, a, b};
                conns.Sort();
                setsWithTComputers.Add(string.Join("-", conns));
            }
        }
    }
}

Console.WriteLine("First Solution: " + setsWithTComputers.Count);

List<string> biggestCluster = new List<string>();

foreach(var connectionOfT in connectionsOfTComputers) {
    for(int i = 0; i < connectionOfT.Value.Count; i++) {

        List<string> cluster = new List<string> {connectionOfT.Key, connectionOfT.Value[i]};

        for(int j = i + 1; j < connectionOfT.Value.Count; j++) {
            string a = connectionOfT.Value[j];

            // it need to have all connections in cluster to be added
            if(cluster.All(clusterElement => connections[a].Contains(clusterElement))) {
                cluster.Add(a);
            }
        }

        if(cluster.Count > biggestCluster.Count) {
            biggestCluster = cluster;
        }
    }
}

biggestCluster.Sort();
System.Console.WriteLine("Second Solution:" + string.Join(",", biggestCluster));