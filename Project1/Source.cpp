#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>

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
	int *a;
	int* b;
	int n;
public:
	Graph() = default;
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
	Graph(const Graph&) = default;
	Graph(Graph&&) = default;
	Graph& operator=(const Graph&) = default;
	void ShowM(Graph H)
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
		a[(v-1)*n + (u - 1)] = 1;
		a[(u - 1) * n + (v-1)] = 1;
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
};

int main()
{
	int a[1001]{ 0 };
	for(int opozdalovo = 0; opozdalovo < 1001; opozdalovo++)
	{
		random_device rd_;
		mt19937 gen_(rd_());
		//uniform_int_distribution<> dist_(1001, 1500);
		Set A = A.RandSet(150000);
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dist(0, 64*A.Sett());
		auto start = high_resolution_clock::now();
		A.Search(dist(gen));
		auto end = high_resolution_clock::now();
		//cout << endl;
		//auto duration = duration_cast<milliseconds>(end - start);

		auto duration = duration_cast<nanoseconds>(end - start);
		//cout << "Time: " << duration.count() << " ns" << endl;
		a[opozdalovo] = duration.count();
	}
	double rez = 0;
	for (int i = 0; i < 1001; i++)
	{
		rez += a[i];
	}
	rez /= 1001;
	cout << "Mean time " << rez << " ns" << endl;

	int b[1001]{ 0 };
	for (int opozdalovo = 0; opozdalovo < 1001; opozdalovo++)
	{
		random_device rd_;
		mt19937 gen_(rd_());
		//uniform_int_distribution<> dist_(1001, 1500);
		int d = 150000;
		Set A = Set().RandSet(d);
		Set B = Set().RandSet(d);
		random_device rd;
		mt19937 gen(rd());

		uniform_int_distribution<> dist(0, 64* d);
		auto start = high_resolution_clock::now();
		A.U(A, B);
		auto end = high_resolution_clock::now();

		auto duration = duration_cast<milliseconds>(end - start);
		b[opozdalovo] = duration.count();
	}
	double rez_ = 0;
	for (int i = 0; i < 1001; i++)
	{
		rez_ += b[i];
	}
	rez_ /= 1001;
	cout << "Mean time " << rez_ << " ms";


	/*Graph G(3);
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


	string a = "42";
	string b = "39";
	int x = 42;
	int n = 1 << 5;
	int t = pow(2, 4);
	int m = n | t;
	cout << n;*/
	return 0;
}