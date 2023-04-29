#include "Graph.h"
#include <iostream>
#include <sstream>

int main() {
  int cost = 0;
  Graph g;
  
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf();

  bool show = false;
  
  g.loadGraph(inputInfo); // cargar grafo
  g.setConsecutiveLabeling();
  
  //g.setRandomLabeling();
  //g.printLabeling();
  if(show){
    std::cout << "vector de solución antes de swap" << std::endl;
    g.printLabeling();
  }
  cost = g.getSolutionCost(show);
  
  std::cout << "classic solution cost: " << cost << std::endl;
  
  //g.makeSwap(0, 5); //realizar un intercambio entre i,j del vector de soluciones
  cost = g.getSolutionCostSwap(0,5,show);  //hacer el intercambio y calcular solo los pares i,j para compararlos y ver si cambiaron
  
  
  if(show){
    std::cout << "vector de solución despues de swap" << std::endl;
    g.printLabeling(); //imprimir el vector de soluciones
  }
    //cost = g.getSolutionCost();
  
  std::cout << "incremental solution cost: " << cost << std::endl;
  
  
  /*
  g.setRandomLabeling();
  cost = g.getSolutionCost();
  std::cout << "solution cost: " << cost << std::endl;
  */
  
  return 0;
}
