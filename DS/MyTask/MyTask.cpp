#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class SegmTree
{
    std::vector<int> heap;
    int n;

public:
    SegmTree(int size) : n(size), heap(4 * size, INT_MAX) {}
    
    void Add(int index, int val)
    {
        DoAdd(0, n, 1, index, val);
    }
    
    int FindMin(int L, int R)
    {
        return DoFindMin(L, R, 0, n, 1);
    }

private:
    int DoFindMin(int L, int R, int hl, int hr, int v)
    {
        if (L >= R || hr <= L || R <= hl) return INT_MAX;
        if (L <= hl && hr <= R)
            return heap[v];
        int m = (hl + hr) / 2;
        if (R <= m) 
            return DoFindMin(L, R, hl, m, 2*v);
        if (m <= L)
            return DoFindMin(L, R, m, hr, 2*v + 1);
        return std::min(DoFindMin(L, m, hl, m, 2*v), 
                       DoFindMin(m, R, m, hr, 2*v + 1));
    }
    
    void DoAdd(int L, int R, int v, int index, int val)
    {
        if (R - L == 1)
        {
            heap[v] = std::min(heap[v], val);
            return;
        }
        int m = (L + R) / 2;
        index < m ? DoAdd(L, m, 2 * v, index, val) 
                  : DoAdd(m, R, 2 * v + 1, index, val);
        heap[v] = std::min(heap[2 * v], heap[2 * v + 1]);
    }
};

struct team
{
    int x, y, z;
    team() : x(0), y(0), z(0) {}
    team(int a, int b, int c) : x(a), y(b), z(c) {}
};

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int n;
    in >> n;
    std::vector<team> teams(n);
    for (int i = 0; i < n; ++i)
    {
        int a, b, c;
        in >> a >> b >> c;
        team temp(a, b, c);
        teams[i] = temp;
    }
    int count = 0;
    std::sort(teams.begin(), teams.end(), [](const team& a, const team& b){return a.x < b.x;});
    SegmTree tree(3*n);
    for (const team& t: teams)
    {
        int min = tree.FindMin(1, t.y);
        if (min > t.z) count++;
        tree.Add(t.y, t.z); 
    }
    out << count;
    return 0;
}