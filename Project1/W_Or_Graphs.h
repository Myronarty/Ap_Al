#pragma once
#include "GraphMat.h"
#include <iostream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

class OrGraphMat : public GraphMat //нащадок неорієнтованого графа - орієнтований
{
public:
	using GraphMat::GraphMat;
	void AdE(int v, int u);
	void DelE(int v, int u);
};

class WGraphMat : public GraphMat //нащадок неорієнтованого графа - зважений
{
public:
	using GraphMat::GraphMat;
	void AdE(int v, int u, int w);
	WGraphMat RG(int t, double c);
};

class WOrGraphMat : public OrGraphMat //нащадок орієнтованого графа - зважений, просто щоб було
{
public:
	using OrGraphMat::OrGraphMat;
	void AdE(int v, int u, int w);
};
