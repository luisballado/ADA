#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std::chrono;

/*
  Tiempo de complejidad O(n!)
*/

const int mat_size = 8;

// funcion para encontrar el terminante de una Matrix cuadrada
int determinante_recursion(int mat[mat_size][mat_size], int n, std::string call_txt){

  
  int resultado = 0;    // variable local para resultados
  int mat_cof[mat_size][mat_size];    // matriz de cofactores
  int cambio_signo = 1; // indicar cambio de signo
  
  //std::cout << "la llamada viende de: " << call_txt << std::endl;
  
  // Caso Base: si la matriz es lo suficiente chica para calcularla
  if (n == 1){
    //std::cout << "caso base 1 \n";
    return mat[0][0];
  }else if (n == 2){
    //std::cout << "caso base 2 \n";
    return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
  }
  
  // recorrer los elementos de la primera fila
  for (int f = 0; f < n; f++){
    
    // elementos de la matrix de cofactores
    int aux_i = 0;
    int aux_j = 0;
    
    for (int i = 1; i < n; i++){
      for (int j = 0; j < n; j++){
	if (j == f)
	  continue;
	mat_cof[aux_i][aux_j] = mat[i][j];
	aux_j++;
      }
      aux_i++;
      aux_j = 0;
    }

    // encontrar el determinando reduciendo el problema hasta llegar al caso base
    resultado += cambio_signo * mat[0][f] * determinante_recursion(mat_cof, n - 1, "funcion");
    
    // cambiar signo
    cambio_signo = -cambio_signo;
  }

  return resultado;
}

//funcion principal
int main(){
  
  /*
  int mat[mat_size][mat_size]= {
    { 1, 0, 2, -1 },
    { 3, 0, 0,  5 },
    { 2, 1, 4, -3 },
    { 1, 0, 5,  0 }
  };
  */
  
  int mat[mat_size][mat_size];

  //poblar la matriz
  for(int i(0); i != mat_size; ++i)
    for(int j(0); j != mat_size; ++j)
        mat[i][j] = rand() % 10;
  
  auto start = high_resolution_clock::now();
  
  //Imprimir resultado
  int resultado = determinante_recursion(mat,mat_size,"main");
  
  auto stop = high_resolution_clock::now();
  std::cout << "el resultado es: " << resultado << std::endl;

  auto duration = duration_cast<microseconds>(stop - start);
  
  std::cout << "Tiempo corrida: "
	    << duration.count() << " microseconds" << std::endl;
  
  return 0;
}
