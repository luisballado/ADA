#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
#include <map>
#include <fstream>
#include <queue>
#include <limits>

typedef std::pair<unsigned int,int> arista;
typedef std::unordered_map<std::string, unsigned int> ip_map;

//Clase GRAFO
class Grafo{

private:
  std::vector<std::vector<arista>> adjList;

public:
  Grafo(int n){
    adjList.resize(n);
  }
  
  void agregar(unsigned int u, unsigned int v, int w){
    adjList[u].push_back(std::make_pair(v,w));
  }

  void imprimir(){
    for(unsigned int i = 0;i<adjList.size();i++){
      std::cout << "Lista " << i << std::endl;
      for(unsigned int j=0;j<adjList[i].size();j++){
	std::cout << "(" << adjList[i][j].first << "," << adjList[i][j].second << ")";
      }
      std::cout << std::endl;
    }
  }

  int grado(int x){
    return adjList[x].size();
  }

  //Ver como agregar BFS
  /***
  void BFS(int s){
    int V = adjList.size();
    bool *visitado = new bool[V];

    //inicializar en no visitados
    for (int i=0;i<V;i++)
      visitado[i] = false;
    
    std::queue<int> q;
    visitado[s] = true;
    q.push(s);
    
    while(!q.empty()){
      int u = q.front();
      std::cout << u << " ";
      q.pop();
      
      for(auto v = adjList[u].begin(); v != adjList[u].end(); ++v){
	
	if(!visitado[v]){
	  visitado[v] = true;
	  q.push(v);
	}
      }
    }
  }
  **/
  
  //dijkstra
  //regresar en vector o lista
  //IP1 - IP2 - PESO
  //void dijkstra(int s){
  std::vector<std::pair<int,int>> dijkstra(int s){
    std::vector<std::pair<int,int>> respuesta;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;
    std::vector<int> dist(adjList.size(), std::numeric_limits<int>::max());

    int max = 0;
    int id_ip = 0;
    pq.push(std::make_pair(0, s));
    dist[s] = 0;

    while(!pq.empty()){
      int u = pq.top().second;
      pq.pop();

      for (auto it = adjList[u].begin(); it != adjList[u].end(); ++it){
	int v = it->first;
	int weight = it->second;
	
	if(dist[v] > dist[u] + weight){
	  dist[v] = dist[u] + weight;
	  pq.push(std::make_pair(dist[v],v));

	  //guardar el de mayor peso
	  if(max > dist[v]){
	    //nada
	  }else{
	    id_ip = v;
	    max = dist[v];
	    
	  }
	}
      }
      
    }
    
    respuesta.push_back(std::make_pair(id_ip,max));

    /**
    std::cout << "Distancia Vertice\tdesde el origen\n";
    
    for(int i = 0; i < adjList.size(); i++){
      std::cout << i << "\t" << dist[i] << "\n";
      
    }
    **/
    
    return respuesta;
  }

  const int INF = std::numeric_limits<int>::max(); //algo grande
  
  //PRIM ALGO
  //regresar arista mas larga
  //void primMST(int s){
  std::vector<std::pair<int, std::pair<int,int>>> primMST(int s){
    
    int maxx = 0;
    int ip1,ip2;
    
    std::vector<std::pair<int, std::pair<int,int>>> respuesta;
    
    int V = adjList.size();
    
    std::vector<int> key(V, INF);
    std::vector<bool> mstSet(V,false);
    std::vector<int> parent(V,-1);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;

    pq.push(std::make_pair(0,s));
    key[s] = 0;

    while(!pq.empty()){

      int u = pq.top().second;
      pq.pop();

      mstSet[u] = true;

      for(auto i = adjList[u].begin(); i != adjList[u].end(); ++i){

	int v = i->first;
	int w = i->second;
	
	if(!mstSet[v]&&w<key[v]){
	  key[v] = w;
	  parent[v] = u;
	  pq.push(std::make_pair(key[v],v));

	  //quedarse con el de la distancia mas grande
	  if(maxx < key[v]){
	    ip1 = parent[v];
	    ip2 = v;
	    maxx = key[v];
	  }
	}
      }
    }
    
    respuesta.push_back(std::make_pair(maxx,std::make_pair(ip1,ip2)));
    
    return respuesta;
    //obtener la arista mas larga
    /*
    for (int i=1; i<V;++i){
      std::cout << parent[i] << " - " << i << " : " << key[i] << std::endl;
    }
    */
  }
};

//CLASE IP
class IP {
public:
  
  //constructor
  IP(int index,std::string ip,int ip_rank): id_(index), ip_(ip), ip_rank_(ip_rank) {}
  
  //Obtener data
  int getId() const{ return id_;}
  std::string getIP() const{ return ip_;}
  int getIPRank() const{ return ip_rank_;}
  
  //Poner informacion
  void setIPRank(int rank){ip_rank_ = rank;}
  
private:
  int id_;
  std::string ip_;
  int ip_rank_;
};


//QUICKSORT
//ORDENAR DE MAYOR A MENOR
void quick_sort(std::vector<std::pair<std::string,int>>& arr, int izq, int der){

  int i = izq;
  int j = der;

  int pivote = arr[(izq + der) / 2].second;

  while(i<=j){
    while(arr[i].second > pivote)
      i++;
    while(pivote > arr[j].second)
      j--;
    if(i<=j){
      std::swap(arr[i],arr[j]);
      i++;
      j--;
    }
  }

  if(izq < j)
    quick_sort(arr, izq, j);
  if(i < der)
    quick_sort(arr, i, der);  

}

// Obtener los datos que me importan
// regresa un vector<string>
std::vector<std::string> get_data(std::string str){

  std::vector<std::string> datos;

  //del dato de entrada poder obtener IP1, IP2, peso
  std::string host;
  std::string dato = "";
  std::regex ip_regex("((?:[0-9]{1,3}.){3}[0-9]{1,3}:[0-9]{2,4})"); //expresion regular para identificar ips
  std::regex peso_regex("[0-9]{2,3}"); //expresion regular para identificar el peso
  std::string prev_x;

  //se le pasa la linea leida
  for (auto x : str){

    if (x == ' '){
      bool IP = regex_match(dato,ip_regex); //revisar si es de tipo IP
      bool PESO = regex_match(dato,peso_regex); //revisar si es un numero
      bool P_X = regex_match(prev_x,ip_regex); //revisar si el dato anterior es de tipo IP
      
      //QUITAMOS EL NUMERO DE PUERTO -- si el dato es una ip meterlo
      if(IP){
	size_t direccion_ip = dato.find_first_of(":");
	host = dato.substr(0,direccion_ip);
	datos.push_back(host);
      }

      //de acuerdo a la estructura si es un numero y anterior hay una IP entonces es el peso
      if(PESO && P_X) //si el dato es un numero meterlo
	datos.push_back(dato);
      
      prev_x = dato;   //aux para ver si el dato previo es una IP
      
      //std::cout << "El dato previo es:" << prev_x << std::endl;

      dato = "";       //resetearlo
    }else {
      dato = dato + x; //concatenar letra
    }
  }
  
  return datos;
  
}

int main() {
    
  int n;  //n
  int m;  //m
  
  std::cin >> n >> m; // guardar valores n - m
  
  ip_map mapa_ips; // crear un unordered map para guardar las ip
  
  Grafo grafo(n); //pasamos el num de vertices para hacer un resize a la lista de adjacencia

  std::map<int, IP> ipes; //crear un map para almacenar objetos
  
  //ITERAR SOLO LAS IPs respecto a n
  for (int i = 0; i < n; i++) {

    std::string ip;  //ip
    std::cin >> ip;
    //std::cout << ip << std::endl;

    //cargar ip a unordered map "ip" - "index"
    mapa_ips[ip] = i;
    
    //Crear un objeto de tipo IP y cargarlo al map
    ipes.emplace(i,IP(i,ip,0));
    
  }
  
  // ITERAR TODO EL TEXTO PARA ARMAR GRAFO respecto IP-PESOS
  for (int i = 0; i <= m; i++) {
    
    std::string texto_ip;  //ip
    std::vector<std::string> data; //vector para almacenar info importante que viene del texto

    std::getline(std::cin,texto_ip);
    
    data = get_data(texto_ip); // PASAR LA LINEA LEIDA Y OBTENER IP1, IP2, PESO

    std::string ip1,ip2;
    //unsigned int ip_dec1,ip_dec2;
    
    for(int j=0; j < data.size();j++){

      int peso;

      if(j == 0){
	ip1 = data.at(j);
	//ip_dec1 = ip_dec(data.at(j));
      }
      
      if(j == 1){
	ip2 = data.at(j);
	//ip_dec2 = ip_dec(data.at(j));
      }
      
      if(j == 2){

	peso = stoi(data.at(j)); //string a intero
	/**
	std::cout << "IP1: " << ip1 << std::endl;
	//std::cout << "num raro " << ip_dec1 << std::endl;
	std::cout << "IP2: " << ip2 << std::endl;
	//std::cout << "num raro " << ip_dec2 << std::endl;
	std::cout <<  "PESO: " << peso << std::endl;
	**/
	unsigned int u = mapa_ips[ip1]; //obtener el index de ip1
	unsigned int v = mapa_ips[ip2]; //obtener el index de ip2
	
	grafo.agregar(u,v,peso);
	
      }
    }
  }
      
  //grafo.imprimir();
  
  std::vector<std::pair<std::string,int>> lista; //una lista para aplicar quicksort
  
  //ITERAR PARA GUARDAR EL GRADO DE SALIDA EN EL OBJETO
  for(int i = 0; i < n; i++){
    
    auto la_ip = ipes.find(i);
    
    int rank = grafo.grado(i);
    la_ip->second.setIPRank(rank);

    /**
    std::cout << "IP: " << la_ip->second.getIP() <<
      " GRADO: " << la_ip->second.getIPRank() << std::endl;
    */
    lista.push_back(std::make_pair(la_ip->second.getIP(),la_ip->second.getIPRank()));
    
  }

  //std::cerr << "ANTES QUICK" << std::endl;
  quick_sort(lista,0,lista.size() - 1);
  //std::cerr << "DESPUES QUICK" << std::endl;

  //hacer archivo de salida
  std::ofstream output_file("gradosIPs.txt");
  
  if(output_file.is_open()){
    for(const auto& pair: lista){
      output_file << pair.first << "," << pair.second << std::endl;
    }
    output_file.close();
  }else{
    std::cerr << "Errores" << std::endl;
  }

  system("clear");
  
  //std::vector<int> boot_ids;
  //imprimir el primero de la lista, es el de mas grados
  for(int i = 0; i < 2; i++){

    std::cout << "#######################################################" << std::endl;
    //boot_ids.push_back(i);
    std::cout << "boot master: " << lista[i].first
	      << "  Grados: " << lista[i].second << std::endl;
    
    //pasar el id de los boot master
    //std::cout << "#################" << std::endl;
    std::cout << "Camino mas largo: " << std::endl;
    //std::cout << lista[i].first << std::endl;
    //std::cout << "#################" << std::endl;
    
    auto la_ip = ipes.find(grafo.dijkstra(i)[0].first);
    
    //regresa id y el peso -- buscar el maximo
    std::cout << "IP - " << la_ip->second.getIP()
	      << " -- "
	      << grafo.dijkstra(i)[0].second << std::endl;
    
    //std::cout << "#################" << std::endl;
    std::cout << "Arista mas larga: " << std::endl;
    //std::cout << lista[i].first << std::endl;
    //std::cout << "#################" << std::endl;
    
    //regresa id y el peso -- buscar el maximo
    //grafo.primMST(boot_ids[0]);
    
    auto la_ip1 = ipes.find(grafo.primMST(i)[0].first);
    auto la_ip2 = ipes.find(grafo.primMST(i)[0].second.first);
    
    std::cout << "IP1 - " << la_ip1->second.getIP()
	      << " -##- "
	      << " IP2 - " << la_ip2->second.getIP()
	      << " -- " << grafo.primMST(i)[0].second.second
	      << std::endl;
  }
  
  return 0;
  
}
