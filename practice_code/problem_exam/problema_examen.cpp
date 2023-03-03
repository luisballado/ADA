#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <cmath>
#include <utility>
#include <unordered_map>

typedef std::pair<unsigned int,int> arista;
typedef std::unordered_map<std::string, unsigned int> ip_map;

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
};

class IP {
public:
  std::string ip;
  unsigned int ipDec;
  int index;
};

// Obtener los datos que me importan
// regresa un vector<string>
std::vector<std::string> get_data(std::string str){

  std::vector<std::string> datos;

  //del dato de entrada poder obtener IP1, IP2, peso
  std::string host;
  std::string dato = "";
  std::regex ip_regex("((?:[0-9]{1,3}.){3}[0-9]{1,3}:[0-9]{2,4})");
  std::regex peso_regex("[0-9]{2,3}");
  std::string prev_x;

  for (auto x : str){
    
    if (x == ' '){
      // si el dato es una ip meterlo
      // si el dato es un numero meterlo
      bool IP = regex_match(dato,ip_regex); //revisar si es de tipo IP
      bool PESO = regex_match(dato,peso_regex); //revisar si es un numero
      bool P_X = regex_match(prev_x,ip_regex); //revisar si el dato anterior es de tipo IP
      
      //QUITAMOS EL NUMERO DE PUERTO
      if(IP){
	size_t found = dato.find_first_of(":");
	host = dato.substr(0,found);
	datos.push_back(host);
      }
      //de acuerdo a la estructura si es un numero y anterior hay una IP entonces es el peso
      if(PESO && P_X)
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

//funcion para calcular los grados se salida
//recibe una lista de adyacencia
//TODO crear file con nodo - grado
void calcular_grados(int n, std::vector<int> adj[]){
  for(int i = 1; i <= n; i++){
    std::cout << adj[i].size();
    
  }
  
}


unsigned int ip_dec(std::string ip){
  //hara un split de una direccion
  //imprimira su resultado
  
  std::string delimiter = ".";

  size_t pos = 0;
  std::string token;

  int num_ip_dec = 0;
  unsigned int i = 0;

  while ((pos = ip.find(delimiter)) != std::string::npos) {
    token = ip.substr(0, pos);
    //std::cout << token << std::endl;
    ip.erase(0, pos + delimiter.length());

    if(i==0){
      num_ip_dec = (num_ip_dec + (stoi(token) * pow(256,3)));
    }

    if(i==1){
      num_ip_dec = (num_ip_dec + (stoi(token) * pow(256,2)));
    }

    if(i==2){
      num_ip_dec = (num_ip_dec + (stoi(token) * 256));
    }
        
    i = i + 1;
  }

  num_ip_dec = (num_ip_dec + stoi(token));
  
  return num_ip_dec;
}

// To add an edge
/**
void addEdge(std::vector<std::pair<int, int> > adj[], int u,
                                     int v, int wt)
{
  adj[u].push_back(std::make_pair(v, wt));
}
 
// Print adjacency list representation of graph
void printGraph(std::vector<std::pair<int,int> > adj[], int V)
{
    int v, w;
    for (int u = 0; u < V; u++)
    {
      std::cout << "Node " << u << " makes an edge with \n";
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++)
        {
            v = it->first;
            w = it->second;
	    std::cout << "\tNode " << v << " with edge weight ="
                 << w << "\n";
        }
	std::cout << "\n";
    }
}
**/
/**
void agregar_nodo(std::vector<int> adj[], int origen, int destino){
  adj[origen].push_back(destino);
}

// Print the graph
void imprimirGrafo(std::vector<unsigned int> adj[], int V) {
  for (int d = 0; d < V; ++d) {
    std::cout << "\n Vertex "
       << d << ":";
    for (auto x : adj[d])
      std::cout << "-> " << x;
    printf("\n");
  }
}
**/
//CREAR Listas de adyacencia (IP, Grado de salida)
  
  //IMPRIMIR en que direccion se encuentra el boot master
  //Lee el archivo de entrada “bitacoraGrafos.txt” y almacena los datos en una lista de adyacencia organizada por la direccio ́n IP de origen. El archivo de entrada y una explicacio ́n de su formato pueden ser descargados desde el Google Drive del curso.
  //Determina el grado de salida de cada nodo del grafo (nu ́mero de IPs adyacentes a cada IP de origen) y almacena en un archivo llamado “gradosIPs.txt” una lista con los pares (IP, grado de salida) en orden decreciente del grado de salida.
  //¿En qu ́e direccio ́n IP presumiblemente se encuentra el boot master? Imprima en pantalla su respuesta.
  //Si el camino m ́as corto entre el boot master y cualquier otra IP del grafo representa el esfuerzo requerido para infectar dicha IP, ¿Cu ́al es la direccio ́n IP que presumiblemente requiere ma ́s esfuerzo para que el boot master la ataque? Imprima en pantalla su respuesta.

int main() {
    
  int n;  //n
  int m;  //m
  
  //guardar valores a n - m
  std::cin >> n >> m;
  
  //se crea un array de vectores con la cardinalidad de vertices(nodos)
  //std::vector<unsigned int> adj[n];
  //std::vector<std::pair<int,int> > adj[n];

  ip_map ipToVertex;
  Grafo grafo(n);
  
  //SOLO LAS IP
  for (int i = 0; i < n; i++) {
    IP myIP; //Crear un objeto de tipo IP
    std::string ip;  //auxiliares que representan las ip
    std::cin >> ip;
    std::cout << ip << std::endl;

    ipToVertex[ip] = i;

    //crear muchos objetos
    IP _ip_;
    _ip_.ip = ip;
    _ip_.ipDec = ip_dec(ip);
    _ip_.index = i;
    
  }
  
  // ITERAR TODO EL TEXTO
  for (int i = 0; i <= m; i++) {
    
    std::string _ip_;  //auxiliares que representan las ip
    std::vector<std::string> _data_;
    std::getline(std::cin,_ip_);
    
    _data_ = get_data(_ip_); // PASAR LA LINEA LEIDA Y OBTENER IP1, IP2, PESO

    std::string ip1,ip2;
    unsigned int ip_dec1,ip_dec2;
    
    for(int j=0; j < _data_.size();j++){

      int peso;

      if(j == 0){
	ip1 = _data_.at(j);
	ip_dec1 = ip_dec(_data_.at(j));
      }
      
      if(j == 1){
	ip2 = _data_.at(j);
	ip_dec2 = ip_dec(_data_.at(j));
      }
      
      if(j == 2){

	peso = stoi(_data_.at(j));

	std::cout << "IP1: " << ip1 << std::endl;
	std::cout << "num raro " << ip_dec1 << std::endl;
	std::cout << "IP2: " << ip2 << std::endl;
	std::cout << "num raro " << ip_dec2 << std::endl;
	std::cout <<  "PESO: " << peso << std::endl;

	unsigned int u = ipToVertex[ip1];
	unsigned int v = ipToVertex[ip2];
	
	grafo.agregar(u,v,peso);
	
      }
    }
  }
      
  grafo.imprimir();
    
  return 0;
  
}
