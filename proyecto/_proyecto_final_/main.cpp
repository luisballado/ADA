#include "Graph.h"
#include <iostream>
#include <sstream>

int main() {
  int cost = 0;
  Graph g;
  
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf();

  g.loadGraph(inputInfo); // cargar grafo
  //g.setConsecutiveLabeling();
  g.setRandomLabeling();
  //g.printLabeling();
  cost = g.getSolutionCost();
  std::cout << "classic solution cost: " << cost << std::endl;
  
  //g.printLabeling(); //imprimir el vector de soluciones
  cost = g.getSolutionCostIncrementally(0, 5);
  std::cout << "incremental solution cost: " << cost << std::endl;

  // Para verificar
  std::cout << std::endl;
  std::cout << "Make swap(0, 5)" << std::endl;
  g.makeSwap(0, 5); //realizar un intercambio entre i,j del vector de soluciones
  //g.printLabeling();
  cost = g.getSolutionCost();
  std::cout << "classic solution cost: " << cost << std::endl;
  
  /*
  g.setRandomLabeling();
  cost = g.getSolutionCost();
  std::cout << "solution cost: " << cost << std::endl;
  */
  
  return 0;
}
