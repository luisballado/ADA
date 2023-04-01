#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

// funcion para calcular la diferencia maxima entre los vertices adjacentes en un camino
int calculate_bandwidth(std::vector<int>& path, std::vector<std::vector<int>>& adj_matrix) {
    int max_diff = 0;
    for (int i = 1; i < path.size(); i++) {
        int diff = abs(path[i] - path[i-1]);
        if (diff > max_diff) {
            max_diff = diff;
        }
    }
    return max_diff;
}

// funcion para calcular el maximo minimo bandwidth -- fuerza bruta
void edge_bandwidth_brute_force(std::vector<std::vector<int>>& adj_matrix, std::vector<int>& edge_weights) {
    int n = adj_matrix.size();
    std::vector<int> vertices(n);
    for (int i = 0; i < n; i++) {
        vertices[i] = i;
    }

    // generar todas las permutaciones posibles
    std::vector<std::vector<int>> all_permutations;
    do {
        all_permutations.push_back(vertices);
    } while (next_permutation(vertices.begin(), vertices.end()));

    // iterar con las permutaciones y calcular el max bandwidth para cada permutacion
    int min_max_bandwidth = INT_MAX; //Value of INT_MAX is 2147483647
    std::vector<int> optimal_edge_weights(n-1);
    for (auto permutation : all_permutations) {
      std::vector<int> path(n);
      for (int i = 0; i < n; i++) {
	path[i] = permutation[i];
      }
      int max_bandwidth = calculate_bandwidth(path, adj_matrix);
      if (max_bandwidth < min_max_bandwidth) {
	min_max_bandwidth = max_bandwidth;
	for (int i = 0; i < n-1; i++) {
	  int u = path[i], v = path[i+1];
	  int edge_index = adj_matrix[u][v];
	  optimal_edge_weights[i] = edge_weights[edge_index];
	}
      }
    }
    
    // resultados
    std::cout << "bandwidth: " << min_max_bandwidth << std::endl;
    std::cout << "Pesos de aristas optimos: ";

    for (int i = 0; i < n-1; i++) {
      std::cout << optimal_edge_weights[i] << " ";
    }
    
    std::cout << std::endl;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  
  // inicializar lista de adyacencia y pesos
  std::vector<std::vector<int>> adj_matrix(n, std::vector<int>(n, -1));
  std::vector<int> edge_weights(m);
  
  // read in edges and weights
  int u, v, weight;
  for (int i = 0; i < m; i++) {
    std::cin >> u >> v >> weight;
    adj_matrix[u][v] = i;
    adj_matrix[v][u] = i;
    edge_weights[i] = weight;
  }
  
  // calculate minimum maximum bandwidth using brute force
  edge_bandwidth_brute_force(adj_matrix, edge_weights);

  return 0;
}
