#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

struct Stats 
{
    long long comparisons = 0; // Кількість порівнянь
    long long copies = 0;      // Кількість записів у масив (копіювань)
    long long memory = 0;      // Використана додаткова пам'ять (у байтах)
    double time = 0.0;         // Час виконання

    void reset() 
    {
        comparisons = 0;
        copies = 0;
        memory = 0;
        time = 0.0;
    }
};

struct Node_
{
    int data;
    Node_* next;

    Node_(int val)
    {
        data = val;
        next = nullptr;
    }
};

enum ArrayType {
    RANDOM,
    SORTED,
    REVERSE_SORTED,
    ALMOST_SORTED,
    FEW_UNIQUE
};

int* generateArray(int n, ArrayType type);

void Top_DownMS(int* x, int n, Stats& stats);

void Bottom_UpMS(int* x, int n);

void Bottom_UpMS_withMods(int* x, int n, Stats& stats);

void Top_DownMS_Node_(Node_** x);