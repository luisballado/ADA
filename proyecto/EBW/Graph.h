//SI _GRAPH_H no esta definido, se define
#ifndef _GRAPH_H

#define _GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <set>
#include <map>
#include <queue>

#define INF 0x3f3f3f3f //VALOR MUY GRANDE ¿?

class Graph {
  private:
    int numNodes;
    int numEdges;
    
    // Lista de adyacencia (vector de listas de pares (vertice, peso))
    //std::vector<LinkedList<std::pair<int, int>>> adjList;
    std::vector<std::vector<int>> adjList;
    std::vector<std::pair<int, int>> lista_aristas;
    std::map<std::pair<int, int>,int> map_lista_aristas; //(nodo1,nodo2),peso
    std::vector<int> bandwidth;
    void split(std::string line, std::vector<int> &res);
    
  public:
    Graph();
    ~Graph();
    void loadGraph(std::istream &input);
    void print_edges();
    void print_graph();
    void random_label();
    void sequential_label();
    void greedy_label();
    void evaluate();
};

#endif // _GRAPH_H
