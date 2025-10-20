#include "UnionFind.h"

UnionFind::UnionFind(int n)
{
    nodes.reserve(n);
    size = n;
    for (int i = 0; i < n; ++i)
    {
        nodes.push_back(new Node(i));
    }
}

UnionFind::~UnionFind()
{
    for (Node* node : nodes)
    {
        delete node;
    }
}

Node* UnionFind::Find(int x)
{
    if (x < 0 || x >= nodes.size())
    {
        return nullptr;
    }

    Node* current = nodes[x];

    Node* root = current;
    while (root->parent != root)
    {
        root = root->parent;
    }

    current = nodes[x];
    while (current != root)
    {
        Node* next_parent = current->parent;
        current->parent = root;
        current = next_parent;
    }

    return root;
}

void UnionFind::Union(int x, int y)
{
    Node* rootX = Find(x);
    Node* rootY = Find(y);

    if (rootX == nullptr || rootY == nullptr || rootX == rootY)
    {
        return;
    }

    if (rootX->size < rootY->size)
    {
        swap(rootX, rootY);
    }

    rootY->parent = rootX;
    rootX->size += rootY->size;
    this->size--;
}

int UnionFind::Size()
{
    return size;
}