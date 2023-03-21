#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>

// constante muy grande
double INF = std::numeric_limits<double>::infinity();

// Bellman-Ford para el camino mas corto con ciclos negativos
// adaptado de https://cppsecrets.com/users/166319711511599105105995564103109971051084699111109/C00-Currency-Arbitrage.php
bool bellman_ford(const std::vector<std::vector<double>>& graph, int start, std::vector<double>& dist) {
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
	return false;  // ciclo negativo
      }
    }
  }
  return true;
}

int main() {
  // num de vertices-num de aristas
  int n, m;
  std::cin >> n >> m;
  
  // Inicializar con distancias INF
  std::vector<std::vector<double>> graph(n, std::vector<double>(n, INF));
  
  // Leer la tasa de cambio y situarla al peso de la arista
  for (int i = 0; i < m; ++i) {
    int u, v;
    double rate;
    std::cin >> u >> v >> rate;
    graph[u][v] = std::max(1e-9, rate);  // peso minimo para evitar error en logaritmo de 0
  }
  
  // conocer las monedas a hacer trade
  int s, t;
  std::cin >> s >> t;
  
  // Encontrar la secuencia con mejores ROI
  std::vector<double> dist(n, INF);

  if (bellman_ford(graph, s, dist)) {
    double result = exp(-dist[t]);
    std::cout << "El tipo de cambio ventajoso de la moneda " << s << " a la moneda " << t << " es " << result << std::endl;
  } else {
    std::cout << "Existe un ciclo negativo" << std::endl;
  }
  
  return 0;
  
}
