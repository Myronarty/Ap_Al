#pragma once
#include <iostream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

class GraphMat
{
protected:
	int* a; //����� ��� �������
	int n; //������� ������
public:
	int* b; //����� ���� ������
	GraphMat();
	GraphMat(int s);
	GraphMat(const GraphMat&);
	GraphMat(GraphMat&&);
	GraphMat& operator=(const GraphMat&);
	void ShowM(); //���������� �������
	void AdV(); //������ �������
	void AdE(int v, int u); //������ �����
	void DelV(int k); //�������� ������� �� �������
	void DelE(int v, int u); // �������� �����
	int getIndex(int* w, int size, int v_n); //����� ������� != �� �������
	int GetSize(GraphMat G);

	int Get_i_j(GraphMat G, int i, int j);

	int Get_Name(GraphMat G, int i);

	GraphMat RG(int t, double c); //���������� ���� ������-����� (���������)
};
