#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100;

struct Edge {
    int u, v, w; // u and v are the endpoints of the edge, w is the weight
};

int n, m; // n is the number of vertices, m is the number of edges
vector<Edge> edges; // a vector to store the edges of the graph
int degree[MAXN + 1]; // degree[i] is the degree of vertex i
int used[MAXN + 1]; // used[i] is 1 if weight i has been used, 0 otherwise

// A comparison function to sort edges in decreasing order of degree
bool cmp(const Edge& a, const Edge& b) {
    return degree[a.u] + degree[a.v] > degree[b.u] + degree[b.v];
}

// The greedy algorithm
void greedy() {
    // Sort the edges in decreasing order of degree
    sort(edges.begin(), edges.end(), cmp);
    // Assign weights to the edges
    for (auto& e : edges) {
        int u = e.u, v = e.v, w = e.w;
        // If weight w has not been used yet, assign it to edge (u,v)
        if (!used[w]) {
            used[w] = 1;
            degree[u]++;
            degree[v]++;
        }
    }
}

int main() {
    // Read in the graph from standard input
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    // Apply the greedy algorithm
    greedy();
    // Compute the maximum bandwidth of any path in the graph
    int max_bw = *max_element(degree + 1, degree + n + 1);
    // Print the maximum bandwidth to standard output
    cout << "Maximum bandwidth: " << max_bw << endl;
    return 0;
}
