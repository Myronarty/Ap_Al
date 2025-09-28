#pragma once
#include <iostream>
#include "GraphMat.h"

using namespace std;

class OrGraphMat : public GraphMat //������� ������������� ����� - ����������
{
public:
	using GraphMat::GraphMat;
	void AdE(int v, int u);
	void DelE(int v, int u);
};

class WGraphMat : public GraphMat //������� ������������� ����� - ��������
{
public:
	using GraphMat::GraphMat;
	void AdE(int v, int u, int w);
};

class WOrGraphMat : public OrGraphMat //������� ����������� ����� - ��������, ������ ��� ����
{
public:
	using OrGraphMat::OrGraphMat;
	void AdE(int v, int u, int w);
};
