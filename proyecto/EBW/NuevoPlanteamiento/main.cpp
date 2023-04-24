#include "Graph.h"
#include <iostream>
#include <sstream>

int main(){
  system("clear");
  int opcion;
  bool running = true;
  
  
  std::cout << "----------------------------------------" << std::endl;
  std::cout << "1. Imprimir lista adyacencia" << std::endl;
  std::cout << "2. Imprimir aristas" << std::endl;
  std::cout << "3. Imprimir lista de pares de aristas" << std::endl;
  std::cout << "4. Etiquetar aristas secuencialmente" << std::endl;
  std::cout << "5. Etiquetar aristas random" << std::endl;
  std::cout << "6. Evaluar EBW" << std::endl;
  std::cout << "7. Salir" << std::endl;
  std::cout << "----------------------------------------" << std::endl;
  std::cout << "Ingresa una opción" << std::endl;
  std::cin >> opcion;

  //inputInfo trae todo el contenido del archivo
  
  Graph g;
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf();
  switch(opcion){
  case 0:
    
  case 1:
        
    g.loadGraph(inputInfo); //cargar grafo
    system("clear");
    std::cout << "LISTA DE ADYACENCIA" << std::endl;
    g.print_graph(); //imprimir
    break;
  case 2:
    std::cout << "ARISTAS UNICAS" << std::endl;
    g.print_edges();
    break;
  case 3:
    std::cout << "LISTA DE PARES DE ARISTAS" << std::endl;
    g.print_list_pair_edges();
    break;
  case 4:
    std::cout << "ETIQUETADO SECUENCIAL" << std::endl;
    g.sequential_label(); //etiquetar de forma sequencial
    break;
  case 5:
    std::cout << "ETIQUETADO RANDOM" << std::endl;
    g.random_label(); //etiquetar de forma random
    break;
  case 6:
    std::cout << "EVALUAR EBW" << std::endl;
    break;
  case 7:
    std::cout << "SALIENDO..." << std::endl;
    exit(-1);
    break;
  default:
    std::cout << "OPCION NO VALIDA" << std::endl;
    break;
  }

  return 0;
  
}
