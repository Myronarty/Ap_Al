#include "GraphList.h"

GraphList::GraphList()
{
	a = { 0 };
	n = 0;
}

GraphList::GraphList(int s)
{
	n = s;
	a = new int[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = i + 1;
		listochok.push_back(list<int>());
	}
}

void GraphList::AdV()
{
	list <int> a;
	listochok.push_back(a);
	n++;
}

void GraphList::AdE(int v, int u)
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

GraphMat GraphList::Convert_(GraphList G)
{
	int m = G.GetSize(G);
	GraphMat H(m);
	for (int i = 0; i < m; i++)
	{
		H.b[i] = G.Get_Name(G, i);
	}
	for (int i = 0; i < m; i++)
	{
		int v = G.Get_Name(G, i);
		list<int> neighbors = G.GetNeighbors(i);

		for (int u : neighbors)
		{
			H.AdE(v, u);
		}
	}
	return H;
}

void GraphList::ShowList()
{
	if (n == 0)
	{
		cout << "GraphList is empty" << endl;
		return;
	}

	for (int i = 0; i < n; i++)
	{
		cout << "v_" << a[i] << ": ";

		auto it = listochok.begin();
		advance(it, i);

		for (int v : *it)
		{
			cout << "v_" << v << " ";
		}
		cout << endl;
	}
	cout << endl;
}

GraphList GraphList::Convert(GraphMat G)
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

int GraphList::getIndex(int* w, int size, int v_n)
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

int GraphList::GetSize(GraphList G)
{
	return G.n;
}

int GraphList::Get_Name(GraphList G, int i)
{
	return G.a[i];
}

list<int> GraphList::GetNeighbors(int i)
{
	auto it = listochok.begin();
	advance(it, i);
	return *it;
}
