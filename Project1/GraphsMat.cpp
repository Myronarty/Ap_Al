#include "GraphMat.h"

GraphMat::GraphMat()
{
	a = { 0 };
	b = { 0 };
	n = 0;
}

GraphMat::GraphMat(int s)
{
	n = s;
	a = new int[n * n];
	b = new int[n];
	for (int i = 0; i < n * n; i++)
	{
		a[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		b[i] = i + 1;
	}
}

GraphMat::GraphMat(const GraphMat&) = default;

GraphMat::GraphMat(GraphMat&&) = default;

GraphMat& GraphMat:: operator=(const GraphMat&) = default;

void GraphMat::ShowM() //візуалізація матриці
{
	if (n != 0)
	{
		cout << "    ";
		for (int i = 0; i < n; i++)
		{
			cout << "v_" << b[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < n * n; i++)
		{
			if ((i % n) == 0)
			{
				cout << "v_" << b[i / n] << "  ";
			}
			cout << a[i] << "   ";

			if (((i + 1) % n) == 0)
			{
				cout << endl;
			}
		}
		cout << endl;
	}
	else
	{
		cout << "GraphMat is empty" << endl;
		return;
	}
}

void GraphMat::AdV() //додати вершину
{
	int* temp = new int[(n + 1) * (n + 1)] {0};
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i * n + j] == 1)
			{
				temp[(n + 1) * i + j] = 1;
			}
		}
	}
	delete[] a;
	a = temp;
	int* temp_ = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		temp_[i] = b[i];
	}
	temp_[n] = n + 1;
	delete[] b;
	b = temp_;
	n++;
}

void GraphMat::AdE(int v, int u) //додати ребро
{
	v = getIndex(b, n, v);
	u = getIndex(b, n, u);
	if (v > n || u > n || v == u)
	{
		return;
	}
	a[v * n + u] = 1;
	a[u * n + v] = 1;
}

void GraphMat::DelV(int k) //видалити вершину за номером
{
	if (k > n || k < 1)
	{
		return;
	}
	k = getIndex(b, n, k);
	int* temp = new int[(n - 1) * (n - 1)] {0};
	for (int i = 0; i < k; i++)
	{
		int n_ = (n - 1) * i;
		int _n = i * n;
		for (int j = 0; j < k; j++)
		{
			temp[n_ + j] = a[_n + j];
		}
		for (int j = k; j < n - 1; j++)
		{
			temp[n_ + j] = a[_n + j + 1];
		}
	}
	for (int i = k; i < n - 1; i++)
	{
		int n_ = (n - 1) * i;
		int _n = (i + 1) * n;
		for (int j = 0; j < k; j++)
		{
			temp[n_ + j] = a[_n + j];
		}
		for (int j = k; j < n - 1; j++)
		{
			temp[n_ + j] = a[_n + j + 1];
		}
	}
	delete[] a;
	a = temp;
	int* temp_ = new int[n - 1];
	for (int i = 0; i < k; i++)
	{
		temp_[i] = b[i];
	}
	for (int i = k; i < n - 1; i++)
	{
		temp_[i] = b[i + 1];
	}
	delete[] b;
	b = temp_;
	n--;
}

void GraphMat::DelE(int v, int u) // видалити ребро
{
	if (v > n || u > n)
	{
		return;
	}
	v = getIndex(b, n, v);
	u = getIndex(b, n, u);
	a[v * n + u] = 0;
	a[u * n + v] = 0;
}

int GraphMat::getIndex(int* w, int size, int v_n) //назва вершини != її індексу
{
	for (int i = 0; i < size; i++)
	{
		if (w[i] == v_n)
		{
			return i;
		}
	}
	return -1;
}

int GraphMat::GetSize(GraphMat G)
{
	return G.n;
}

int GraphMat::Get_i_j(GraphMat G, int i, int j)
{
	return G.a[i * G.n + j];
}

int GraphMat::Get_Name(GraphMat G, int i)
{
	return G.b[i];
}

GraphMat GraphMat::RG(int t, double c) //випадковий граф Ердеша-Регьї (сподіваюсь)
{
	GraphMat G(t);
	double p = c * log(t) / t;
	random_device rd;
	mt19937 gen(rd());
	bernoulli_distribution d(p);

	for (int i = 0; i < t; i++)
	{
		for (int j = 0; j < t; j++)
		{
			if (d(gen) == 1)
			{
				G.AdE(i + 1, j + 1);
			}
		}
	}
	return G;
}
