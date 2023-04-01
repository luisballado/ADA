#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

// calcular max bandwidth de cualquier camino en el grafo para un peso de arista dado usando el algoritmo de floyd-warshall
// tip pasar vector como referencia &
// pasar pesos como referencia &
int calc_bandwidth(std::vector<std::vector<int>> grafo, std::vector<int> pesos) {

  int n = grafo.size();

  std::vector<std::vector<int>> dist(n, std::vector<int>(n, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      dist[i][j] = (i == j ? 0 : INT_MAX);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j : grafo[i]) {
      dist[i][j] = pesos[i] + pesos[j];
      dist[j][i] = dist[i][j];
    }
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	dist[i][j] = std::min(dist[i][j], std::max(dist[i][k], dist[k][j]));
      }
    }
  }

  int max_bw = 0;

  for (int i = 0; i < n; i++) {
    for (int j : grafo[i]) {
      max_bw = std::max(max_bw, dist[i][j]);
    }
  }

  return max_bw;

}

// buscar solucion fuerza bruta
// generando todas las posibles permutaciones usando next_permutation y seleccionando el resultado con el pequeño max bandwidth
void solucion(std::vector<std::vector<int>> grafo, int m) {

  int n = grafo.size();
  
  //vector de pesos
  std::vector<int> pesos(m);

  //asignar pesos
  for (int i = 0; i < m; i++) {
    pesos[i] = i + 1;
  }
  
  int mejor_bw = INT_MAX; //infinito
  
  //mejor solucion
  std::vector<int> mejor_peso;
  
  do {
    
    int bw = calc_bandwidth(grafo, pesos);
    
    if (bw < mejor_bw) {
      mejor_bw = bw;
      mejor_peso = pesos;
    }
    
  } while (next_permutation(pesos.begin(), pesos.end()));
  //https://www.geeksforgeeks.org/stdnext_permutation-prev_permutation-c/
  
  //Resultados
  std::cout << "bandwidth: " << mejor_bw << std::endl;
  std::cout << "Pesos optimos: ";
  
  // mostrar la mejor secuencia
  for (int w : mejor_peso) {
    std::cout << w << " ";
  }
  
  std::cout << std::endl;
  
}

// Main
int main(int argc, char *argv[]) {
  
  if (argc < 2) {
    std::cout << "Error: " << argv[0] << " falta el archivo" << std::endl;
    return 1;
  }

  std::ifstream fin(argv[1]);

  if (!fin) {
    std::cout << "Error: no se puede abrir el archivo " << argv[1] << std::endl;
    return 1;
  }

  int n, m;

  //asignar n, m
  fin >> n >> m;

  //representar grafo no dirigido
  std::vector<std::vector<int>> grafo(n);

  //crear grafo
  for (int i = 0; i < m; i++) {
    int u, v;
    fin >> u >> v;
    grafo[u].push_back(v);
    grafo[v].push_back(u);
  }

  solucion(grafo,m); //calcular edge-bandwidth
  
  return 0;
}
