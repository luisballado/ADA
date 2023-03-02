#include <iostream>
#include <vector>
//#include <fstream>
#include <string>
#include <regex>

// ---------------------------------
// Binary Search Complexity
// ---------------------------------
// Best case complexity: O(1)
// Average case complexity: O(log n)
// Worst case complexity: O(log n)
// ---------------------------------
int busquedaBinaria(int array[], int x, int low, int high) {
  // Repeat until the pointers low and high meet each other
  while (low <= high) {
    int mid = low + (high - low) / 2;
    
    if (array[mid] == x)
      return mid;
    
    if (array[mid] < x)
      low = mid + 1;
    
    else
      high = mid - 1;
  }
  
  return -1;

}

// Obtener los datos que me importan
// regresa un vector<string>
std::vector<std::string> get_info(std::string str){

  std::vector<std::string> datos;

  //del dato de entrada poder obtener IP1, IP2, peso
  std::string host;
  std::string dato = "";
  std::regex ip_regex("((?:[0-9]{1,3}\.){3}[0-9]{1,3}:[0-9]{2,4})");
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
	size_t full_ip = dato.find_first_of(":");
	host = dato.substr(0,full_ip);
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

/**
void ip_dec(std::string ip){
  //hara un split de una direccion
  //imprimira su resultado
  std::string part1,part2,part3,part4;
  
  size_t full_ip = ip.find_first_of(".");
  part1 = ip.substr(0,full_ip);
  part2 = ip.substr(1,full_ip);
  part3 = ip.substr(2,full_ip);
  part4 = ip.substr(3,full_ip);
  std::cout << part1 << std::endl;
  std::cout << part2 << std::endl;
  std::cout << part3 << std::endl;
  std::cout << part4 << std::endl;
  
}
*/
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

  std::cout << "FOR1" << std::endl;
  
  // ITERAR TODO EL TEXTO
  for (int i = 0; i <= m; i++) {
    std::string _ip_;  //auxiliares que representan las ip
    std::vector<std::string> _data_;
    std::getline(std::cin,_ip_);

    // PASAR LA LINEA LEIDA Y OBTENER IP1, IP2, PESO
    _data_ = get_info(_ip_);
    
    for(int i=0; i < _data_.size();i++){
      if(i == 0)
	std::cout << "IP1: " << _data_.at(i) << std::endl;
      if(i == 1)
	std::cout << "IP2: " << _data_.at(i) << std::endl;
      if(i == 2)
	std::cout <<  "PESO: " << _data_.at(i) << std::endl;
      
    }
  }
  return 0;

}
