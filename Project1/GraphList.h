#pragma once
#include <iostream>
#include <list>
#include "GraphMat.h"

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
	void AdV();
	void AdE(int v, int u);
	GraphMat Convert_(GraphList G);
	void ShowList();
	GraphList Convert(GraphMat G);
	int getIndex(int* w, int size, int v_n);
	int GetSize(GraphList G);
	int Get_Name(GraphList G, int i);
	list<int> GetNeighbors(int i);
};
