// SI _GRAPH_H no esta definido, se define
#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "EdgeInfo.h"

#define INF 0x3f3f3f3f 

class Graph {
//Atributos
private:
  int numNodes;
  int numEdges;

  // semilla del generador de numeros aleatorios (time-based)
  unsigned seed;

  // generador de numeros aleatorios (Mersenne Twister 64 bits)
  std::mt19937_64 gen;

  // Lista de adyacencia (vector de vectores)
  std::vector<std::vector<int>> adjList;
  std::map<std::pair<int, int>, EdgeInfo> aristas; //(nodo1,nodo2), ObjetoEdgeInfo
  std::vector<std::map<std::pair<int,int>,EdgeInfo>::iterator> aristaPosition;
  std::vector<std::pair<int, int>> aristasAdyacentes; // (idArista1, idArista2)
  std::vector<int> currentDifferences;
  std::vector<int> solucion;  

  void split(std::string line, std::vector<int> &res);

//métodos públicos
public:
  Graph();
  ~Graph();
  void loadGraph(std::istream &input);
  void printGraph();
  void printLabeling();
  void setConsecutiveLabeling();
  void setRandomLabeling();
  int getSolutionCost();
  int getSolutionCostIncrementally(int u, int v);
  void makeSwap(int u, int v);
};

#endif // _GRAPH_H
