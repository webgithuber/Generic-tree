#include <vector>
#ifndef TREE_H
#define TREE_H
#define ll long long int
#define ff first
#define ss second

template <typename T>
class Tree
{
private:
    vector<int> row(30, -1);
    vvi up; // binary_lift matrix

    int size; // no of vertex in Tree

    vector<T> *ptr; // to point adjacency list

    vector<int> eluer, first_occur, last_occur, level_arr;
    // vectors for eluer array ,first and last occurence index of vertex .

    void eluer_dfs(int, int, int); // eluer dfs form eluer array

public:
    Tree(int n); // constructor

    void add_edge(int s, int d, int wt); // add edge between s-d.

    int level(int i); // return level from root node.

    void eluer(int x); // do eluer dsf by making x as root node, intialize eluer array

    std::vector<T> *adj_list(int n); // return adjacency list of nth node.

    void binary_lift(int a, int b); // form binary_lift matrix ,b is parent of a.

    int kth_ancestor(int a, int k); // return kth ancestor of a.

    int LCA(int a, int b); // return lca for node a and b.
};
template <typename T>
Tree<T>::Tree(int n)
{
    size = n;
    ptr = new vector<T>[n + 1];
    up.resize(n, row);
}
template <typename T>
void Tree<T>::add_edge(int s, int d, int wt)
{
    ptr[s].push_back({d, wt});
    ptr[d].push_back({s, wt});
}
template <typename T>
std::vector<T> *Tree<T>::adj_list(int n)
{
    return &ptr[n];
}
template <typename T>
void Tree<T>::eluer(int x)
{
    level_arr.resize(size + 1, -1);
    eluer_dfs(x, 0, -1);
    first_occur.resize(size + 1, -1);
    last_occur.resize(size + 1, -1);

    for (int i = 0; i < eluer.size(); i++)
    {
        if (first_occur[eluer[i]] == -1)
        {
            first_occur[eluer[i]] = i;
        }
        last_occur[eluer[i]] = i;
    }
}
template <typename T>
void Tree<T>::eluer_dfs(int i, int j, int prnt)
{
    eluer.push_back(i);
    level_arr[i] = j;
    auto it = ptr[i].begin();
    for (; it != ptr[i].end(); it++)
    {
        if (prnt != *it)
        {
            eluer_dfs(*it, j + 1, i);
        }
    }
    eluer.push_back(i);
}

template <typename T>
void Tree<T>::binary_lift(int i, int prnt)
{
    up[i][0] = prnt;
    int j = 1;
    while (j < 21 && up[i][j - 1] != -1 && up[up[i][j - 1]][j - 1] != -1)
    {
        up[i][j] = up[up[i][j - 1]][j - 1];
        j++;
    }

    for (auto it : ptr[i])
    {
        if (*it != prnt)
        {
            binary_lift(B, *it, i);
        }
    }
}

template <typename T>
int Tree<T>::kth_ancestor(int a, int k)
{
    for (int i = 29; i >= 0; i--)
    {
        if ((1ll << i) & k)
        {
            a = up[a][i];
        }
    }
    return a;
}
template <typename T>
int Tree<T>::LCA(int a, int b)
{

    if (level(a) < level(b))
    {
        swap(a, b);
    }
    a = kth_ancestor(a, abs(level(a) - level(b)));

    if (a == b)
    {
        return a;
    }

    for (int i = 20; i >= 0; i--)
    {
        if (up[a][i] != up[b][i])
        {
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}
#endif