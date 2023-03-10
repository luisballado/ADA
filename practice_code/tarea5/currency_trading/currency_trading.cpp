#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

const double INF = std::numeric_limits<double>::infinity();

//Dijkstra para encontrar el camino más corto
void dijkstra(const std::vector<std::vector<double> >& graph, int start, std::vector<double>& dist){

  int n = graph.size();
  std::vector<bool> visitado(n, false);

  dist[start] = 0.0;

  std::priority_queue<std::pair<double,int>,std::vector<std::pair<double,int> >, std::greater<std::pair<double, int> > > pq;
  pq.push(std::make_pair(dist[start], start));

  while(!pq.empty()){
    int u = pq.top().second;
    pq.pop();

    if(visitado[u]) continue;

    visitado[u] = true;

    for(int v = 0;v<n;++v){
      if(graph[u][v] == INF) continue;
      double alt = dist[u] + graph[u][v];
      if(alt < dist[v]){
	dist[v] = alt;
	pq.push(std::make_pair(dist[v],v));
      }
    }
    
  }

}

int main(){

  int n, m;

  std::cin >> n >> m;

  std::vector<std::vector<double> > graph(n, std::vector<double>(n,INF));

  for(int i=0;i<m;++i){
    int u,v;
    double rate;
    std::cin >> u >> v >> rate;
    graph[u][v] = -log(std::max(rate,1e-9));
  }

  int s, t;
  std::cin >> s >> t;

  std::vector<double> dist(n, INF);
  dijkstra(graph,s,dist);
  double result = exp(-dist[t]);

  std::cout << "El intercambio de " << s << " a " << t << " es " << result << std::endl;

  return 0;
  
}
