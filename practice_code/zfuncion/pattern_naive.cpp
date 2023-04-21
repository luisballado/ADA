#include<iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// naive version
// correr
// ./pattern_naive textos.txt mujer
std::vector<int> z_function(std::string s) {
    int n = s.length();
    std::vector<int> z(n, 0);
    for (int i = 1; i < n; i++) {
      for (int j = i; j < n; j++) {
	if(s[j] == s[j-i]){
	  z[i] = z[i] + i;
	}else{
	  break;
	}
      }
    }
    
    return z;
}

int main(int argc, char *argv[]){

  if (argc < 2) {
    std::cout << "Error: " << argv[0] << " falta el archivo" << std::endl;
    return -1;
  }

  std::ifstream fin(argv[1]);
  std::string pattern = argv[2];
  
  std::string archivo_texto;
  
  if (!fin) {
    std::cout << "Error: no se puede abrir el archivo " << argv[1] << std::endl;
    return -1;
  }else{
    std::ostringstream ss;
    ss << fin.rdbuf();
    archivo_texto = ss.str();
  }

  std::vector<int> z = z_function(archivo_texto);

  for (int i = 0; i < z.size(); i++) {
    std::cout << z[i] << " ";
  }
  
  std::cout << std::endl;
      
  return 0;
  
}
