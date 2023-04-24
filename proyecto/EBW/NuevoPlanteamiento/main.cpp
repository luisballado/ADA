#include "Graph.h"
#include <iostream>
#include <sstream>

int main(){
  system("clear");
    
  Graph g;
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf();

  g.loadGraph(inputInfo); //cargar grafo
  g.print_graph(); //imprimir
  g.print_edges();
  g.sequential_label(); //etiquetar de forma sequencial
  g.print_list_pair_edges();
  g.classic_evaluation();
  //g.random_label(); //etiquetar de forma random
  g.make_swap(0,8);
  g.classic_evaluation();
  
  return 0;
  
}
