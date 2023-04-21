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

int evaluar(int arista1, int arista2){
  
  int solucion = 0;
  solucion = abs(arista1-arista2);
  
  return solucion;

}

int main(int argc, char* argv[]) {

  //soluciones disponibles
  std::string solucion;

  if(argc <= 1){

    std::cerr << "######################- ERROR -#########################" << std::endl;
    std::cerr << "Faltan argumentos: " << argv[0] << "-solucion <SOLUCION>" << std::endl;
    std::cerr << "Posibles: " << std::endl;
    std::cerr << "-solucion greedy" << std::endl;
    std::cerr << "-solucion naive"  << std::endl;

    exit(-1);
    
  }else{
  
    // recorrer entrada para leer banderas
    for(int i = 1; i < argc; i++){
      if(std::string(argv[i]) == " -solucion" && i + 1 < argc){
	solucion = argv[i+1];

	
	
      }
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
  std::map<std::pair<int, int>,int> map_lista_aristas; //(nodo1,nodo2),peso
  
  //Crear grafo
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--; // vertices 0-index
    grafo[u].push_back(v);
    grafo[v].push_back(u);

    if(u<v){
      //no inicializar con pesos
      //map_lista_aristas <pair,bandwidth_id>
      map_lista_aristas.insert(std::make_pair(std::make_pair(u,v),i));
      lista_aristas.push_back(std::make_pair(u,v)); //agregar 
    }
  }

  for(int i=0;i<lista_aristas.size();i++){
    bandwidth[i] = i+1;
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
  std::cout << "LISTA-ARISTA" << std::endl;

  //imprimir lista_aristas - vector
  for (int i = 0; i < lista_aristas.size(); i++){
    std::cout << i << " :" << lista_aristas[i].first
	      << "," << lista_aristas[i].second << std::endl;
  };
  
  std::cout << "############################" << std::endl;
  std::cout << "LISTA-ARISTA CON PESOS" << std::endl;
  
  for (int i = 0; i < lista_aristas.size(); i++){
    std::cout << "ARISTA: " << lista_aristas[i].first << "," << lista_aristas[i].second << " "
	      << "PESO: " << bandwidth[i] << std::endl;
  };

  /***
  std::cout << "############################" << std::endl;
  std::cout << "LISTA-ARISTA CON MAP" << std::endl;
  
  //lista de aristas map
  for (auto const& arista : map_lista_aristas) {
    std::cout << "arista: (" << arista.first.first << ", " << arista.first.second << ")";
    std::cout << " peso: " << bandwidth[arista.second] << std::endl;
  }
  */
  
  //vector max bandwidth
  std::vector<int> max_bandwidth;
  std::vector<int> gmax_bandwidth;
  
  // ########################SOLUCION NORMAL######################################
  std::pair<int, int> aux_pivote;
  std::pair<int, int> aux_pivote2;

  std::pair<int, int> aux2_pivote;
  std::pair<int, int> aux2_pivote2;

  std::cout << "############################" << std::endl;
  std::cout << "EVALUACION NORMAL" << std::endl;  
  
  for(int i=0; i<n; i++){
    for(int j=0; j<grafo[i].size(); j++){
      
      //el primer par es pivote
      aux_pivote = std::make_pair(i, grafo[i][j]);
      aux_pivote2 = std::make_pair(grafo[i][j],i);
      int val1,val2;
      int max_bw;
      //iterar dentro del vector y formar nuevos pares
      for(int k=j+1;k<grafo[i].size();k++){
	if(map_lista_aristas[aux_pivote] == 0){
	  std::cout << "(" <<  aux_pivote.first << "," << aux_pivote.second << ">>" << bandwidth[map_lista_aristas[aux_pivote2]] << ") - (";
	  val1 = bandwidth[map_lista_aristas[aux_pivote2]];
	}else{
	  std::cout << "(" <<  aux_pivote.first << "," << aux_pivote.second << ">>" << bandwidth[map_lista_aristas[aux_pivote]] << ") - (";
	  val1 = bandwidth[map_lista_aristas[aux_pivote]];
	}
	
	//nuevo par
	aux2_pivote = std::make_pair(i, grafo[i][k]);
	aux2_pivote2 = std::make_pair(grafo[i][k],i);
	if(map_lista_aristas[aux2_pivote] == 0){
	  std::cout << i << "," << grafo[i][k] << ">>" << bandwidth[map_lista_aristas[aux2_pivote2]]  << ")";
	  val2 = bandwidth[map_lista_aristas[aux2_pivote2]];
	}else{
	  std::cout << i << "," << grafo[i][k] << ">>" << bandwidth[map_lista_aristas[aux2_pivote]] << ")";
	  val2 = bandwidth[map_lista_aristas[aux2_pivote]];
	}
	max_bw = abs(val1-val2);
	max_bandwidth.push_back(max_bw);
	std::cout << "=" << max_bw << std::endl;
      }
    }
  }
  
  //https://www.geeksforgeeks.org/how-to-find-the-maximum-element-of-a-vector-using-stl-in-c/
  std::cout << "\nMAX BANDWIDTH:"
	    << *std::max_element(max_bandwidth.begin(), max_bandwidth.end())
	    << std::endl;

  // ########################SOLUCION NORMAL######################################

  std::cout << "\n############################" << std::endl;
  std::cout << "EVALUACION GREEDY" << std::endl;  
  
  // ########################SOLUCION GREEDY######################################

  std::vector<int> gbandwidth(m, 0);
  
  for(int i=0;i<grados.size();i++){
    gbandwidth[grados[i].second] = i+1;
  }
  
  std::cout << "############################" << std::endl;
  std::cout << "NODO-GRADO" << std::endl;

  //imprimir nodo-grado
  for (int i = 0; i < grados.size(); i++){
    std::cout << "NODO: " << grados[i].second
	      << " GRADO:" << grados[i].first << std::endl;
  }
  
  //Etiquetar respecto al nodo grado
  std::cout << "LISTA ADJ" << std::endl;
  for(int i = 0; i < n; i++){
    std::cout << "NODO " << grados[i].second << " --> [";
    for(int j = 0; j < grafo[grados[i].second].size(); j++){
      std::cout << grafo[grados[i].second][j] << " ";
    }
    std::cout << "]" << std::endl;
  }

  //LISTA ARISTAS

  std::pair<int, int> gpesos;
  //Etiquetar respecto al nodo grado
  std::cout << "LISTA-ARISTAS" << std::endl;
  int count = 1;
  for(int i = 0; i < n; i++){
    //std::cout << "NODO " << grados[i].second << " --> [";
    for(int j = 0; j < grafo[grados[i].second].size(); j++){
      //std::cout << grafo[grados[i].second][j] << " ";
      if(grados[i].second < grafo[grados[i].second][j]){
	gpesos = std::make_pair(grados[i].second, grafo[grados[i].second][j]);
	map_lista_aristas[gpesos] = count;
	bandwidth[count] = count;
	std::cout << "(" << grados[i].second << "," << grafo[grados[i].second][j] << ") - "
		  << map_lista_aristas[gpesos]
		  << std::endl;
	//buscar el par y modificar el peso
	
	count++;
      }
      //buscar el par formado y actualizar su peso
    }
  }
  
  // ########################SOLUCION GREEDY######################################
  //EVALUACION

  //hacer una nueva lista de aristas
  
  std::pair<int, int> gaux_pivote;
  std::pair<int, int> gaux_pivote2;

  std::pair<int, int> gaux2_pivote;
  std::pair<int, int> gaux2_pivote2;

  for(int i = 0; i < n; i++){
    for(int j = 0; j < grafo[grados[i].second].size(); j++){

      //el primer par es pivote
      gaux_pivote = std::make_pair(grados[i].second, grafo[grados[i].second][j]);
      gaux_pivote2 = std::make_pair(grafo[grados[i].second][j],grados[i].second);
      int gval1,gval2;
      int gmax_bw;
      //iterar dentro del vector y formar nuevos pares
      for(int k=j+1;k<grafo[grados[i].second].size();k++){
	if(map_lista_aristas[gaux_pivote] == 0){
	  std::cout << "(" <<  gaux_pivote.first << "," << gaux_pivote.second << ">>" << bandwidth[map_lista_aristas[gaux_pivote2]] << ") - (";
	  gval1 = bandwidth[map_lista_aristas[gaux_pivote2]];
	}else{
	  std::cout << "(" <<  gaux_pivote.first << "," << gaux_pivote.second << ">>" << bandwidth[map_lista_aristas[gaux_pivote]] << ") - (";
	  gval1 = bandwidth[map_lista_aristas[gaux_pivote]];
	}
	
	//nuevo par
	gaux2_pivote = std::make_pair(grados[i].second, grafo[grados[i].second][k]);
	gaux2_pivote2 = std::make_pair(grafo[grados[i].second][k],grados[i].second);
	if(map_lista_aristas[gaux2_pivote] == 0){
	  std::cout << grados[i].second << "," << grafo[grados[i].second][k] << ">>" << bandwidth[map_lista_aristas[gaux2_pivote2]]  << ")";
	  gval2 = bandwidth[map_lista_aristas[gaux2_pivote2]];
	}else{
	  std::cout << grados[i].second << "," << grafo[grados[i].second][k] << ">>" << bandwidth[map_lista_aristas[gaux2_pivote]] << ")";
	  gval2 = bandwidth[map_lista_aristas[gaux2_pivote]];
	}
	gmax_bw = abs(gval1-gval2);
	gmax_bandwidth.push_back(gmax_bw);
	std::cout << "=" << gmax_bw << std::endl;
      }
    }
  }
  
  std::cout << "\nMAX BANDWIDTH:"
	    << *std::max_element(gmax_bandwidth.begin(), gmax_bandwidth.end())
	    << std::endl;
  return 0;

}
