#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

vector<int> adj[MAXN];
int degree[MAXN];

int main() {
    int n, m;
    cin >> n >> m;
    // We start by reading in the number of vertices n and the number of edges m from the input file. We then initialize the degrees of all vertices to 0
    // Initialize degrees of all vertices to 0
    for (int i = 1; i <= n; i++) {
        degree[i] = 0;
    }

    // We read in the edges from the input file, and update the degrees of their endpoints:
    // Read in edges and update degrees
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }

    // We sort the edges by degree in decreasing order:
    // Sort edges by degree in decreasing order
    vector<pair<int, int>> edges;
    for (int u = 1; u <= n; u++) {
        for (auto v : adj[u]) {
            if (u < v) {
                edges.push_back({degree[u] + degree[v], u * n + v});
            }
        }
    }
    sort(edges.begin(), edges.end(), greater<pair<int, int>>());

    // Here, we use a nested loop to iterate over all edges, and store each edge as a pair of its key (the sum of its endpoints' degrees) and its index in the original adjacency list (represented as u * n + v). We then sort the edges using greater<pair<int, int>>, which sorts them in decreasing order of their keys.
    // We assign bandwidths to the edges in the order of the sorted edges:
    // Assign bandwidth to each edge
    vector<int> bandwidth(m);
    for (auto [_, uv] : edges) {
        int u = uv / n, v = uv % n;
        int endpoint = (degree[u] > degree[v]) ? u : v;
        int bandwidth_uv = degree[endpoint] - 1;
        bandwidth[uv] = bandwidth[v * n + u] = bandwidth_uv;
        degree[u]--;
        degree[v]--;
    }

    // Here, we iterate over the sorted edges, and for each edge, we find the endpoint with the highest remaining degree. We then assign the edge a bandwidth equal to the difference in degrees of its endpoints, and update the degrees of the endpoints. We also store the bandwidth of each edge in a vector<int>.
    // Finally, we output the bandwidth of each edge
    // Here, we iterate over all edges in the original adjacency list, and for each edge, we output its endpoints and its bandwidth.
    // Output bandwidth of each edge
    for (int u = 1; u <= n; u++) {
        for (auto v : adj[u]) {
            if (u < v) {
                cout << u << " " << v << " " << bandwidth[u * n + v] << endl;
            }
        }
    }

    return 0;
}
