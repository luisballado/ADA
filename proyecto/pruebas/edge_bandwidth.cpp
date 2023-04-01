/****
This implementation first reads in the input and builds the adjacency list and edge list of the graph. 
It then sorts the edges in ascending order of their degrees, 
and assigns labels to each edge in the sorted order. 

Finally, it computes the maximum label difference between adjacent edges to obtain 
the edge bandwidth of the graph.

Note that the greedy algorithm may not always produce an optimal solution, 
but it is often faster than other algorithms that guarantee optimality 
****/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100;

int n, m, bandwidth;
vector<int> adj[MAXN];
vector<pair<int, int>> edges;

int main() {

  //n - m
  cin >> n >> m;
  
  // leer entrada y construir la lista de adyacencia
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
    edges.push_back(make_pair(min(u, v), max(u, v)));
  }
  
  // buscar edges en orden ascendente por su grado
  //nlog(n)
  //https://www.geeksforgeeks.org/sort-algorithms-the-c-standard-template-library-stl/
  sort(edges.begin(), edges.end(), [&](pair<int, int> a, pair<int, int> b) {
				     
				     return adj[a.first].size() + adj[a.second].size() <
				       adj[b.first].size() + adj[b.second].size();
				   });
  
  // asignar etiquetas a los edges
  vector<int> label(m, -1);
  
  for (int i = 0; i < m; i++) {
    
    int u = edges[i].first;
    int v = edges[i].second;
    int j;
    
    for (j = 0; j < i; j++) {
      int u1 = edges[j].first;
      int v1 = edges[j].second;

      if ((u == u1 || u == v1 || v == u1 || v == v1) && abs(label[j] - i) <= n-2) {
	break; // hay un conflicto
      }
    }
    
    label[i] = j;

  }
  
  // Calcular edge bandwidth
  for (int i = 0; i < m-1; i++) {

    for (int j = i+1; j < m; j++) {
      int u1 = edges[i].first;
      int v1 = edges[i].second;
      int u2 = edges[j].first;
      int v2 = edges[j].second;

      if (u1 == v1 || u2 == v2) {
	continue;
      }

      int bandwidth1 = abs(label[i] - label[j]);
      int bandwidth2 = n - bandwidth1 - 2;

      bandwidth = max(bandwidth, max(bandwidth1, bandwidth2));
    }
  }
  
  cout << "El edge bandwidth del grafo es " << bandwidth << endl;
    
    return 0;
}
