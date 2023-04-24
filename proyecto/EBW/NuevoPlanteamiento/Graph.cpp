#include "Graph.h"

//https://www.geeksforgeeks.org/how-to-find-the-maximum-element-of-a-vector-using-stl-in-c/
//https://www.udacity.com/blog/2020/03/c-maps-explained.html
//https://stackoverflow.com/questions/1939953/how-to-find-if-a-given-key-exists-in-a-c-stdmap
//https://www.tutorialspoint.com/how-can-i-clear-console-using-cplusplus

/*****************************************
 * AQUI DEFINO LOS METODOS
 * AQUI SE PROGRAMA LO QUE HACEN C/U
 ****************************************/

Graph::Graph(){
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
  map_aristas.clear();
  peso_arista.clear();
}

//tipo garbage collector
Graph::~Graph(){
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
  map_aristas.clear();
  peso_arista.clear();
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
  int index = 0;
  while(std::getline(input, line)){
    
    // se omite la primera linea por ser un comentario
    
    if(i == 0){
      i++;
      continue;
    }

    // leer el numNodes & numEdges
    if(i == 1){
      std::vector<int> result;
      split(line, result);
      
      numNodes = result[0];
      numEdges = result[1];

      //resize respecto al size de numNodes
      adjList.resize(numNodes+1);
      peso_arista.resize(numEdges);
      
      i++;
      continue;
    }

    std::vector<int> result;

    /***********************************************************************
     * VALIDACION QUE LA ENTRADA SEAN SOLOS NUMEROS
     **********************************************************************/

    try{
      split(line,result);
    }catch(const std::invalid_argument& ia){
      system("clear");
      std::cout << "***************************************************" << std::endl;
      std::cout << "\n Argumento Invalido encontrado en la línea: "
		<< i+1 << " \n sólo se aceptan números:: " << line << std::endl;
      std::cout << "***************************************************" << std::endl;
      exit(-1); //terminar programa
    }catch(...){
      std::cout << "SE DETECTO UN ERROR" << std::endl;
      exit(-1);
    }

    //**********************************************************************

    //ir leyendo u,v
    int nodoU = result[0];
    int nodoV = result[1];
    
    //std::cout << "nodoU: " << nodoU << "nodoV: " << nodoV<< std::endl;
        
    adjList[nodoU].push_back(nodoV);
    adjList[nodoV].push_back(nodoU);

    //nodos unicos
    if(nodoU<nodoV){
      //map aristas nodoU,nodoV,index
      map_aristas.insert(std::make_pair(std::make_pair(nodoU,nodoV),index));
    }
    
    i++;
    index++;
  }

  std::pair<int,int> pareja1;
  std::pair<int,int> pareja2;
  
  //Crear lista de pares aristas
  for (int i = 0; i < adjList.size(); i++) {
    for (int j = 0; j < adjList[i].size(); j++) {

      //cuidar el u<v para poder encontrarlo
      if(i<adjList[i][j]){
	pareja1 = std::make_pair(i,adjList[i][j]);
      }else{
	pareja1 = std::make_pair(adjList[i][j],i);
      }
      
      for(int k=j+1; k< adjList[i].size();k++){
	
	//cuidar el u<v para poder encontrarlo
	if(i<adjList[i][k]){
	  pareja2 = std::make_pair(i,adjList[i][k]);
	}else{
	  pareja2 = std::make_pair(adjList[i][k],i);
	}

	//lista de pares normal
	edge_pairs.push_back(std::make_pair(pareja1,pareja2));

	auto id0 = map_aristas.find(pareja1);
	auto id1 = map_aristas.find(pareja2);

	//lista de pares con indices
	edge_pairs_simple.push_back(std::make_pair(id0->second,id1->second));

      }
    }
  }
}

void Graph::print_list_pair_edges(){

  std::cout << "-------------------------" << std::endl;
  std::cout << "LISTA PARES ARISTAS" << std::endl;
  std::cout << "-------------------------" << std::endl;
  
  // loop over each edge and print its vertices
  for (const auto& edge_pair : edge_pairs) {
    std::cout << "(" << edge_pair.first.first << ", " << edge_pair.first.second << ") - ";
    std::cout << "(" << edge_pair.second.first << ", " << edge_pair.second.second << ")"
	      << std::endl;
  }

  std::cout << "-----------------------------" << std::endl;
  std::cout << "LISTA PARES ARISTAS INDICES" << std::endl;
  std::cout << "-----------------------------" << std::endl;

  for (const auto& edge_pair : edge_pairs_simple) {
    std::cout << "(" << edge_pair.first << " - " << edge_pair.second << ")" << std::endl;
  }
  
  
  
  std::cout << "-------------------------" << std::endl;
}

void Graph::print_edges(){
  std::cout << "-------------------------" << std::endl;
  std::cout << "ARISTAS" << std::endl;
  std::cout << "-------------------------" << std::endl;

  int indx = 0;
  for(auto it = map_aristas.begin(); it != map_aristas.end();it++){
    std::cout << "index: " << it->second << " - (" << it->first.first << "," << it->first.second << ")" << std::endl;
  }
    
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
    std::cout << nodeU << " --> [";
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

  for(int i=0;i<map_aristas.size();i++){
    peso_arista[i] = rand() % map_aristas.size() + 1;
  }

  for(auto it = map_aristas.begin(); it != map_aristas.end();it++){
    std::cout << "(" << it->first.first << "," << it->first.second << ") - "
	      << peso_arista[it->second] 
	      << std::endl;
  }

  std::cout << "-------------------------" << std::endl;
  
}

void Graph::sequential_label(){
  std::cout << "-------------------------" << std::endl;
  std::cout << "SEQUENTIAL LABEL" << std::endl;
  std::cout << "-------------------------" << std::endl;

  for(int i=0;i<map_aristas.size();i++){
    peso_arista[i] = i+1;
  }

  int indx = 0;
  for(auto it = map_aristas.begin(); it != map_aristas.end();it++){
    std::cout << "(" << it->first.first << "," << it->first.second << ") - "
	      << peso_arista[it->second] 
	      << std::endl;
    indx++;
  }
  
    
  std::cout << "-------------------------" << std::endl;
}

//O(P)
void Graph::classic_evaluation(){

  std::cout << "-------------------------" << std::endl;
  std::cout << "EVALUACION CLASICA" << std::endl;
  std::cout << "-------------------------" << std::endl;
  
  int max_bw;
  
  for (const auto& edge_pair : edge_pairs_simple) {
    max_bw = abs(peso_arista[edge_pair.first] - peso_arista[edge_pair.second]);
    max_bandwidth.push_back(max_bw);
    
    std::cout << "(" << peso_arista[edge_pair.first]
	      << " - "
	      << peso_arista[edge_pair.second]
	      << ") = " << max_bw
	      << std::endl;
  };

  std::cout << "\nMAX BANDWIDTH:"
	    << *std::max_element(max_bandwidth.begin(), max_bandwidth.end())
	    << std::endl;

}

void Graph::make_swap(int i, int j){

  std::swap(peso_arista[i],peso_arista[j]);
  
}

//O(w+p)
void Graph::incremental_evaluation(){
  
}
