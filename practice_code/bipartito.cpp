#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool isBipartite(int start, vector<vector<int>>& adj_list, vector<int>& color) {
    queue<int> q;
    q.push(start);
    color[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj_list[u]) {
            if (color[v] == -1) {
                color[v] = 1 - color[u];
                q.push(v);
            }
            else if (color[v] == color[u]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    // create an adjacency list
    vector<vector<int>> adj_list(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    // initialize color array
    vector<int> color(n, -1);

    // check if the graph is bipartite
    bool bipartite = true;
    for (int u = 0; u < n; u++) {
        if (color[u] == -1) {
            bipartite &= isBipartite(u, adj_list, color);
        }
    }

    if (bipartite) {
        cout << "The graph is bipartite." << endl;
    }
    else {
        cout << "The graph is not bipartite." << endl;
    }

    return 0;
}
