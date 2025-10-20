#include "GraphList.h"

GraphList::GraphList()
{
	a = nullptr;
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

GraphList::GraphList(const GraphList&) = default;

GraphList::GraphList(GraphList&&) = default;

GraphList& GraphList:: operator=(const GraphList&) = default;

void GraphList::AdV()
{
	listochok.push_back(list<int>());
	int* temp_ = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		temp_[i] = a[i];
	}
	temp_[n] = n + 1;
	delete[] a;
	a = temp_;
	n++;
	cout << n << endl;
}

void GraphList::AdE(int v, int u)
{
	v = getIndex(v);
	u = getIndex(u);

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

int GraphList::getIndex(int v_n)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i] == v_n)
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

WGraphList::WGraphList(const WGraphList&) = default;

WGraphList::WGraphList(WGraphList&&) = default;

WGraphList& WGraphList:: operator=(const WGraphList&) = default;

WGraphList::WGraphList() : a(nullptr), n(0) {}

WGraphList::WGraphList(int s)
{
	n = s;
	a = new int[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = i + 1;
		listochok.push_back(list <pair<int, int>>());
	}
}

int WGraphList::getIndex(int v_n)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i] == v_n)
		{
			return i;
		}
	}
	return -1;
}

void WGraphList::AdV()
{
	listochok.push_back(list<pair<int, int>>());
	int* temp_ = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		temp_[i] = a[i];
	}
	if(n != 0)
	{
		temp_[n] = temp_[n - 1] + 1;
	}
	else
	{
		temp_[n] = 1;
	}
	delete[] a;
	a = temp_;
	n++;
	cout << n << endl;
}

void WGraphList::AdE(int v, int u, int w)
{
	int index_v = getIndex(v);
	int index_u = getIndex(u);

	if (index_v == -1 || index_u == -1) 
	{
		cout << -1 << endl;
		return;
	}

	listochok[index_v].push_back({ index_u, w });
	listochok[index_u].push_back({ index_v, w });
}

void WGraphList::ShowList()
{
	if (n == 0)
	{
		cout << "WGraphList is empty" << endl;
		return;
	}

	for (int i = 0; i < n; i++)
	{
		cout << "v_" << a[i] << ": ";

		for (pair<int, int> v : listochok[i])
		{
			cout << "(v_" << a[v.first] << ", " << v.second << ") ";
		}
		cout << endl;
	}
	cout << endl;
}

void WGraphList::DelV(int v) {
	int index_v = getIndex(v);

	if (index_v == -1) {
		cout << "V doesn't exist." << endl;
		return;
	}

	listochok.erase(listochok.begin() + index_v);

	int* temp_a = new int[n - 1];
	for (int i = 0, j = 0; i < n; i++) 
	{
		if (i != index_v)
		{
			temp_a[j++] = a[i];
		}
	}
	delete[] a;
	a = temp_a;

	n--;

	for (int i = 0; i < n; i++) 
	{
		for (auto it = listochok[i].begin(); it != listochok[i].end(); ) 
		{
			if (it->first == index_v) 
			{
				it = listochok[i].erase(it);
			}
			else 
			{
				if (it->first > index_v) 
				{
					it->first--;
				}
				++it;
			}
		}
	}

	cout << "v_" << v << " deleated." << endl;
}

void WGraphList::DelE(int v, int u) {
	int index_v = getIndex(v);
	int index_u = getIndex(u);

	if (index_v == -1 || index_u == -1) {
		cout << "v or u don't exist." << endl;
		return;
	}

	for (auto it = listochok[index_v].begin(); it != listochok[index_v].end(); ++it) {
		if (it->first == index_u) {
			listochok[index_v].erase(it);
			break;
		}
	}

	for (auto it = listochok[index_u].begin(); it != listochok[index_u].end(); ++it) 
	{
		if (it->first == index_v) 
		{
			listochok[index_u].erase(it);
			break;
		}
	}

	cout << "Edges (" << v << ", " << u << ") deleated." << endl;
}

WGraphList WGraphList::Convert(WGraphMat G)
{
	// Отримуємо розмір графа G, який ми конвертуємо
	int m = G.GetSize(G);

	// Створюємо новий граф H правильного розміру
	WGraphList H(m);

	// Копіюємо імена вершин
	for (int i = 0; i < m; i++)
	{
		H.a[i] = G.Get_Name(G, i);
	}

	// Копіюємо ребра, використовуючи правильний розмір 'm'
	for (int i = 0; i < m; i++) // ВИПРАВЛЕНО: n -> m
	{
		for (int j = 0; j < m; j++) // ВИПРАВЛЕНО: n -> m
		{
			int w = G.Get_i_j(G, i, j);

			if (w > 0)
			{
				// Додаємо ребро до списку суміжності графа H
				H.listochok[i].push_back({ j, w });
			}
		}
	}
	return H;
}
