import argparse
import sys
import random
import numpy as np
import time

"""
Leer el parametro de entrada para crear la matriz

"""

parser = argparse.ArgumentParser()

parser.add_argument("-size", "--size", help="pasar el rango de la matriz")
args = parser.parse_args()

if args.size:
    matrix_size = args.size
else:
    parser.print_help(sys.stderr)
    sys.exit()

    
def recursivo(matrix):
    
    n = len(matrix)

    #caso base
    if n == 1:
        return matrix[0][0]
    if n == 2:
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]

    det = 0
    for i in range(n):
        sub_matrix = [row[:i] + row[i+1:] for row in matrix[1:]] 
        det += ((-1) ** i) * matrix[0][i] * recursivo(sub_matrix)

    return det
    
def iterativo(matrix):
    determinant = 1
    n = len(matrix)
    for i in range(n):
        # Encontrar el valor maximo en la columna
        maxRow = i
        for j in range(i + 1, n):
            if abs(matrix[j][i]) > abs(matrix[maxRow][i]):
                maxRow = j
        # intercambiar el maximo valor con el valor actual
        if maxRow != i:
            matrix[i], matrix[maxRow] = matrix[maxRow], matrix[i]
            determinant *= -1

        # Multiplicar el determinante por la diagonal
        determinant *= matrix[i][i]
        
        # terminar si los elementos de la diagonal son ceros
        if matrix[i][i] == 0:
            return 0

        # Eliminar los elementos abajo de la diagonal
        for j in range(i + 1, n):
            if matrix[i][i] == 0:
                scale = 0
            else:
                scale = matrix[j][i] / matrix[i][i]
                
            for k in range(i, n):
                matrix[j][k] -= scale * matrix[i][k]
                
    return determinant


print(matrix_size)

matriz = [] #1D vacio
aux = []    #1D vacio


#inicializar la columna
for j in range(0, int(matrix_size)):

    if j%2 == 0:
        random.seed(100)
        num = random.randint(1,10)
    else:
        random.seed(101)
        num = random.randint(25, 50)
    
    aux.append(num)

# Agregar la columna a cada fila
for i in range(0, int(matrix_size)):
    matriz.append(aux)

n_array = np.array(matriz)
  
# Mostrar la matriz
print("Numpy Matrix is:")
print(n_array)
  
# calcular la determinante de la matrix por numpy
det = np.linalg.det(n_array)
  
print("\n Determinante con numpy:")
print(int(det))


print("\n Determinante con iterativo:")
start_time = time.time()
print(iterativo(matriz))
print("--- %s seconds ---" % (time.time() - start_time))

print("\n Determinante con recursivo:")
start_time = time.time()
print(recursivo(matriz))
print("--- %s seconds ---" % (time.time() - start_time))



