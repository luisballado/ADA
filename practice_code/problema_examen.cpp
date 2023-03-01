#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int main() {

  
  
  /****
  int n;  //n
  int m;  //m
  
  std::cin >> n >> m;

  //se crea un array de vectores con la cardinalidad de vertices(nodos)
  std::vector<int> adj[n];
  
  for (int i = 0; i < n; i++) {
    char ip[13];  //auxiliares que representan las ip
    std::cin >> ip;
    std::cout << ip << std::endl;
  }

  for (int i = 0; i < m; i++) {
    char dates[600];  //auxiliares que representan las ip
    std::cin >> dates;
    std::cout << dates << std::endl;
  }
  **/

  // Create a text string, which is used to output the text file
  std::string myText;
  
  // Read from the text file
  std::ifstream MyReadFile("datos_examen.txt");
  
  // Use a while loop together with the getline() function to read the file line by line
  while (getline (MyReadFile, myText)) {
    // Output the text from the file
    std::cout << myText << std::endl;
  }
  
  // Close the file
  MyReadFile.close(); 
  
  return 0;
}
