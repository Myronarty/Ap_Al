#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct Node 
{
    int data;
    Node* parent;
    int size;

    explicit Node(int value) : data(value), parent(this), size(1) {}
};

struct UnionFind
{
private:
    vector<Node*> nodes;
    int size;
public:

    UnionFind(int n);

    ~UnionFind();
    UnionFind(const UnionFind&) = delete;
    UnionFind& operator=(const UnionFind&) = delete;

    Node* Find(int x);
    void Union(int x, int y);
    int Size();
};
