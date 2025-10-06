#pragma once
#include "GraphMat.h"
#include <iostream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

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
	WGraphMat RG(int t, double c);
};

class WOrGraphMat : public OrGraphMat //������� ����������� ����� - ��������, ������ ��� ����
{
public:
	using OrGraphMat::OrGraphMat;
	void AdE(int v, int u, int w);
};
