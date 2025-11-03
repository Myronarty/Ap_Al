#include "LUP.h"

int* sum(int* A, int* B, int n)
{
	int* C = new int[n*n];

	for (int i = 0; i < n*n; i++)
	{
		C[i] = A[i] + B[i];
	}

	return C;
}

int* diff(int* A, int* B, int n)
{
	int* C = new int[n * n];

	for (int i = 0; i < n * n; i++)
	{
		C[i] = A[i] - B[i];
	}

	return C;
}

int* mult(int* A, int* B, int n)
{
	int* C = new int[n * n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
			C[i * n + j] = 0;

            for (int k = 0; k < n; k++)
            {
				C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }

	return C;
}

double* mult(double* A, double* v, int n)
{
    double* y = new double[n];

    for (int i = 0; i < n; i++)
    {
        y[i] = 0;

        for (int j = 0; j < n; j++)
        {
            y[i] += A[i * n + j] * v[j];
        }
    }

    return y;
}

double* LUP(double*& A, vector<int>& P, int n)
{
    P.resize(n, 0);
    for (int i = 0; i < n; i++)
    {
        P[i] = i;
    }

    for (int k = 0; k < n; k++)
    {
        double max_val = 0.0;
        int k_ = k;

        for (int i = k; i < n; i++)
        {
            if (fabs(A[i * n + k]) > max_val)
            {
                max_val = fabs(A[i * n + k]);
                k_ = i;
            }
        }
        if (max_val < 1e-9)
        {
            cout << "Matrix virodgena" << endl;
            return nullptr;
        }

        if(k != k_)
        {
            double* temp = new double[n];
            for (int i = 0; i < n; i++)
            {
                temp[i] = A[k * n + i];
            }

            for (int i = 0; i < n; i++)
            {
                A[k * n + i] = A[k_ * n + i];
            }

            for (int i = 0; i < n; i++)
            {
                A[k_ * n + i] = temp[i];
            }
            delete[] temp;

            int temp_ = P[k];
            P[k] = P[k_];
            P[k_] = temp_;
        }

        for (int i = k + 1; i < n; i++)
        {
            A[i * n + k] /= A[k * n + k];
            for (int j = k + 1; j < n; j++)
            {
                A[i * n + j] = A[i * n + j] - A[i * n + k] * A[k * n + j];
            }
        }
    }
    return A;
}

double* rozviazok(double* A, double* b, int n)
{
    vector<int> P;
    A = LUP(A, P, n);

    double* y = new double[n];

    double* b_p = new double[n];

    for (int i = 0; i < n; i++)
    {
        b_p[i] = b[P[i]];
    }

    y[0] = b_p[0];

    for (int i = 1; i < n; i++)
    {
        double sum = 0.0;
        for (int t = 0; t < i; t++)
        {
            sum += A[i * n + t] * y[t];
        }
        sum = b_p[i] - sum;
        y[i] = sum;
    }

    double* x = new double[n];

    x[n - 1] = y[n-1] / A[n * n - 1];

    for (int i = n - 2; i > -1; i--)
    {
        double sum = 0.0;
        for (int t = i + 1; t < n; t++)
        {
            sum += A[i * n + t] * x[t];
        }
        x[i] = (y[i] - sum) / A[i * n + i];
    }

    return x;
}