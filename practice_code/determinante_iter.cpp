// C++ program to find Determinant of a matrix

#include <iostream>
#include <cmath>
#include <chrono>
#include <cstdlib>
using namespace std::chrono;

// rango de la matrix de entrada
const int mat_size = 5;

// funcion para obtener la determinante de una matriz
int determinante_iterativo(int mat[mat_size][mat_size], int n){
  int num1, num2, det = 1, index, total = 1; // Initialize result
  
  // temporary array for storing row
  int temp[n + 1];
  
  // loop for traversing the diagonal elements
  for (int i = 0; i < n; i++){
    index = i; // initialize the index
    
    // finding the index which has non zero value
    while (index < n && mat[index][i] == 0){
      index++;
    }
    // if there is non zero element
    if (index == n) {
      // the determinant of matrix as zero
      continue;
    }
    if (index != i){
      // loop for swapping the diagonal element row and
      // index row
      for (int j = 0; j < n; j++){
	std::swap(mat[index][j], mat[i][j]);
      }
      // determinant sign changes when we shift rows
      // go through determinant properties
      det = det * pow(-1, index - i);
    }
    
    // storing the values of diagonal row elements
    for (int j = 0; j < n; j++){
      temp[j] = mat[i][j];
    }
    // traversing every row below the diagonal element
    for (int j = i + 1; j < n; j++){
      num1 = temp[i]; // value of diagonal element
      num2 = mat[j][i]; // value of next row element
      
			// traversing every column of row
			// and multiplying to every row
      for (int k = 0; k < n; k++){
	// multiplying to make the diagonal
	// element and next row element equal
	mat[j][k]
	  = (num1 * mat[j][k]) - (num2 * temp[k]);
      }
      total = total * num1; // Det(kA)=kDet(A);
    }
  }
  
  // multiplying the diagonal elements to get determinant
  for (int i = 0; i < n; i++){
    det = det * mat[i][i];
  }
  return (det / total); // Det(kA)/k=Det(A);
}

// Driver code
int main(){


  int mat[mat_size][mat_size] = {
    { 1, 0, 2, -1, 1 },
    { 3, 0, 0, 5, 1 },
    { 3, 0, 0, 5, 1 },
    { 2, 1, 4, -3, 1 },
    { 1, 0, 5, 0, 1 }
  };
  

  //int mat[mat_size][mat_size];

  //poblar la matriz
  /**
  for(int i(0); i != mat_size; ++i)
    for(int j(0); j != mat_size; ++j)
        mat[i][j] = rand() % 10;;
  **/
  auto start = high_resolution_clock::now();
  
  //Imprimir resultado
  int resultado = determinante_iterativo(mat,mat_size);
  
  auto stop = high_resolution_clock::now();
  std::cout << "el resultado es: " << resultado << std::endl;

  auto duration = duration_cast<microseconds>(stop - start);
  
  std::cout << "Tiempo corrida: "
	    << duration.count() << " microseconds" << std::endl;
  
  return 0;
}
