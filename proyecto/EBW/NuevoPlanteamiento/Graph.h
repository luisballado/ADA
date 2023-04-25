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
#include <algorithm>
#include <random>

#define INF 0x3f3f3f3f //VALOR MUY GRANDE ¿?

class Graph {
  private:
    int numNodes;
    int numEdges;
    
    // Lista de adyacencia (vector de listas de pares (vertice, peso))
    //std::vector<LinkedList<std::pair<int, int>>> adjList;
    std::vector<std::vector<int>> adjList;
    std::map<std::pair<int, int>,int> map_aristas; //(nodo1,nodo2),index
    std::vector<int> peso_arista;
    std::vector<int> max_bandwidth;
    std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> edge_pairs;
    std::vector<std::pair<int,int>> edge_pairs_simple;
    int maxbandwidth;
    void split(std::string line, std::vector<int> &res);
    
  public:
    Graph();
    ~Graph();
    void loadGraph(std::istream &input);
    void print_edges();
    void print_graph();
    void print_list_pair_edges();
    void random_label();
    void sequential_label();
    void classic_evaluation();
    void incremental_evaluation();
    void evaluate();
    void make_swap(int i, int j);
};

#endif // _GRAPH_H
