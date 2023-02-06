/*
 * Encontrar la determinante de una matrix dada
 */

#include<iostream>
#include<math.h>

//el determinante inicial es cero
double determinante = 0;

double compute_det(int size_matrix, double mat[10][10]);

//calculo por cofactores
double compute_det(int size_matrix, double mat[10][10]){

  std::cout << "Llamada";
  
  double submat[10][10];

  if (size_matrix == 1)
    return ((mat[0][0]));
  else if (size_matrix == 2)
    return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
  else{
    for (int c = 0; c < size_matrix; c++){
      int subi = 0; //submatrix's i value
      for (int i = 1; i < size_matrix; i++){
	int subj = 0;
	for (int j = 0; j < size_matrix; j++){
	  if (j == c)
	    continue;
	  submat[subi][subj] = mat[i][j];
	  subj++;
	}
	subi++;
      }
      determinante = determinante + (pow(-1, c) * mat[0][c] * compute_det(size_matrix - 1, submat));
    }
  }
  return determinante;
}

int main(){
  
  int size_mat; 
  
  //imprimir en pantalla
  std::cout << "Ingresa el rango de la matriz (RANGO MAX 10):\n";

  //entrada de datos
  std::cin >> size_mat;

  //matriz max
  double mat[10][10];
  
  std::cout << "Ingresa los elementos de la matriz:\n";

  for (int i = 0; i < size_mat; i++){
    for (int j = 0; j < size_mat; j++){
      std::cin >> mat[j][i];
    }
  }

  //imprimir el resultado
  std::cout << "El determinante de la matriz dada es: " << compute_det(size_mat, mat);
  
  return 0;
}
