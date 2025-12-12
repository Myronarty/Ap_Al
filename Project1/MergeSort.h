#pragma once

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

void Top_DownMS(int* x, int n);

void Bottom_UpMS(int* x, int n);

void Bottom_UpMS_withMods(int* x, int n);

void Bottom_UpMS_10(int* x, int n);

void Top_DownMS_Node_(Node_** x);