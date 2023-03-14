#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Define a constant for infinity
const double INF = numeric_limits<double>::infinity();

// Bellman-Ford algorithm to find the shortest path in a graph
bool bellman_ford(const vector<vector<double>>& graph, int start, vector<double>& dist) {
    int n = graph.size();
    dist[start] = 0.0;
    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (graph[u][v] == INF) continue;
                double alt = dist[u] - log(graph[u][v]);
                if (alt < dist[v]) {
                    dist[v] = alt;
                }
            }
        }
    }
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] == INF) continue;
            double alt = dist[u] - log(graph[u][v]);
            if (alt < dist[v]) {
                return false;  // negative cycle detected
            }
        }
    }
    return true;
}

int main() {
    // Open the input file
    //ifstream infile("input.txt");
  /**
  if (!infile) {
        cerr << "Error: could not open input file" << endl;
        return 1;
    }
  */
    // Read the number of currencies and exchange rates
    int n, m;
    cin >> n >> m;

    // Initialize the graph with INF weights
    vector<vector<double>> graph(n, vector<double>(n, INF));

    // Read the exchange rates and set the corresponding edge weights
    for (int i = 0; i < m; ++i) {
        int u, v;
        double rate;
        cin >> u >> v >> rate;
        graph[u][v] = max(1e-9, rate);  // set a minimum weight to avoid taking logarithm of 0
    }

    // Read the source and destination currencies
    int s, t;
    cin >> s >> t;

    // Find the most advantageous sequence of currency exchanges
    vector<double> dist(n, INF);
    if (bellman_ford(graph, s, dist)) {
        double result = exp(-dist[t]);
        cout << "The most advantageous exchange rate from currency " << s << " to currency " << t << " is " << result << endl;
    } else {
        cout << "Negative cycle detected" << endl;
    }

    return 0;
}
