#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

struct Stats_QS
{
    long long comparisons = 0;
    long long swaps = 0;
    long long copies = 0;

    void reset() 
    {
        comparisons = 0;
        swaps = 0;
        copies = 0;
    }
};
typedef int (*PivotStrategy)(int*, int);

typedef void (*SortFunction)(int*, int, int, PivotStrategy, Stats_QS&);

void QS_Lomuto(int* x, int low, int high, int (*op)(int*, int), Stats_QS& stats);

void QS_Goar(int* x, int low, int high, int (*op)(int*, int), Stats_QS& stats);

void three_sides(int* x, int low, int high, int (*op)(int*, int), Stats_QS& stats);

int op_last(int* x, int n);

int op_rand(int* x, int n);

int op_med(int* x, int n);

int op_med_rand(int* x, int n);
