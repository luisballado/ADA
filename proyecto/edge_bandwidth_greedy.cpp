#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

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

int main(int argc, char* argv[]) {

  //soluciones disponibles
  std::string solucion;

  if(argc <= 1){

    std::cerr
      << "######################- ERROR -#########################"
      << std::endl;
    std::cerr
      << "Faltan argumentos: "
      << argv[0]
      << "-solucion <SOLUCION>"
      << std::endl;
    std::cerr
      << "Posibles: "
      << std::endl;
    std::cerr
      << "-solucion greedy"
      << std::endl;
    std::cerr
      << "-solucion naive"
      << std::endl;

    exit(-1);
    
  }else{
  
    // recorrer entrada para leer banderas
    for(int i = 1; i < argc; i++){
      if(std::string(argv[i]) == " -solucion" && i + 1 < argc)
	solucion = argv[i+1];
    }
  }
  
  int n, m;

  std::cin >> n >> m;
  
  std::vector<std::vector<int>> grafo(n);

  //cada arista tendra su etiqueta
  //vector solucion
  //tiene el peso de la arista, se indexa respecto a la lista de aristas
  std::vector<int> bandwidth(m, 0);

  //lista de aristas
  std::vector<std::pair<int, int>> lista_aristas;
  //std::map<std::pair<int, int>,int> lista_aristas; //(nodo1,nodo2),peso
  
  //Crear grafo
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--; // vertices 0-index
    grafo[u].push_back(v);
    grafo[v].push_back(u);

    if(u<v){
      //lista_aristas.insert(std::make_pair(std::make_pair(u,v),i+1));
      lista_aristas.push_back(std::make_pair(u,v)); //agregar
      bandwidth[i] = i+1;
    }
    
  }
  
  //imprimir lista de adj
  std::cout << "############################" << std::endl;
  std::cout << "LISTA ADJ" << std::endl;
  for(int i = 0; i < grafo.size(); i++){
    std::cout << "NODO " << i << " --> [";
    for(int j = 0; j < grafo[i].size(); j++){
      std::cout << grafo[i][j] << " ";
    }
    std::cout << "]" << std::endl;
  }
  
  //crear lista de aristas
  //depreciado por ser n*n
  /**
  for(int i = 0; i < grafo.size(); i++){
    for(int j = 0; j < grafo[i].size(); j++){
      if(i<grafo[i][j]){
	lista_aristas.push_back(std::make_pair(i, grafo[i][j])); //agregar
      }
    }
  }
  */
    
  // Ordenar vertices por grado en orden descendente (el de mayor grado primero)
  // https://www.digitalocean.com/community/tutorials/sort-in-c-plus-plus
  //size, nodo
  std::vector<std::pair<int, int>> grados;
  
  for (int i = 0; i < n; i++) {
    grados.push_back(std::make_pair(grafo[i].size(), i));
  }
  
  // reverse vector nlog(n)
  // https://www.geeksforgeeks.org/vector-rbegin-and-rend-function-in-c-stl/
  sort(grados.rbegin(), grados.rend());

  std::cout << "############################" << std::endl;
  std::cout << "NODO-GRADO" << std::endl;
  //imprimir nodo-grado
  for (int i = 0; i < grados.size(); i++){
    std::cout << "NODO: " << grados[i].second
	      << " GRADO:" << grados[i].first << std::endl;
  };

  std::cout << "############################" << std::endl;
  std::cout << "LISTA-ARISTA" << std::endl;

  //imprimir lista_aristas - vector
  for (int i = 0; i < lista_aristas.size(); i++){
    std::cout << i << " :" << lista_aristas[i].first
	      << "," << lista_aristas[i].second << std::endl;
  };

  for (int i = 0; i < bandwidth.size(); i++){
    std::cout << lista_aristas[i].first << "," << lista_aristas[i].second
	      << " PESO:" << bandwidth[i] << std::endl;
  };
  
  //lista de aristas map
  /***
  for (auto const& arista : lista_aristas) {
    std::cout << "arista: (" << arista.first.first << ", " << arista.first.second << ")";
    std::cout << " peso: " << arista.second << std::endl;
  }
  **/
  
  int max_bandwidth = 0;
  
  // Asignar bandwidth a aristas en orden de aparicion
  // para cada vertice
  for (int i = 0; i < n; i++) {
    int u = grados[i].second; // tomo el vertice 2
    
    //para cada vertices adj
    for (int j = 0; j < grafo[u].size(); j++) {
      int v = grafo[u][j];
      //std::cout << v << std::endl;
      if (bandwidth[v] == 0) {
	bandwidth[v] = ++max_bandwidth;
	// Calcular bandwidth de arista (u,v)
	int edge_bandwidth = abs(bandwidth[u]-bandwidth[v]);
	max_bandwidth = std::max(max_bandwidth, edge_bandwidth);
      }
    }
  }
  

  //print bandwidths of each edge
  for(int u=1; u<n; u++){
    for(int j=0;j<grafo[u].size();j++){
      int v = grafo[u][j];
      std::cout << u << " " << v << abs(bandwidth[u] - bandwidth[v]) << std::endl;
    }
  }
  
  // Imprimir resultado
  std::cout << max_bandwidth << std::endl;
    
  return 0;
}
