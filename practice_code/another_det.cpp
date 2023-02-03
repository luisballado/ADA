// Determinant C++
#include <iostream>
#include <ctime>
using namespace std;

void RandInitArray(int *, const int, int = 0, int = 20);
void Display(int *, const int);

int CalculateDeterminant(int *&, const int);
int Determinant(int *&, const int);

int main()
{
    
    srand((unsigned int)time(NULL));

    int N = 12;     // Size of matrix
    int * S = new int[N * N];
    int a(-10), b(10), det;

    RandInitArray(S, N, a, b);
    cout.precision(4);
    Display(S, N);

    det = CalculateDeterminant(S, N);

    cout << "\nDeterminant = " << det << "\n\n";

    cin.get();
    return 0;
}

void RandInitArray(int * arr, const int N, int a, int b)
{
    for (int i = 0; i < N * N; i++)
        arr[i] = rand() % (b - a + 1) + a;
}

void Display(int *arr, const int N)
{
    for (int i = 0; i < N * N; i++)
        cout << arr[i] << ((i + 1) % N ? "\t" : "\n");
}

int CalculateDeterminant(int *& S, const int N)
{
    int rez;

    if (N < 1)
        cout << "Size of matrix must be positive\n";
    else if (N == 1)
        rez = *S;
    else if (N == 2)
        rez = S[0] * S[3] - S[1] * S[2];
    else if (N == 3)
        rez = S[0] * S[4] * S[8] + S[1] * S[5] * S[6] + S[2] * S[3] * S[7] -
        S[2] * S[4] * S[6] - S[1] * S[3] * S[8] - S[0] * S[5] * S[7];
    else
        rez = Determinant(S, N);

    return rez;
}

int Determinant(int *& S, const int N)
{
    int sign(1), det(0), res, M(N - 1);
    int  * _S;

    for (int k = 0; k < N; k++)
    {
        _S = new int[M * M];

        int ind = 0;
        for (int i = N; i < N * N; i++)
        {
            if (i % N != k)
                _S[ind++] = S[i];
        }

        if (M == 3)
        {
            res = S[k] == 0 ? 0 : _S[0] * _S[4] * _S[8] + _S[1] * _S[5] * _S[6] + _S[2] * _S[3] * _S[7] -
            _S[2] * _S[4] * _S[6] - _S[1] * _S[3] * _S[8] - _S[0] * _S[5] * _S[7];

            delete[] _S;
        }
        else
            res = S[k] == 0 ? 0 : Determinant(_S, N - 1);

        det += S[k] * sign * res;
        sign *= -1;
    }

    delete[] S;

    return det;
}
