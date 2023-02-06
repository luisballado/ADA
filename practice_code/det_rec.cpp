#include <iostream>
#include <cmath>

/*
Note that this implementation uses a recursive approach, which has a time complexity of O(n!). A more efficient approach is to use a matrix library with an in-place LU decomposition to calculate the determinant, which has a time complexity of O(n^3).
*/

const int N = 3;

// Function to find the determinant of a NxN matrix
double determinant(double mat[N][N], int n)
{
    double D = 0; // Initialize result

    // Base case: if the matrix contains a single element
    if (n == 1)
        return mat[0][0];

    // Temporary matrix to store cofactors
    double temp[N][N];

    int sign = 1; // To store sign multiplier

    // Iterate through each element of the first row
    for (int f = 0; f < n; f++)
    {
        // Get the cofactor matrix
        int temp_i = 0;
        int temp_j = 0;
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (j == f)
                    continue;
                temp[temp_i][temp_j] = mat[i][j];
                temp_j++;
            }
            temp_i++;
            temp_j = 0;
        }

        // Recursively find the determinant of the cofactor matrix
        D += sign * mat[0][f] * determinant(temp, n - 1);

        // Alternate the sign
        sign = -sign;
    }

    return D;
}

int main()
{
    double mat[N][N] = {{1, 1, 2},
                        {1, 4, 6},
                        {1, 3, 1}};
    
    std::cout << "Determinant of the matrix is: " << determinant(mat, N) << std::endl;

    return 0;
}
