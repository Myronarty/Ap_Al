#pragma once
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


double* LUP(double*& A, std::vector<int>& P, int n);

double* rozviazok(double* A, double* b, int n);
