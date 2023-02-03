/*
 * Encontrar la determinante de una matrix dada
 */

#include<iostream>
#include<math.h>

//using namespace std;

double d = 0;

double det(int n, double mat[10][10]);

double det(int n, double mat[10][10]){
  
  double submat[10][10];

  if (n == 1)
    return ((mat[0][0]));
  
  else if (n == 2)
    return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
  
  else{

    for (int c = 0; c < n; c++){
      
      int subi = 0; //submatrix's i value

      for (int i = 1; i < n; i++){
	int subj = 0;
	for (int j = 0; j < n; j++){
	  if (j == c)
	    continue;
	  submat[subi][subj] = mat[i][j];
	  subj++;
	}
	subi++;
      }
      d = d + (pow(-1, c) * mat[0][c] * det(n - 1, submat));
    }
  }
  return d;
}

int main(int argc, char **argv){

  std::cout << "Ingresa el rango de la matriz:\n";
  int n;
  std::cin >> n;
  double mat[10][10];
  std::cout << "Ingresa los elementos de la matriz:\n";

  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      std::cin >> mat[j][i];
    }
  }

  std::cout << "El determinante de la matriz dada es: " << det(n, mat);
  
  return 0;
}
