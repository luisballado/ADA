#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <cmath>
#include <utility>
#include <unordered_map>

#include<map>

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

  int grado(int x){
    return adjList[x].size();
  }

    
};

class IP {
public:

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

//YA NO SE USA
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
  
  ip_map mapa_ips; //crear un unordered map para guardar las ip
  
  Grafo grafo(n); //pasamos el num de vertices para hacer un resize

  std::map<int, IP> ipes; //crear un map para almacenar objetos
  
  //ITERAR SOLO LAS IPs
  for (int i = 0; i < n; i++) {

    std::string ip;  //ip
    std::cin >> ip;
    std::cout << ip << std::endl;

    //cargar ip a unordered map
    mapa_ips[ip] = i;
        
    //Crear un objeto de tipo IP y cargarlo al map
    ipes.emplace(i,IP(i,ip,0));
    
  }
  
  // ITERAR TODO EL TEXTO PARA ARMAR GRAFO
  for (int i = 0; i <= m; i++) {
    
    std::string texto_ip;  //ip
    std::vector<std::string> data; //vector para almacenar info importante

    std::getline(std::cin,texto_ip);
    
    data = get_data(texto_ip); // PASAR LA LINEA LEIDA Y OBTENER IP1, IP2, PESO

    std::string ip1,ip2;
    unsigned int ip_dec1,ip_dec2;
    
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

	peso = stoi(data.at(j));

	std::cout << "IP1: " << ip1 << std::endl;
	//std::cout << "num raro " << ip_dec1 << std::endl;
	std::cout << "IP2: " << ip2 << std::endl;
	//std::cout << "num raro " << ip_dec2 << std::endl;
	std::cout <<  "PESO: " << peso << std::endl;

	unsigned int u = mapa_ips[ip1];
	unsigned int v = mapa_ips[ip2];
	
	grafo.agregar(u,v,peso);
	
      }
    }
  }
      
  //grafo.imprimir();

  //ITERAR PARA GUARDAR EL GRADO DE SALIDA EN EL OBJETO
  for(int i = 0; i < n; i++){
    
    auto la_ip = ipes.find(i);
    
    int rank = grafo.grado(i);
    la_ip->second.setIPRank(rank);

    std::cout << "IP: " << la_ip->second.getIP() <<
      " GRADO: " << la_ip->second.getIPRank() << std::endl;
  }

  return 0;
  
}
