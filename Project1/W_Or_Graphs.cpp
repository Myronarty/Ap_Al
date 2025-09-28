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
