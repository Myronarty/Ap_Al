#pragma once
#include <iostream>
#include <string>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Set
{
protected:
	int t;
	int* A_;
public:
	Set();
	Set(int n);
	int Sett();
	Set RandSet(int y);
	Set SetU(Set A);
	Set(const Set&);
	Set(Set&&);
	Set& operator=(const Set&);
	int& operator[](int i);
	Set& operator=(Set&&);
	virtual ~Set();
	int* SetA(Set S);
	int Insert(int N);
	int Delete(int N);
	bool Search(int N);
	int Clear();
	Set U(Set A, Set B);
	Set not_U(Set A, Set B);
	Set Diff(Set A, Set B);
	Set SymDiff(Set A, Set B);
	bool IsSubSet(Set A, Set B);
};
