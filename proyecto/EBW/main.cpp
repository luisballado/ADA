#include "Graph.h"
#include <iostream>
#include <sstream>

int main(){
  
  //inputInfo trae todo el contenido del archivo
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf();
  
  //std::cout << inputInfo.str() << std::endl;
  
  Graph g;
  g.loadGraph(inputInfo); //cargar grafo
  g.print_graph(); //imprimir
  g.print_edges();
  g.sequential_label(); //etiquetar de forma sequencial
  g.evaluate();
  g.random_label(); //etiquetar de forma random
  g.evaluate();
  //g.greedy_label();
  //g.evaluate();
  return 0;
  
}
