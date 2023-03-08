#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
#include <map>
#include <fstream>
#include <queue>
#include <limits>

/********************************************************************
 Ejecutar el programa, se incluye un archivo make que ejecuta lo siguiente:
 - Eliminar el ejecutable anterior
 - Compilar usando g++

 Pasos para compilar:
 make
 ./problema_examen < bitacoraGrafos.txt

 RESULTADO:
 #######################################################
 boot master: 73.89.221.25  Grados: 18
 Camino mas largo: 
 IP - 244.223.133.50 -- 998
 Arista mas larga: 
 IP1 - 5.103.188.166 -##-  IP2 - 131.166.58.201 -- 2524
 #######################################################
 boot master: 185.109.34.183  Grados: 18
 Camino mas largo: 
 IP - 244.223.133.50 -- 1136
 Arista mas larga: 
 IP1 - 5.103.188.166 -##-  IP2 - 154.1.79.55 -- 6646

*******************************************************************/

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

  //TODO: Arreglar
  void BFS(int s){
    
    int V = adjList.size();
    
    //bool *visitado = new bool[V];
    std::vector<bool> visitado;
    //visitado.resize(V,false);
    
    //inicializar en no visitados
    for (int i=0;i<V;i++)
      visitado[i] = false;
    
    //https://www.programiz.com/cpp-programming/queue
    std::queue<int> q;
    visitado[s] = true;
    q.push(s);
    
    while(!q.empty()){
      int u = q.front();
      //std::cout << u << " ";
      q.pop();

      for (auto i = adjList[u].begin(); i != adjList[u].end(); ++i){
      	int v = i->first;
		
	if(!visitado[v]){
	  visitado[v] = true;
	  q.push(v);
	}
      }
    }
  }
  
  /*******************************************************************************************
   https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
   dijkstra O(E*logV)
   Regresa un vector con los pares IP, PESO con el vertice más lejano
  ********************************************************************************************/
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

    return respuesta;
    
  }

  /***************************************************************************************
  PRIM ALGO (adaptado de: https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/)
  Dado un grafo conexo, encuentra el MST
  regresando el PESO y el par de Vertices de la arista más grande
  Complejidad: MEJOR CASO O(E*logV)
  ****************************************************************************************/
  std::vector<std::pair<int, std::pair<int,int>>> primMST(int s){
    
    int maxx = 0; //aux para regresar respuesta
    int ip1,ip2;  //aux para regresar respuesta

    int INF = std::numeric_limits<int>::max(); //algo grande

    //Respuesta a regresar con los valores de PESO y el par de Vertices IP1-IP2
    std::vector<std::pair<int, std::pair<int,int>>> respuesta;
    
    //Cardinalidad del total de IP's
    int V = adjList.size();

    //Crear un vector para los pesos y se inicializa con valores infinitos
    std::vector<int> key(V, INF);

    //Almacenar todos los vertices incluidos en el MST 
    std::vector<bool> mstSet(V,false);

    //Almacenar el MST
    std::vector<int> parent(V,-1);

    //Crear una cola de prioridad para almacenar los vertices que son parte del MST
    //https://www.geeksforgeeks.org/implement-min-heap-using-stl/
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;

    //Ingresar el origen con peso 0
    pq.push(std::make_pair(0,s));
    key[s] = 0;

    //iterar hasta tener la cola vacia
    while(!pq.empty()){

      //El primer vertice es el minimo, quitarlo de la cola
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
    
  }
};

//CLASE IP
class IP {
public:
  
  //constructor
  IP(int index,std::string ip,int ip_rank): id_(index), ip_(ip), ip_rank_(ip_rank) {}
  
  //Obtener id
  int getId() const{ return id_;}

  //Obtener la ip
  std::string getIP() const{ return ip_;}

  //Obtener rango del vertice
  int getIPRank() const{ return ip_rank_;}
  
  //(SET) Poner información
  void setIPRank(int rank){ip_rank_ = rank;}
  
private:
  int id_;
  std::string ip_;
  int ip_rank_;
};


/*********************************************
 QUICKSORT ORDENAR DE MAYOR A MENOR
 Complejidad: PEOR CASO N^2 | MEJOR CASO nlog(n)
 Recibe un vector con los pares IPID, PESO
 Ordena el vector
*************************************************/
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

/*******************************************
 Obtener los datos que me importan
 Recibe la linea de texto a ser analizada
 regresa un vector<string>
 IP1
 IP2
 PESO
*******************************************/
std::vector<std::string> get_data(std::string str){

  std::vector<std::string> datos;

  //del dato de entrada poder obtener IP1, IP2, peso
  std::string host;
  std::string dato = "";
  
  //expresion regular para identificar ips
  std::regex ip_regex("((?:[0-9]{1,3}.){3}[0-9]{1,3}:[0-9]{2,4})");

  //expresion regular para identificar el peso
  std::regex peso_regex("[0-9]{2,3}"); 

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

  std::cout << "Cargando la información" << std::endl;
  
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
