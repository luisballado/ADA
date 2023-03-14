#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

const double INF = std::numeric_limits<double>::infinity();

//Dijkstra para encontrar el camino más corto
void dijkstra(const std::vector<std::vector<double> >& graph, int start, std::vector<double>& costo){

  int n = graph.size();
  std::vector<bool> visitado(n, false);

  costo[start] = 0.0;

  std::priority_queue<std::pair<double,int>,std::vector<std::pair<double,int> >, std::greater<std::pair<double, int> > > pq;

  pq.push(std::make_pair(costo[start], start));

  while(!pq.empty()){
    int u = pq.top().second;
    pq.pop();

    if(visitado[u]) continue;

    visitado[u] = true;

    for(int v = 0;v<n;++v){
      if(graph[u][v] == INF) continue;
      double alt = costo[u] + graph[u][v];
      if(alt < costo[v]){
	costo[v] = alt;
	pq.push(std::make_pair(costo[v],v));
      }
    }
    
  }

}

int main(){

  int n, m;

  //numero de monedas - numero de tasas de cambio
  std::cin >> n >> m;

  std::vector<std::vector<double> > graph(n, std::vector<double>(n,INF));

  //cargar los diferentes intercambios 
  for(int i=0;i<m;++i){
    int u,v;
    double rate;
    std::cin >> u >> v >> rate;
    graph[u][v] = -log(std::max(rate,1e-9));
  }

  //moneda origen --> moneda destino
  int s, t;
  std::cin >> s >> t;
  
  std::vector<double> costo(n, INF);
  dijkstra(graph,s,costo);
  double result = exp(-costo[t]);

  std::cout << "El intercambio de " << s << " a " << t << " es " << result << std::endl;

  return 0;
  
}
