#include "Graph.h"

/*****************************************
 * AQUI DEFINO LOS METODOS
 * AQUI SE PROGRAMA LO QUE HACEN C/U
 ****************************************/

Graph::Graph(){
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
  map_lista_aristas.clear();
  lista_aristas.clear();
  bandwidth.clear();
}

//tipo garbage collector
Graph::~Graph(){
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
  map_lista_aristas.clear();
  lista_aristas.clear();
  bandwidth.clear();
}

void Graph::split(std::string line, std::vector<int> & res){
  size_t strPos = line.find(" ");
  size_t lastPos = 0;
  int value;
  while(strPos != std::string::npos){
    //string to int
    value = stoi(line.substr(lastPos, strPos - lastPos));
    res.push_back(value);
    lastPos = strPos + 1;
    strPos = line.find(" ", lastPos);
  }
  res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

void Graph::loadGraph(std::istream &input){
  /**
     std::cout << "LOAD DATA-RECIBI:::" << std::endl;
  **/
  
  std::string line;
  int i = 0;

  while(std::getline(input, line)){
    // la primer linea es un comentario
    if(i == 0){
      i++;
      continue;
    }
    if(i == 1){
      std::vector<int> result;
      split(line, result);
      
      numNodes = result[0];
      numEdges = result[1];

      /***
      std::cout << "VERTICES: " << numNodes
		<< " | EDGES: " << numEdges
		<< std::endl;
      ***/

      adjList.resize(numNodes+1);
      bandwidth.resize(numEdges);
      
      i++;
      continue;
    }

    std::vector<int> result;
    try{
      split(line,result);
    }catch(const std::invalid_argument& ia){
      system("clear");
      std::cout << "\n Argumento Invalido encontrado en la línea: "
		<< i+1 << " \n sólo se aceptan números:: "
		<< line << std::endl;
      exit(-1);
    }catch(...){
      std::cout << "ERROR AQUI" << std::endl;
      exit(-1);
    }
    
    int nodoU = result[0];
    int nodoV = result[1];

    /**
    std::cout << "nodoU: " << nodoU << "nodoV: " << nodoV<< std::endl;
    **/
    
    adjList[nodoU].push_back(nodoV);
    adjList[nodoV].push_back(nodoU);

    if(nodoU<nodoV){
      map_lista_aristas.insert(std::make_pair(std::make_pair(nodoU,nodoV),i));
      lista_aristas.push_back(std::make_pair(nodoU,nodoV));
    }
    
    //Crear aqui tambien lista de aristas
    
    i++;
  }
  
}

void Graph::print_edges(){
  std::cout << "-------------------------" << std::endl;
  std::cout << "EDGES" << std::endl;
  std::cout << "-------------------------" << std::endl;
  
  for (int i = 0; i < lista_aristas.size(); i++){
    std::cout << i+1 << " :" << lista_aristas[i].first
	      << "," << lista_aristas[i].second << std::endl;
  };

  std::cout << "-------------------------" << std::endl;
}

void Graph::print_graph(){
  std::cout << "-------------------------" << std::endl;
  std::cout
    << "numNode: " << numNodes
    << " | "
    << "numEdges: " << numEdges
    << std::endl;
  std::cout << "-------------------------" << std::endl;
  std::cout << "LISTA ADJ" << std::endl;
  std::cout << "-------------------------" << std::endl;
  for(int nodeU = 1; nodeU <= numNodes; nodeU++){
    std::cout << "vertex " << nodeU << " --> [";
    for(int j = 0; j < adjList[nodeU].size(); j++){
      std::cout << adjList[nodeU][j] << " ";
    }
    std::cout << "]" << std::endl;
  }
  std::cout << "-------------------------" << std::endl;
}

void Graph::random_label(){
  std::cout << "-------------------------" << std::endl;
  std::cout << "RANDOM LABEL" << std::endl;
  std::cout << "-------------------------" << std::endl;

  for(int i=0;i<lista_aristas.size();i++){
    bandwidth[i] = rand() % lista_aristas.size() + 1;
  }
  
  for (int i = 0; i < lista_aristas.size(); i++){
    std::cout << "ARISTA: "
	      << lista_aristas[i].first << "," << lista_aristas[i].second
	      << " PESO: " << bandwidth[i] << std::endl;
  };
  std::cout << "-------------------------" << std::endl;
  
}

void Graph::sequential_label(){
  std::cout << "-------------------------" << std::endl;
  std::cout << "SEQUENTIAL LABEL" << std::endl;
  std::cout << "-------------------------" << std::endl;

  for(int i=0;i<lista_aristas.size();i++){
    bandwidth[i] = i+1;
  }
  
  for (int i = 0; i < lista_aristas.size(); i++){
    std::cout << "ARISTA: "
	      << lista_aristas[i].first << "," << lista_aristas[i].second
	      << " PESO: " << bandwidth[i] << std::endl;
  };
  std::cout << "-------------------------" << std::endl;
}

void Graph::greedy_label(){
  std::cout << "-------------------------" << std::endl;
  std::cout << "GREEDy LABEL" << std::endl;
  std::cout << "-------------------------" << std::endl;
  for(int nodeU = 1; nodeU <= numNodes; nodeU++){
    //for (int i = 0; i < numNodes; i++) {
    grados.push_back(std::make_pair(adjList[nodeU].size(), nodeU));
  }
  
  // reverse vector nlog(n)
  // https://www.geeksforgeeks.org/vector-rbegin-and-rend-function-in-c-stl/
  sort(grados.rbegin(), grados.rend());

  std::cout << "NODO-GRADO" << std::endl;
  std::cout << "-------------------------" << std::endl;
  //imprimir nodo-grado
  for (int i = 0; i < grados.size(); i++){
    std::cout << "NODO: " << grados[i].second
	      << " GRADO:" << grados[i].first << std::endl;
  }
  
}

void Graph::evaluate(){
  std::cout << "EVALuATE" << std::endl;
  
  for(int i=0; i<numNodes; i++){
    for(int j=0; j<adjList[i].size(); j++){
      
      //el primer par es pivote
      aux_pivote = std::make_pair(i, adjList[i][j]);
      aux_pivote2 = std::make_pair(adjList[i][j],i);
      int val1,val2;
      int max_bw;
      //iterar dentro del vector y formar nuevos pares
      for(int k=j+1;k<adjList[i].size();k++){
	if(map_lista_aristas[aux_pivote] == 0){
	  std::cout << "(" <<  aux_pivote.first << "," << aux_pivote.second << ">>" << bandwidth[map_lista_aristas[aux_pivote2]] << ") - (";
	  val1 = bandwidth[map_lista_aristas[aux_pivote2]];
	}else{
	  std::cout << "(" <<  aux_pivote.first << "," << aux_pivote.second << ">>" << bandwidth[map_lista_aristas[aux_pivote]] << ") - (";
	  val1 = bandwidth[map_lista_aristas[aux_pivote]];
	}
	
	//nuevo par
	aux2_pivote = std::make_pair(i, adjList[i][k]);
	aux2_pivote2 = std::make_pair(adjList[i][k],i);
	if(map_lista_aristas[aux2_pivote] == 0){
	  std::cout << i << "," << adjList[i][k] << ">>" << bandwidth[map_lista_aristas[aux2_pivote2]]  << ")";
	  val2 = bandwidth[map_lista_aristas[aux2_pivote2]];
	}else{
	  std::cout << i << "," << adjList[i][k] << ">>" << bandwidth[map_lista_aristas[aux2_pivote]] << ")";
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

  
}
