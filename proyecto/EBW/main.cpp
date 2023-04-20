#include "Graph.h"
#include <iostream>
#include <sstream>

//COMPILAR
//g++ main.cpp Graph.cpp -o salida

int main(){
  
  //inputInfo trae todo el contenido del archivo
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf();
  
  Graph g;
  g.loadGraph(inputInfo); //cargar elementos a grafo
  g.print_graph(); //imprimir grafo
  g.print_edges(); //imprimir etiquetas ¿?
  //g.random_label(); //imprimir grafo
  g.sequential_label(); //imprimir grafo

  //g.greedy_label(); //imprimir grafo

  g.evaluate(); //imprimir grafo
  
  return 0;
  
}
