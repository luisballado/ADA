#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<int> bandwidth(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--; // vertices are 0-indexed
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Sort vertices by degree in descending order
    vector<pair<int, int>> deg;
    for (int i = 0; i < n; i++) {
        deg.push_back(make_pair(adj[i].size(), i));
    }
    sort(deg.rbegin(), deg.rend());

    // Assign bandwidth to edges in order of appearance on paths
    int b = 0;
    for (int i = 0; i < n; i++) {
        int u = deg[i].second;
        for (int j = 0; j < adj[u].size(); j++) {
            int v = adj[u][j];
            if (bandwidth[v] == 0) {
                bandwidth[v] = ++b;
            }
        }
    }

    // Print bandwidths of each edge
    for (int u = 0; u < n; u++) {
        for (int j = 0; j < adj[u].size(); j++) {
            int v = adj[u][j];
            cout << u + 1 << " " << v + 1 << " " << abs(bandwidth[u] - bandwidth[v]) << endl;
        }
    }

    return 0;
}
