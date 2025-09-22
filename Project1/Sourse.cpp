#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <random>
#include <list>


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

class GraphMat
{
protected:
	int *a; //масив для матриці
	int *b; //масив імен вершин
	int n; //кількість вершин
public:
	GraphMat()
	{
		a = { 0 };
		b = { 0 };
		n = 0;
	}
	GraphMat(int s)
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
	GraphMat GraphMatList(GraphMat A) //перетворення у списки
	{
		// ???
	}
	GraphMat(const GraphMat&) = default;
	GraphMat(GraphMat&&) = default;
	GraphMat& operator=(const GraphMat&) = default;
	void ShowM(GraphMat H) //візуалізація матриці
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
			cout << "GraphMat is empty" << endl;
			return;
		}
	}
	void AdV() //додати вершину
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
	void AdE(int v, int u) //додати ребро
	{
		if (v > n || u > n || v == u)
		{
			return;
		}
		v = getIndex(b, n, v);
		u = getIndex(b, n, u);
		a[v*n + u] = 1;
		a[u * n +v] = 1;
	}
	void DelV(int k) //видалити вершину за номером
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
	void DelE(int v, int u) // видалити ребро
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



	int getIndex(int* w, int size, int v_n) //назва вершини != її індексу
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

	int GetSize(GraphMat G)
	{
		return G.n;
	}

	int Get_i_j(GraphMat G, int i, int j)
	{
		return G.a[i * G.n + j];
	}

	int Get_Name(GraphMat G, int i)
	{
		return G.b[i];
	}

	GraphMat RG(int t, double c) //випадковий граф Ердеша-Регьї (сподіваюсь)
	{
		GraphMat G(t);
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

class GraphList
{
private:
	list <list <int>> listochok; //списки
	int* a; //назви вершин
	int n;
public:
	GraphList()
	{
		a = { 0 };
		n = 0;
	}
	GraphList(int s)
	{
		n = s;
		a = new int[n];
		for (int i = 0; i < n; i++) 
		{
			a[i] = i + 1;
			listochok.push_back(list<int>());
		}
	}
	void AdV()
	{
		list <int> a;
		listochok.push_back(a);
		n++;
	}
	void AdE(int v, int u)
	{
		v = getIndex(a, n, v);
		u = getIndex(a, n, u);

		if (v == -1 || u == -1) return;

		auto it_v = listochok.begin();
		advance(it_v, v);
		it_v->push_back(u);

		auto it_u = listochok.begin();
		advance(it_u, u);
		it_u->push_back(v);
	}

	void ShowList()
	{
		if (n == 0)
		{
			cout << "GraphList is empty" << endl;
			return;
		}

		for (int i = 0; i < n; i++)
		{
			cout << "v_" << a[i] << " -> ";

			auto it = listochok.begin();
			advance(it, i);

			for (int v : *it)
			{
				cout << "v_" << v << " ";
			}
			cout << endl;
		}
	}

	GraphList Convert(GraphMat G)
	{
		int m = G.GetSize(G);
		GraphList H(m);
		for (int i = 0; i < H.n; i++)
		{
			H.a[i] = G.Get_Name(G, i);
		}
		for (int i = 0; i < H.n; i++)
		{
			for (int j = 0; j < H.n; j++)
			{
				if (G.Get_i_j(G, i, j) == 1)
				{
					auto it = H.listochok.begin();
					advance(it, i);
					it->push_back(H.a[j]);
				}
			}
		}
		return H;
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

	int GetSize(GraphList G)
	{
		return G.n;
	}

	int Get_Name(GraphList G, int i)
	{
		return G.a[i];
	}

	list<int> GetNeighbors(int i)
	{
		auto it = listochok.begin();
		advance(it, i);
		return *it;
	}

};

class OrGraphMat : public GraphMat //нащадок неорієнтованого графа - орієнтований
{
public:
	using GraphMat::GraphMat;
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

class WGraphMat : public GraphMat //нащадок неорієнтованого графа - зважений
{
public:
	using GraphMat::GraphMat;
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

class WOrGraphMat : public OrGraphMat //нащадок орієнтованого графа - зважений, просто щоб було
{
public:
	using OrGraphMat::OrGraphMat;
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
	GraphMat G(3);
	G.ShowM(G);
	G.AdE(2, 3);
	G.ShowM(G);
	G.AdE(2, 1);
	G.ShowM(G);
	G.AdV();
	G.AdV();
	G.AdV();
	G.AdE(3, 4);
	G.AdE(4, 1);
	G.AdE(2, 4);
	G.AdE(6, 5);
	G.AdE(2, 5);
	G.AdE(6, 1);
	G.ShowM(G);
	G.DelV(3);
	G.ShowM(G);
	G.DelV(5);
	G.ShowM(G);

	GraphList H = H.Convert(G);
	H.ShowList();

	return 0;
}