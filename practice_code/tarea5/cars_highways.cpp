//Problema 4.13 You are given a set of cities, along with the pattern of highways between them, in the form of an undirected graph G = (V, E). Each stretch of highway e ∈ E connects two of the cities, and you know its length in miles, le. You want to get from city s to city t. There’s one problem: your car can only hold enough gas to cover L miles. There are gas stations in each city, but not between cities. Therefore, you can only take a route if every one of its edges has length le ≤ L.
//(a) Given the limitation on your car’s fuel tank capacity, show how to determine in linear time whether there is a feasible route from s to t.
//(b) You are now planning to buy a new car, and you want to know the minimum fuel tank capacity that is needed to travel from s to t. Give an O((|V | + |E|) log |V |) algorithm to determine this.

#include <iostream>
#include <queue>
#include <vector>
#include <limits>

const int INF = std::numeric_limits<int>::max();
typedef std::pair<int, int> arista;

std::vector<std::vector<arista> > adj_lista;
std::vector<int> visitado; //ciudades visitadas

bool bfs(int s, int t, int L){

  std::queue<int> q;
  q.push(s);
  visitado[s] = true;

  while(!q.empty()){

    int u = q.front();
    q.pop();

    for(auto v_pair: adj_lista[u]){

      int v = v_pair.first;
      int weight = v_pair.second;

      if(!visitado[v] && weight <= L){
	visitado[v] = true;
	q.push(v);
	if(v==t) return true; //existe una ruta a t
      }
    }
    
  }
  return false; //no hay una ruta para t
}

//Busqueda binaria para encontrar el tanque minimo para viajar de s a t
int busqueda_binaria(int c_inicio, int c_destino, int max_distancia){
  int min = 0;
  int max = max_distancia;

  while (min < max){
    int mid = min + (max - min) / 2;
    visitado.assign(adj_lista.size(),false);
    if (bfs(c_inicio,c_destino,mid)){
      max = mid;
    }else{
      min = mid + 1;
    }
  }
  return max; // regresar la capacidad minima
}

int main(){

  int num_ciudades;
  int num_autopistas;
  int ciudad_inicio;
  int ciudad_destino;

  std::cin >> num_ciudades >> num_autopistas >> ciudad_inicio >> ciudad_destino;

  adj_lista.resize(num_ciudades);

  int max_distancia = 0; //max distancia entre dos ciudades

  for(int i=0;i<num_autopistas;i++){
    int u,v,peso;
    std::cin >> u >> v >> peso;
    adj_lista[u].push_back(std::make_pair(v,peso));
    adj_lista[v].push_back(std::make_pair(u,peso));
    max_distancia = std::max(max_distancia, peso);
  }

  //punto a
  visitado.assign(num_ciudades,false);

  if(bfs(ciudad_inicio,ciudad_destino,INF)){
    std::cout << "Existe una ruta de la ciudad " << ciudad_inicio
	      << " a la ciudad " << ciudad_destino << std::endl;
  }else{
    std::cout << "No existe una ruta de la ciudad " << ciudad_inicio
	      << " a la ciudad " << ciudad_destino << std::endl;
  }
  
  //punto b
  int tanque_gas = busqueda_binaria(ciudad_inicio, ciudad_destino, max_distancia);

  std::cout << "La capacidad minima del tanque para viajar de la ciudad " << ciudad_inicio
	    << " a la ciudad " << ciudad_destino << " es " << tanque_gas << std::endl;

  return 0;
  
}
