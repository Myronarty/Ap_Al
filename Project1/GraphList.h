#pragma once
#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include "GraphMat.h"
#include "W_Or_Graphs.h"

using namespace std;
using namespace std::chrono;

class GraphList
{
private:
	list <list <int>> listochok; //списки
	int* a; //назви вершин
	int n;
public:
	GraphList();
	GraphList(int s);
	GraphList(const GraphList&);
	GraphList(GraphList&&);
	GraphList& operator=(const GraphList&);
	void AdV();
	void AdE(int v, int u);
	GraphMat Convert_(GraphList G);
	void ShowList();
	GraphList Convert(GraphMat G);
	int getIndex(int v_n);
	int GetSize(GraphList G);
	int Get_Name(GraphList G, int i);
	list<int> GetNeighbors(int i);
};

class WGraphList : public GraphList //нащадок неорієнтованого графа - зважений
{
protected:
	vector <list <pair<int, int>>> listochok; //списки: вершина та вага шляху до неї
	int* a; //назви вершин
	int n;
public:
	using GraphList::GraphList;
	WGraphList();
	WGraphList(int s);
	WGraphList(const WGraphList&);
	WGraphList(WGraphList&&);
	WGraphList& operator=(const WGraphList&);
	int getIndex(int v_n);
	void AdV();
	void AdE(int v, int u, int w);
	void DelV(int v);
	void DelE(int v, int u);
	void ShowList();
	WGraphList Convert(WGraphMat G);

	pair<int, int>* Dijkstra(int s);
	int* BF(int s);
};
