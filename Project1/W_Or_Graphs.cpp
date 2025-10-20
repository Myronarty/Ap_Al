#include "W_Or_Graphs.h"

void OrGraphMat::AdE(int v, int u)
{
	v = getIndex(b, n, v);
	u = getIndex(b, n, u);
	if (v == -1 || u == -1)
	{
		return;
	}
	a[v * n + u] = 1;
}

void OrGraphMat::DelE(int v, int u)
{
	if (v > n || u > n)
	{
		return;
	}
	v = getIndex(b, n, v);
	u = getIndex(b, n, u);
	a[v * n + u] = 0;
}

void WGraphMat::AdE(int v, int u, int w)
{
	v = getIndex(b, n, v);
	u = getIndex(b, n, u);
	if (v == -1 || u == -1)
	{
		return;
	}
	a[v * n + u] = w;
	a[u * n + v] = w;
}

WGraphMat WGraphMat::RG(int t, double c)
{
	WGraphMat G(t);
	//double p = c * log(t) / t;
	random_device rd;
	mt19937 gen(rd());
	bernoulli_distribution d(c);

	for (int i = 0; i < t; i++)
	{
		for (int j = i+1; j < t; j++)
		{
			mt19937 gen(rd());
			uniform_int_distribution<> distrib(1, 451);
			if (d(gen) == 1)
			{
				G.AdE(i + 1, j + 1, distrib(gen));
			}
		}
	}
	return G;
}

void WOrGraphMat::AdE(int v, int u, int w)
{
	v = getIndex(b, n, v);
	u = getIndex(b, n, u);
	if (v == -1 || u == -1)
	{
		return;
	}
	a[v * n + u] = w;
}
