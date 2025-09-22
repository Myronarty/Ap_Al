#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

class Set
{
protected:
	int t;
	int *A_;
public:
	Set()
	{
		t = 1001;
		A_ = new int[t] {0};
	}
	Set(int n)
	{
		t = n;
		A_ = new int[t] {0};
	}
	int Sett()
	{
		return t;
	}
	Set RandSet(int y)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dist_(0, 1);
		Set A(y);
		A.t = y;
		for (int i = 0; i < y; i++) 
		{
			A.A_[i] = dist_(gen);
		}
		return A;
	}
	Set SetU(Set A)
	{
		Set U;
		U.t = A.t;
		U.A_ = new int[t] {1};
		return U;
	}
	Set(const Set&) = default;
	Set(Set&&) = default;
	Set& operator=(const Set&) = default;
	int& operator[](int i)
	{
		return A_[i];
	};
	Set& operator=(Set&&) = default;
	virtual ~Set() = default;
	int* SetA(Set S)
	{
		return A_;
	}
	int Insert(int N)
	{
		int j = N % 64;
		int i = (N - j) / 64;
		int t = 1 << j;
		A_[i] = A_[i] | t;
		return N;
	}
	int Delete(int N)
	{
		int j = N % 64;
		int i = (N - j) / 64;
		int t = 1 << j;
		A_[i] = A_[i] & ~t;
		return N;
	}
	bool Search(int N)
	{
		int j = N % 64;
		int i = (N - j) / 64;
		int k = 1 << j;
		bool s = A_[i] & k;
		//cout << s;
		return s;
	}
	int Clear()
	{
		for (int i = 0; i < t; i++)
		{
			A_[i] = 0;
		}
		return 0;
	}
	Set U(Set A, Set B)
	{
		Set C = Set(A.t);
		for (int i = 0; i < t; i++)
		{
			C[i] = A[i] | B[i];
		}
		return C;
	}
	Set not_U(Set A, Set B)
	{
		Set C = Set(A.t);
		for (int i = 0; i < t; i++)
		{
			C[i] = A[i] & B[i];
		}
		return C;
	}
	Set Diff(Set A, Set B)
	{
		Set C = Set(A.t);
		for (int i = 0; i < t; i++)
		{
			C[i] = A[i] & ~(B[i]);
		}
		return C;
	}
	Set SymDiff(Set A, Set B)
	{
		Set C = Set(A.t);
		for (int i = 0; i < t; i++)
		{
			C[i] = (A[i] | B[i]) & (~(A[i]) | ~(B[i]));			
		}
		return C;
	}
	bool IsSubSet(Set A, Set B)
	{
		for (int i = 0; i < t; i++)
		{
			if (A[i] != (A[i] & B[i]))
			{
				return 0;
			}
		}
		return 1;
	}
};

class Graph
{
protected:
	int *a; //масив для матриці
	int* b; //масив імен вершині
	int n; //кількість вершин
public:
	Graph()
	{
		a = { 0 };
		b = { 0 };
		n = 0;
	}
	Graph(int s)
	{
		n = s;
		a = new int[n*n];
		b = new int[n];
		for (int i = 0; i < n * n; i++)
		{
			a[i] = 0;
		}
		for (int i = 0; i < n; i++)
		{
			b[i] = i+1;
		}
	}
	Graph GraphS(Graph A)
	{
		// ???
	}
	Graph(const Graph&) = default;
	Graph(Graph&&) = default;
	Graph& operator=(const Graph&) = default;
	void ShowM(Graph H)
	{
		if (H.n != 0) 
		{
			cout << "    ";
			for (int i = 0; i < H.n; i++)
			{
				cout << "v_" << b[i] << " ";
			}
			cout << endl;
			for (int i = 0; i < H.n * H.n; i++)
			{
				if ((i % n) == 0)
				{
					cout << "v_" << b[i / n] << "  ";
				}
				cout << H.a[i] << "   ";

				if (((i + 1) % n) == 0)
				{
					cout << endl;
				}
			}
			cout << endl;
		}
		else
		{
			cout << "Graph is empty" << endl;
			return;
		}
	}
	void AdV()
	{
		int* temp = new int[(n + 1) * (n + 1)] {0};
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (a[i * n + j] == 1)
				{
					temp[(n+1)*i+j] = 1;
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
	void AdE(int v, int u)
	{
		if (v > n || u > n)
		{
			return;
		}
		v = getIndex(b, n, v);
		u = getIndex(b, n, u);
		a[v*n + u] = 1;
		a[u * n +v] = 1;
	}
	void DelV(int k)
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
			for (int j = k; j < n-1; j++)
			{
				temp[n_ + j] = a[_n + j+1];
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
	void DelE(int v, int u)
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


	int getIndex(int* w, int size, int v_n)
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

	Graph RG(int t, double c)
	{
		Graph G(t);
		double p = c * log(t)/t;
		random_device rd;
		mt19937 gen(rd());
		bernoulli_distribution d(p);

		for (int i = 0; i < t; i++) 
		{
			for (int j = 0; j < t; j++)
			{
				if (d(gen) == 1)
				{
					G.AdE(i+1, j+1);
				}
			}
		}
		return G;
	}
};

class OrGraph : public Graph //нащадок неорієнтованого графа - орієнтований
{
public:
	using Graph::Graph;
	void AdE(int v, int u)
	{
		if (v > n || u > n)
		{
			return;
		}
		v = getIndex(b, n, v);
		u = getIndex(b, n, u);
		a[v * n + u] = 1;
	}
	void DelE(int v, int u)
	{
		if (v > n || u > n)
		{
			return;
		}
		v = getIndex(b, n, v);
		u = getIndex(b, n, u);
		a[v * n + u] = 0;
	}
};

class WGraph : public Graph //нащадок неорієнтованого графа - зважений
{
public:
	using Graph::Graph;
	void AdE(int v, int u, int w)
	{
		if (v > n || u > n)
		{
			return;
		}
		v = getIndex(b, n, v);
		u = getIndex(b, n, u);
		a[v * n + u] = w;
		a[u * n + v] = w;
	}
};

class WOrGraph : public OrGraph //нащадок орієнтованого графа - зважений, просто щоб було
{
public:
	using OrGraph::OrGraph;
	void AdE(int v, int u, int w)
	{
		if (v > n || u > n)
		{
			return;
		}
		v = getIndex(b, n, v);
		u = getIndex(b, n, u);
		a[v * n + u] = w;
	}
};

int main()
{
	Graph G = G.RG(9, 1);
	G.ShowM(G);

	return 0;
}