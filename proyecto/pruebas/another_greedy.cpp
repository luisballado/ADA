#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

vector<int> adj[MAXN];
int bandwidth[MAXN];

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Sort vertices by degree in descending order
    vector<pair<int, int>> deg;
    for (int i = 1; i <= n; i++) {
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
    for (int u = 1; u <= n; u++) {
        for (int j = 0; j < adj[u].size(); j++) {
            int v = adj[u][j];
            cout << u << " " << v << " " << abs(bandwidth[u] - bandwidth[v]) << endl;
        }
    }

    return 0;
}
