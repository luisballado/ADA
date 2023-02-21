#include <iostream>
#include <vector>
#include <stack>

//mi gcc en linux no es una version reciente
//usar la bandera -std=c++11 para compilar con versiones recientes de c++
//g++ -std=c++11 tarea4_contenedores.cpp -o contenedor

//const nos permite declarar constantes de una manera más adecuada
const int CONTENEDORES = 3;
const int LITROS_OBJETIVOS = 2;

//Definir el estado inicial de los contenedores
std::vector<int> estado_inicial = {0, 7, 4};

// funcion de parada para revisar si los elementos 2 y 3 de la lista de adyacencia cumplen con la condicion objetivo
bool cumple_objetivo(const std::vector<int>& estado) {
  if(estado.at(1) == LITROS_OBJETIVOS || estado.at(2) == LITROS_OBJETIVOS)
    return true;
  else
    return false;
}

// funcion para hacer el vaciado de litros
// regresamos el vector con el estado modificado
std::vector<int> vaciar(const std::vector<int>& estado, int c_procedencia, int c_destino) {
  std::vector<int> cambio_estado(estado);
  int espacio = CONTENEDORES - c_destino;
  int litros = std::min(espacio, estado[c_procedencia]);
  cambio_estado.at(c_procedencia) -= litros;
  cambio_estado.at(c_destino) += litros;
  return cambio_estado;
}

// Algoritmo iterativo DFS
bool dfs() {

  std::stack<std::vector<int>> pila; //pila dfs
  pila.push(estado_inicial);  //agregar el primer estado
  std::vector<std::vector<int>> visitado; //vector para indicar visitados
  
  //hacer hasta que la pila este vacia
  while (!pila.empty()) {
    //tomar el vector de los estados de la pila
    std::vector<int> estado = pila.top();
    pila.pop(); //quitar de pila
    
    //revisar si el estado cumple con los requisitos
    if (cumple_objetivo(estado)) {
      return true;
    }
    
    //agregar el estado actual a visitados
    visitado.push_back(estado);

    //ciclos for para jugar con las posiciones de los 3 contenedores
    //y conocer nuevos estados
    for (int i = 0; i < CONTENEDORES; i++) {
      for (int j = 0; j < CONTENEDORES; j++) {
	if (i != j) {
	  //intercambiar liquidos
	  std::vector<int> nuevo_estado = vaciar(estado, i, j);
	  bool es_nuevo_estado = true;
	  //revisar si realmente es un nuevo estado
	  for (int k = 0; k < visitado.size(); k++) {
	    if (visitado.at(k) == nuevo_estado) {
	      es_nuevo_estado = false;
	      break;
	    }
	  }
	  //agregar a pila si es nuevo estado
	  if (es_nuevo_estado) {
	    pila.push(nuevo_estado);
	  }
	}
      }
    }
  }
  return false;
}

int main() {

  //correr dfs
  bool hay_solucion = dfs();

  if (hay_solucion) {
    std::cout << "Si existe un camino donde quedan " << LITROS_OBJETIVOS << " litros en los contenedores" << std::endl;
  } else {
    std::cout << "No existe un camino donde quedan " << LITROS_OBJETIVOS << " litros en los contenedores" << std::endl;
  }

  return 0;

}
