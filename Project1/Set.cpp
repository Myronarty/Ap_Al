#include "Set.h"

Set::Set()
{
	t = 1001;
	A_ = new int[t] {0};
}

Set::Set(int n)
{
	t = n;
	A_ = new int[t] {0};
}

int Set :: Sett()
{
	return t;
}

Set Set::RandSet(int y)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist_(0, 1);
	Set A(y);
	A.t = y;
	for (int i = 0; i < y; i++)
	{
		A.A_[i] = dist_(gen);
	}
	return A;
}

Set Set::SetU(Set A)
{
	Set U;
	U.t = A.t;
	U.A_ = new int[t] {1};
	return U;
}

Set::Set(const Set&) = default;

Set::Set(Set&&) = default;

Set& Set:: operator=(const Set&) = default;

int& Set:: operator[](int i)
{
	return A_[i];
};

Set& Set:: operator=(Set&&) = default;

Set::~Set() = default;

int* Set::SetA(Set S)
{
	return A_;
}

int Set::Insert(int N)
{
	int j = N % 64;
	int i = (N - j) / 64;
	int t = 1 << j;
	A_[i] = A_[i] | t;
	return N;
}

int Set::Delete(int N)
{
	int j = N % 64;
	int i = (N - j) / 64;
	int t = 1 << j;
	A_[i] = A_[i] & ~t;
	return N;
}

bool Set::Search(int N)
{
	int j = N % 64;
	int i = (N - j) / 64;
	int k = 1 << j;
	bool s = A_[i] & k;
	//cout << s;
	return s;
}

int Set::Clear()
{
	for (int i = 0; i < t; i++)
	{
		A_[i] = 0;
	}
	return 0;
}

Set Set::U(Set A, Set B)
{
	Set C = Set(A.t);
	for (int i = 0; i < t; i++)
	{
		C[i] = A[i] | B[i];
	}
	return C;
}

Set Set::not_U(Set A, Set B)
{
	Set C = Set(A.t);
	for (int i = 0; i < t; i++)
	{
		C[i] = A[i] & B[i];
	}
	return C;
}

Set Set::Diff(Set A, Set B)
{
	Set C = Set(A.t);
	for (int i = 0; i < t; i++)
	{
		C[i] = A[i] & ~(B[i]);
	}
	return C;
}

Set Set::SymDiff(Set A, Set B)
{
	Set C = Set(A.t);
	for (int i = 0; i < t; i++)
	{
		C[i] = (A[i] | B[i]) & (~(A[i]) | ~(B[i]));
	}
	return C;
}

bool Set::IsSubSet(Set A, Set B)
{
	for (int i = 0; i < t; i++)
	{
		if (A[i] != (A[i] & B[i]))
		{
			return 0;
		}
	}
	return 1;
}
