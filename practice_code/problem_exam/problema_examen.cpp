#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
#include <map>
#include <fstream>

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

    
};

//CLASE IP
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
  
  std::vector<std::pair<std::string,int>> lista;
  
  //ITERAR PARA GUARDAR EL GRADO DE SALIDA EN EL OBJETO
  for(int i = 0; i < n; i++){
    
    auto la_ip = ipes.find(i);
    
    int rank = grafo.grado(i);
    la_ip->second.setIPRank(rank);
    
    std::cout << "IP: " << la_ip->second.getIP() <<
      " GRADO: " << la_ip->second.getIPRank() << std::endl;
    
    lista.push_back(std::make_pair(la_ip->second.getIP(),la_ip->second.getIPRank()));
    
  }

  //std::cerr << "ANTES QUICK" << std::endl;
  quick_sort(lista,0,lista.size() - 1);
  //std::cerr << "DESPUES QUICK" << std::endl;

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

  //imprimir el primero de la lista
  std::cout << "boot master: " << lista.front().first
	    << "  Grados: " << lista.front().second << std::endl;
    
  return 0;
  
}
