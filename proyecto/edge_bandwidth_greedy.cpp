#include <iostream>
#include <vector>
#include <algorithm>

/*****************************************
  1. Leer el numero de Vertices , Aristas y las conexiones
  2. Crear lista de adyacencia y el vector de bandwidth
  3. Actualizar los grados respecto a la lista de adyacencia
  4. Ordenar los grados en orden descendente
  5. Inicializar max_bandwidth a cero
  6. Para cada vertice en en grados
      - Para cada arista adyacente al vertice
         - Si su bandwidth es 0, se le asigna un valor y se actualiza el max_bandwidth
         - Calcular bandwidth de la arista(u,v) y se actualiza el max_bandwidth
  7. Imprimir resultado
 *******************************************/

int main() {
  
  int n, m;

  std::cin >> n >> m;
  
  std::vector<std::vector<int>> grafo(n);
  std::vector<int> bandwidth(m, 0);
  
  //Crear grafo
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--; // vertices 0-index
    grafo[u].push_back(v);
    grafo[v].push_back(u);
  }
  
  //imprimir lista de adj
  for(int i = 0; i < grafo.size(); i++){
    std::cout << "NODO" << i << ":";
    for(int j = 0; j < grafo[i].size(); j++){
      std::cout << grafo[i][j] << " ";
    }
    std::cout << std::endl;
  }
  
  // Ordenar vertices por grado en orden descendente (el de mayor grado primero)
  // https://www.digitalocean.com/community/tutorials/sort-in-c-plus-plus
  std::vector<std::pair<int, int>> grados;

  for (int i = 0; i < n; i++) {
    grados.push_back(std::make_pair(grafo[i].size(), i));
  }
  
  // reverse vector nlog(n)
  // https://www.geeksforgeeks.org/vector-rbegin-and-rend-function-in-c-stl/
  sort(grados.rbegin(), grados.rend());

  for (int i = 0; i < grados.size(); i++){
    std::cout << "NODO: " << grados[i].second
	      << " GRADO:" << grados[i].first << std::endl;
  }

  exit(1);
  
  // Asignar bandwidth a aristas en orden de aparicion
  int max_bandwidth = 0;
  
  // para cada vertice
  for (int i = 0; i < n; i++) {
    int u = grados[i].second; // tomo el vertice 2
    
    //para cada vertices adj
    for (int j = 0; j < grafo[u].size(); j++) {
      
      int v = grafo[u][j];
      std::cout << v << std::endl;
      if (bandwidth[v] == 0) {
	bandwidth[v] = ++max_bandwidth;
	// Calcular bandwidth de arista (u,v)
	int edge_bandwidth = abs(bandwidth[u]-bandwidth[v]);
	max_bandwidth = std::max(max_bandwidth, edge_bandwidth);
      }
      
    }
  }
  
  // Imprimir resultado
  std::cout << max_bandwidth << std::endl;
    
  return 0;
}