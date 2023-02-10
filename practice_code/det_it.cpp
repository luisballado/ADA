#include <iostream>
#include <cmath>

#include <chrono>
#include <cstdlib>
using namespace std::chrono;

//No funciona para el experimento

const int N = 8;

double determinant(double a[N][N], int n) {
    double det = 1;
    for (int i = 0; i < n; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++)
            if (fabs(a[j][i]) > fabs(a[k][i]))
                k = j;
        if (fabs(a[k][i]) < 1e-9)
            return 0.0;
	std::swap(a[i], a[k]);
        if (i != k)
            det = -det;
        det *= a[i][i];
        for (int j = i + 1; j < n; j++) {
            double t = a[j][i] / a[i][i];
            for (int l = i + 1; l < n; l++)
                a[j][l] -= t * a[i][l];
        }
    }
    return det;
}

int main() {

  
  double a[N][N] = {
    {1.0, 1.0, 2.0, 1.0,1.0, 1.0, 2.0, 1.0},
    {1.0, 1.0, 2.0, 1.0,1.0, 1.0, 2.0, 1.0},
    {1.0, 1.0, 2.0, 1.0,1.0, 1.0, 2.0, 1.0},
    {1.0, 1.0, 2.0, 1.0,1.0, 1.0, 2.0, 1.0},
    {1.0, 1.0, 2.0, 1.0,1.0, 1.0, 2.0, 1.0},
    {3.0, 1.0, 1.0, 1.0,1.0, 1.0, 2.0, 1.0},
    {3.0, 1.0, 1.0, 1.0,1.0, 1.0, 2.0, 1.0},
    {1.0, 2.0, 1.0, 4.0,1.0, 1.0, 2.0, 1.0}
  };
  

  int n = N;
  std::cout << "determinante de la matrix: " << determinant(a, n) << std::endl;
  return 0;
}
