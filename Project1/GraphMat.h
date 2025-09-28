#pragma once
#include <iostream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

class GraphMat
{
protected:
	int* a; //масив для матриці
	int n; //кількість вершин
public:
	int* b; //масив імен вершин
	GraphMat();
	GraphMat(int s);
	GraphMat(const GraphMat&);
	GraphMat(GraphMat&&);
	GraphMat& operator=(const GraphMat&);
	void ShowM(); //візуалізація матриці
	void AdV(); //додати вершину
	void AdE(int v, int u); //додати ребро
	void DelV(int k); //видалити вершину за номером
	void DelE(int v, int u); // видалити ребро
	int getIndex(int* w, int size, int v_n); //назва вершини != її індексу
	int GetSize(GraphMat G);

	int Get_i_j(GraphMat G, int i, int j);

	int Get_Name(GraphMat G, int i);

	GraphMat RG(int t, double c); //випадковий граф Ердеша-Регьї (сподіваюсь)
};
