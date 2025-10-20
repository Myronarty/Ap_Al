#include "GraphList.h"
#include <limits> // for std::numeric_limits<int>::max()

bool comparees(const Edge& a, const Edge& b) 
{
	return a.weight < b.weight;
}

pair<int, int>* WGraphList::Dijkstra(int s)
{
	pair<int, int>* A = new pair<int, int>[n];
	for (int i = 0; i < n; i++) 
	{
		A[i].first = std::numeric_limits<int>::max();
		A[i].second = -1;
	}
	A[getIndex(s)].first = 0;
	vector<bool> visited(n, false);
	int v = s;
	for (int verhunki=0; verhunki < n; verhunki++)
	{
		int u = -1;
		int min_dist = std::numeric_limits<int>::max();
		for (int i = 0; i < n; ++i) 
		{
			if (!visited[i] && A[i].first < min_dist) 
			{
				min_dist = A[i].first;
				u = i;
			}
		}

		if (u == -1) break;

		visited[u] = true;

		for (pair<int, int> v : listochok[u])
		{
			if (!visited[v.first] && A[u].first != std::numeric_limits<int>::max() && A[v.first].first > A[u].first + v.second)
			{
				A[v.first].first = A[u].first + v.second;
			}
			A[v.first].second = a[v.first];
		}
	}

	return A;
}

int* WGraphList::BF(int s)
{
	int* A = new int[n];
	for (int i = 0; i < n; i++)
	{
		A[i] = std::numeric_limits<int>::max();
	}
	A[getIndex(s)]= 0;
	for (int i = 1; i < n; i++)
	{
		for (int verhunki = 0; verhunki < n; verhunki++)
		{
			for (pair<int, int> v : listochok[verhunki])
			{
				if (A[verhunki] == std::numeric_limits<int>::max())
				{
					continue;
				}
				if (A[v.first] > A[verhunki] + v.second)
				{
					A[v.first] = A[verhunki] + v.second;
				}
			}
		}
	}
	return A;
}

vector<Edge> WGraphList::Sort()
{
	vector<Edge> E;
	for (int u = 0; u < this->n; ++u)
	{
		for (const auto& e_pair : this->listochok[u])
		{
			int v = e_pair.first;
			int weight = e_pair.second;

			if (u < v)
			{
				E.push_back({ u, v, weight });
			}
		}
	}
	sort(E.begin(), E.end(), comparees);
	return E;
}

vector<Edge> WGraphList::Kruskal(const vector<Edge>& E)
{
	UnionFind UF(this->n);
	vector<Edge> T;


	for (const auto& e : E)
	{
		if (UF.Find(e.u) != UF.Find(e.v)) 
		{
			T.push_back(e);
			UF.Union(e.u, e.v);
		}

		if (T.size() == this->n - 1)
		{
			break;
		}
	}

	return T;
}