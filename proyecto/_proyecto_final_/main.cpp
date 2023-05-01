#include "Graph.h"
#include <iostream>
#include <sstream>

int main() {

  Graph g;
  
  //Costos 
  int costClassic = 0;
  int costIncremental = 0;
  
  std::vector<int> resultados_clasico;
  std::vector<int> resultados_incremental;

  int c_operations_count = 0;
  int i_operations_count = 0;
  
  // ******* CARGAR GRAFO ********
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf();
  g.loadGraph(inputInfo);
  // *****************************

  std::vector<int> graphInfo;
  graphInfo = g.getGraphInfo();
  int numNodes = graphInfo[0];
  int numEdges = graphInfo[1];
  
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  int maxDifC = 0;
  
  // ******************** EVALUACION CLASICA ******************************
  for(int i = 0; i < 100; i++){
    g.setRandomLabeling(); //efectuar un etiquetado random
    resultados_clasico = g.getSolutionCost(); //obtener el vect de resultados
    c_operations_count = resultados_clasico[0] + c_operations_count; //operaciones basicas
    costClassic = resultados_clasico[1]; //obtener el costo de la ejecucion

    //Nos quedamos con el mejor hasta ahora
    if(costClassic > maxDifC)
      maxDifC = costClassic;
    
  }
  
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Evaluación Clásica  " << std::endl;
  std::cout << "Núm Nodes:  " << numNodes << std::endl;
  std::cout << "Núm Edges:  " << numEdges << std::endl;
  std::cout << "Mejor Costo encontrado: " << maxDifC << std::endl;
  std::cout << "Operaciones: " << c_operations_count << std::endl;
  std::cout << "Tiempo Ejecucion: " << std::endl;
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()<< "[µs]" << std::endl;
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
  std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;
  
  // *********************************************************************

  /***
  //g.printLabeling(); //imprimir el vector de soluciones
  cost = g.getSolutionCostIncrementally(0, 5);
  std::cout << "incremental solution cost: " << cost << std::endl;
  // Para verificar
  std::cout << std::endl;
  std::cout << "Make swap(0, 5)" << std::endl;
  g.makeSwap(0, 5); //realizar un intercambio entre i,j del vector de soluciones
  **/

  /**************** EVALUACION INCREMENTAL *********************************/
  std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now(); 
  
  int maxDifI = 0;

  g.setRandomLabeling();
  
  for(int j = 0; j < 99; j++){
    int a = g.getRandomNumber(); //obtener un num random entre 0,soluciones-1
    int b = g.getRandomNumber();
    
    resultados_incremental = g.getSolutionCostIncrementally(a, b);
    c_operations_count = resultados_incremental[0] + i_operations_count; //operaciones basicas
    costIncremental = resultados_incremental[1];
    
    if(costIncremental > maxDifI)
      maxDifI = costIncremental;
    
  }
  
  std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();

  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Evaluación Incremental  " << std::endl;
  std::cout << "Núm Nodes:  " << numNodes << std::endl;
  std::cout << "Núm Edges:  " << numEdges << std::endl;
  std::cout << "Mejor Costo encontrado: " << maxDifI << std::endl;
  std::cout << "Operaciones: " << c_operations_count << std::endl;
  std::cout << "Tiempo Ejecucion: " << std::endl;
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count()<< "[µs]" << std::endl;
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2).count() << "[ms]" << std::endl;
  std::cout << std::chrono::duration_cast<std::chrono::seconds>(end2 - begin2).count() << "[s]" << std::endl;

  /************************************************************************/

  /***
  //g.printLabeling();
  cost = g.getSolutionCost();
  std::cout << "classic solution cost: " << cost << std::endl;
  **/
  
  /*
  g.setRandomLabeling();
  cost = g.getSolutionCost();
  std::cout << "solution cost: " << cost << std::endl;
  */
  
  return 0;
  
}
