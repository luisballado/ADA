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
  std::cout << "RANDOM LABEL" << std::endl;
}

void Graph::sequential_label(){
  std::cout << "SEQUENTIAL LABEL" << std::endl;

  for(int i=0;i<lista_aristas.size();i++){
    bandwidth[i] = i+1;
  }
  
  for (int i = 0; i < lista_aristas.size(); i++){
    std::cout << "ARISTA: "
	      << lista_aristas[i].first << "," << lista_aristas[i].second
	      << " PESO: " << bandwidth[i] << std::endl;
  };
}

void Graph::greedy_label(){
  std::cout << "GREEDy LABEL" << std::endl;
}

void Graph::evaluate(){
  std::cout << "EVALuATE" << std::endl;
}
