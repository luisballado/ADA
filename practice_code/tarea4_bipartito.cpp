#include <iostream>
#include <vector>

//funcion que indica si el grafo es o no bipartito
// -1 - no lo es; 0 - es bipartita
int esBipartita(int u, std::vector<int> adj[], std::vector<int>& visitado);

int main() {

  int vertice; //numero de vertices
  int arista;  //numero de aristas

  //default verdadero
  //hasta que la funcion diga lo contrario
  bool es_bipartita = true;

  //ingreasr los datos desde consola
  //Crear el grafo con lista de adjacencia
  //con los valores leidos
  std::cin >> vertice >> arista;

  //se crea un array de vectores con la cardinalidad de vertices(nodos)
  std::vector<int> adj[vertice];

  //ir poblando con la lectura de consola respecto
  //al num de aristas, este indica el num de conexiones en el grafo
  //decimos que existe una conexion entre el nodo 0 y nodo 1 de la siguiente forma: 0 1
  for (int i = 0; i < arista; i++) {
    int v1, v2;  //auxiliares que representan los vertices
    std::cin >> v1 >> v2; 
    adj[v1].push_back(v2); //agregar en dos vias las 
    adj[v2].push_back(v1); //conexiones del grafo
  }
  
  //vector visitado
  //se inicializa con la cardinalidad de vertices(nodos) y todos en -1
  std::vector<int> visitado(vertice, -1);

  //iterar hasta encontrar resultado
  for (int i = 0; i < vertice; i++) {
    if (visitado.at(i) == -1) {
      visitado.at(i) = 0; //marcar como visitado
      if (esBipartita(i, adj, visitado) == -1) {
	es_bipartita = false;
	break;
      }
    }
  }

  // Verificar si la variable cambio para imprimir resultado
  if (es_bipartita) {
    std::cout << "El grafo de entrada es bipartito." << std::endl;
  } else {
    std::cout << "El grafo de entrada no es bipartito." << std::endl;
  }
  
  return 0;
}

/******************************************************************
 * Funcion booleana para indicar si el grafo es bipartito o no
 * param vertice a analizar
 * param lista de adyacencia
 * param vector de visitados
 ******************************************************************/
//hacemos uso del callstack para almacenar nuestro stack para la version recursiva
int esBipartita(int u, std::vector<int> adj[], std::vector<int>& visitado) {
  for (int v : adj[u]) {
    if (visitado.at(v) == -1) {
      visitado.at(v) = 1 - visitado.at(u); //si se invalidan dara 0
      if (!esBipartita(v, adj, visitado)) { //ver si los vecinos han sido visitados
	return -1;
      }
    } else if (visitado.at(v) == visitado.at(u)) {
      return -1;
    }
  }
  return 0;
}

