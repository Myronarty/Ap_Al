#pragma once
#include <iostream>
#include "GraphMat.h"

using namespace std;

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
};

class WOrGraphMat : public OrGraphMat //нащадок орієнтованого графа - зважений, просто щоб було
{
public:
	using OrGraphMat::OrGraphMat;
	void AdE(int v, int u, int w);
};
