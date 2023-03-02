#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <cmath>

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
      dato = dato + x; //concatenarlo
    }
  }
  
  return datos;
  
}

class IP {
public:
  std::string ip;
  unsigned int ipDec;
  int index;
};


//funcion para calcular los grados se salida
//recibe una lista de adyacencia
/**
   void calcular_grados(int n,std::vector<int> adj[]){
   
   for(int u = 1; u<=n; u++){
   grado_salida[u] = adj[u].size();
   }
   
   }
**/


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


int main() {
  
  //TODO: LEER ARCHIVO
  //CREAR Listas de adyacencia (IP, Grado de salida)
  
  //IMPRIMIR en que direccion se encuentra el boot master
  //Lee el archivo de entrada “bitacoraGrafos.txt” y almacena los datos en una lista de adyacencia organizada por la direccio ́n IP de origen. El archivo de entrada y una explicacio ́n de su formato pueden ser descargados desde el Google Drive del curso.
  //Determina el grado de salida de cada nodo del grafo (nu ́mero de IPs adyacentes a cada IP de origen) y almacena en un archivo llamado “gradosIPs.txt” una lista con los pares (IP, grado de salida) en orden decreciente del grado de salida.
  //¿En qu ́e direccio ́n IP presumiblemente se encuentra el boot master? Imprima en pantalla su respuesta.
  //Si el camino m ́as corto entre el boot master y cualquier otra IP del grafo representa el esfuerzo requerido para infectar dicha IP, ¿Cu ́al es la direccio ́n IP que presumiblemente requiere ma ́s esfuerzo para que el boot master la ataque? Imprima en pantalla su respuesta.
  
  std::cout << "INICIO" << std::endl;
  
  int n;  //n
  int m;  //m
  
  //guardar valores a n - m
  std::cin >> n >> m;
  
  //se crea un array de vectores con la cardinalidad de vertices(nodos)
  std::vector<int> adj[n];
  
  //SOLO LAS IP
  for (int i = 0; i < n; i++) {
    std::string ip;  //auxiliares que representan las ip
    std::cin >> ip;
    std::cout << ip << std::endl;
    
    //adj[i].push_back(ip);
    
  }
  
  // ITERAR TODO EL TEXTO
  for (int i = 0; i <= m; i++) {
    std::string _ip_;  //auxiliares que representan las ip
    std::vector<std::string> _data_;
    std::getline(std::cin,_ip_);
    
    // PASAR LA LINEA LEIDA Y OBTENER IP1, IP2, PESO
    _data_ = get_data(_ip_);
    
    for(int i=0; i < _data_.size();i++){

      if(i == 0){
	std::cout << "IP1: " << _data_.at(i) << std::endl;
	std::cout << "num raro " << ip_dec(_data_.at(i)) << std::endl;
      }

      if(i == 1){
	std::cout << "IP2: " << _data_.at(i) << std::endl;
	std::cout << "num raro " << ip_dec(_data_.at(i)) << std::endl;
      }
      
      if(i == 2)
	std::cout <<  "PESO: " << _data_.at(i) << std::endl;
      
    }
  }

  return 0;
  
}
