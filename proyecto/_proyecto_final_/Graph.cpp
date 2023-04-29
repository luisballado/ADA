#include "Graph.h"

// https://www.geeksforgeeks.org/how-to-find-the-maximum-element-of-a-vector-using-stl-in-c/
// https://www.udacity.com/blog/2020/03/c-maps-explained.html
// https://stackoverflow.com/questions/1939953/how-to-find-if-a-given-key-exists-in-a-c-stdmap
// https://www.tutorialspoint.com/how-can-i-clear-console-using-cplusplus

//./main < TestCases/data.txt

///*****************************************
// * AQUI DEFINO LOS METODOS
// * AQUI SE PROGRAMA LO QUE HACEN C/U
// ****************************************/

Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
  aristas.clear();
  aristasAdyacentes.clear();
  solucion.clear();
  aristaPosition.clear();
  // semilla del generador de numeros aleatorios (time-based)
  seed = std::chrono::system_clock::now().time_since_epoch().count();
  // inicializar el generador con la semilla creada
  gen.seed(seed);
}

// tipo garbage collector
Graph::~Graph() {
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
  aristas.clear();
  aristasAdyacentes.clear();
  solucion.clear();
  aristaPosition.clear();
}

void Graph::split(std::string line, std::vector<int> &res) {
  size_t strPos = line.find(" ");
  size_t lastPos = 0;
  int value;
  while (strPos != std::string::npos) {
    // string to int
    value = stoi(line.substr(lastPos, strPos - lastPos));
    res.push_back(value);
    lastPos = strPos + 1;
    strPos = line.find(" ", lastPos);
  }
  res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

void Graph::loadGraph(std::istream &input) {
  /**
     std::cout << "LOAD DATA-RECIBI:::" << std::endl;
  **/

  std::string line;
  int i = 0;
  int index = 0;
  while (std::getline(input, line)) {

    // se omite la primera linea por ser un comentario

    if (i == 0) {
      i++;
      continue;
    }

    // leer el numNodes & numEdges
    if (i == 1) {
      std::vector<int> result;
      split(line, result);

      numNodes = result[0];
      numEdges = result[1];

      // resize respecto al size de numNodes
      adjList.resize(numNodes + 1); //1 basado
      solucion.resize(numEdges);
      aristaPosition.resize(numEdges);
      currentDifferences = std::vector<int>(numEdges, 0);
      
      i++;
      continue;
    }
    
    std::vector<int> result;

    //***********************************************************************
    // * VALIDACION QUE LA ENTRADA SEAN SOLOS NUMEROS
    // **********************************************************************

    try {
      split(line, result);
    } catch (const std::invalid_argument &ia) {
      
      std::cout << "***************************************************"
                << std::endl;
      std::cout << "\n Argumento Invalido encontrado en la línea: " << i + 1
                << " \n sólo se aceptan números:: " << line << std::endl;
      std::cout << "***************************************************"
                << std::endl;
      exit(-1); // terminar programa
    } catch (...) {
      std::cout << "SE DETECTO UN ERROR" << std::endl;
      exit(-1);
    }
    
    //*********************************************************************
    
    int nodoU = result[0]; //valor u
    int nodoV = result[1]; //valor v

    //formar lista de adyacencia
    adjList[nodoU].push_back(nodoV);
    adjList[nodoV].push_back(nodoU);
    
    // nodos unicos
    if (nodoU < nodoV){
      std::pair<std::map<std::pair<int,int>,EdgeInfo>::iterator, bool> ret;
      ret = aristas.insert(std::make_pair(std::make_pair(nodoU,nodoV),EdgeInfo(index))); // map aristas nodoU,nodoV,index
      aristaPosition[index] = ret.first;
    }else{
      std::pair<std::map<std::pair<int,int>,EdgeInfo>::iterator, bool> ret;
      ret = aristas.insert(std::make_pair(std::make_pair(nodoV,nodoU),EdgeInfo(index))); // map aristas nodoU,nodoV,index
      aristaPosition[index] = ret.first;
    }
    i++;
    index++; //index para el objeto EdgeInfo
  } 

  std::pair<int, int> arista1, arista2; //pares de aristas
  
  std::map<std::pair<int,int>,EdgeInfo>::iterator it1, it2; //iterador
  
  // Crear lista de pares aristas comenzando de 1, 
  for (int i = 1; i <= (int)adjList.size(); i++) {
    for (int j = 0; j < (int)adjList[i].size(); j++) {
      // cuidar el u<v para poder encontrarlo
      if (i < adjList[i][j])
        arista1 = std::make_pair(i, adjList[i][j]);
      else
        arista1 = std::make_pair(adjList[i][j], i);
      for (int k = j + 1; k < (int)adjList[i].size(); k++) {
        // cuidar el u<v para poder encontrarlo
        if (i < adjList[i][k])
          arista2 = std::make_pair(i, adjList[i][k]);
        else
          arista2 = std::make_pair(adjList[i][k], i);
        //find - log(n)
        it1 = aristas.find(arista1);
        it2 = aristas.find(arista2);
        //asegurarse que se encontro
        if (it1 != aristas.end() && it2 != aristas.end()) {
          aristasAdyacentes.push_back({it1->second.index,it2->second.index});
          int tmpIndex = aristasAdyacentes.size()-1;
          it1->second.positions.push_back(tmpIndex);
          it2->second.positions.push_back(tmpIndex);
          
        }
      }
    }
  }
  
  
  //std::cout << "currentDifferences size: " << currentDifferences.size() << std::endl;

  
  //Listado de aristas adyacentes por indice
  std::cout << "Aristas adyacentes" << std::endl;
  //O(n)
  for (int i = 0; i < (int)aristasAdyacentes.size(); i++) {
    std::cout << aristasAdyacentes[i].first << ", " << aristasAdyacentes[i].second << std::endl;
  }

  std::map<std::pair<int,int>,EdgeInfo>::iterator it;
  
  std::cout << "aristas contains: " << std::endl;
  //O(n)
  
  for (it=aristas.begin(); it!=aristas.end(); ++it) {
    std::cout << "("<< it->first.first << ", " << it->first.second << ") " << it->second.index << "--";
    //O(m) lista de pares vecinas recorre un vector
    for (int k = 0; k < (int)it->second.positions.size(); k++)
      std::cout << it->second.positions[k] << " ";
    std::cout << std::endl;
  }
  /*
  std::cout << "arista 0: " << std::endl;
  it = aristaPosition[0];
  std::cout << aristaPosition[0]->second.positions[0] << std::endl;
  std::cout << "("<< it->first.first << ", " << it->first.second << ") " << it->second.index << "--" << std::endl;
  std::cout << "arista 5: " << std::endl;
  it = aristaPosition[5];
  std::cout << "("<< it->first.first << ", " << it->first.second << ") " << it->second.index << "--" << std::endl;
  */
}

void Graph::printGraph() {
  std::cout << "-------------------------" << std::endl;
  std::cout << "numNode: " << numNodes << " | "
            << "numEdges: " << numEdges << std::endl;
  std::cout << "-------------------------" << std::endl;
  std::cout << "LISTA ADJ" << std::endl;
  std::cout << "-------------------------" << std::endl;
  //O(n)
  for (int nodeU = 1; nodeU <= numNodes; nodeU++) {
    std::cout << nodeU << " --> [";
    //O(m)
    for (int j = 0; j < (int)adjList[nodeU].size(); j++) {
      std::cout << adjList[nodeU][j] << " ";
    }
    std::cout << "]" << std::endl;
  }
  std::cout << "-------------------------" << std::endl;
}

//imprime el etiquetado de las aristas
void Graph::printLabeling() {
  std::cout << "solution: " << std::endl;
  for (int i = 0; i < (int)solucion.size(); i++)
    std::cout << solucion[i] << ", ";
  std::cout << std::endl;
}

//etiquetado consecutivo respecto al numEdges
void Graph::setConsecutiveLabeling() {
  for (int i = 0; i < (int)solucion.size(); i++)
    solucion[i] = i;
}

//etiquetado random
//O(n) respecto a la cardinalidad de la lista de pares de aristas
void Graph::setRandomLabeling() {
  //se etiqueta de forma secuencial
  for (int i = 0; i < (int)solucion.size(); i++)
    solucion[i] = i;
  
  //reacomodar en posiciones random
  std::shuffle(solucion.begin(), solucion.end(), gen);
}

//obtener la el costo de la solución
//O(n)
int Graph::getSolutionCost() {

  int maxDif = 0;
  
  std::cout << "Evalua solucion" << std::endl;
  
  for (int i = 0; i < (int)aristasAdyacentes.size(); i++) {
    int difAbs = std::abs(solucion[aristasAdyacentes[i].first] - solucion[aristasAdyacentes[i].second]);
    std::cout << "|" << solucion[aristasAdyacentes[i].first] << " - " << solucion[aristasAdyacentes[i].second] << "| = " << difAbs << std::endl;
    currentDifferences[difAbs]++; //costo
    //se queda con el maximo
    if (difAbs > maxDif)
      maxDif = difAbs;
  }
  return maxDif;
}
//hacer un swap
void Graph::makeSwap(int u, int v) {
  std::swap(solucion[u], solucion[v]);  
}

int Graph::getSolutionCostIncrementally(int arista1, int arista2) {
  int maxDif = 0, difAbsOld = 0, difAbsNew = 0;
  std::vector<int> copyCurrentDifferences(currentDifferences);
  int labelArista1, labelArista2;
  int labelNewArista1, labelNewArista2;
  labelArista1 = labelNewArista2 = solucion[arista1];
  labelArista2 = labelNewArista1 = solucion[arista2];
  std::map<std::pair<int,int>,EdgeInfo>::iterator it;
  std::cout << std::endl;
  std::cout << "Evalua solucion incremental" << std::endl;
  it = aristaPosition[arista1];
  std::cout << "Aristas adyacentes implicadas (arista1)" << std::endl;
  for (int k = 0; k < (int)it->second.positions.size(); k++) {
      std::cout << "arista adyacente: " << it->second.positions[k] << std::endl;
      int j = it->second.positions[k];
      std::cout << "aristaA: " << aristasAdyacentes[j].first << " aristaB: " << aristasAdyacentes[j].second << " ";
      if (aristasAdyacentes[j].first == arista1) {
        difAbsOld = std::abs(labelArista1 - solucion[aristasAdyacentes[j].second]);
        difAbsNew = std::abs(labelNewArista1 - solucion[aristasAdyacentes[j].second]);
        std::cout << "A" << std::endl;
        std::cout << "Old: " << difAbsOld << " New: " << difAbsNew << std::endl;
      }
      else {
        difAbsOld = std::abs(solucion[aristasAdyacentes[j].first] - labelArista1);
        difAbsNew = std::abs(solucion[aristasAdyacentes[j].first] - labelNewArista1);
        std::cout << "B" << std::endl;
        std::cout << "Old: " << difAbsOld << " New: " << difAbsNew << std::endl;
      }
      copyCurrentDifferences[difAbsOld]--;
      copyCurrentDifferences[difAbsNew]++;
      
  }
  std::cout << std::endl;
  it = aristaPosition[arista2];
  std::cout << "Aristas adyacentes implicadas (arista2)" << std::endl;
  for (int k = 0; k < (int)it->second.positions.size(); k++) {
      std::cout << "arista adyacente: " << it->second.positions[k] << std::endl;
      int j = it->second.positions[k];
      std::cout << "aristaA: " << aristasAdyacentes[j].first << " aristaB: " << aristasAdyacentes[j].second << " ";
      if (aristasAdyacentes[j].first == arista2) {
        difAbsOld = std::abs(labelArista2 - solucion[aristasAdyacentes[j].second]);
        difAbsNew = std::abs(labelNewArista2 - solucion[aristasAdyacentes[j].second]);
        std::cout << "A" << std::endl;
        std::cout << "Old: " << difAbsOld << " New: " << difAbsNew << std::endl;
      }
      else {
        difAbsOld = std::abs(solucion[aristasAdyacentes[j].first] - labelArista2);
        difAbsNew = std::abs(solucion[aristasAdyacentes[j].first] - labelNewArista2);
        std::cout << "B" << std::endl;
        std::cout << "Old: " << difAbsOld << " New: " << difAbsNew << std::endl;
      }
      copyCurrentDifferences[difAbsOld]--;
      copyCurrentDifferences[difAbsNew]++;
  }
  for (maxDif = numEdges - 1; (copyCurrentDifferences[maxDif]) == 0; maxDif--);
  return maxDif;
}
