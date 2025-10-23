#include <fstream>
#include <vector>
#include <iostream>


using namespace std;

struct node
{
    int value;
    long long lower, upper;
    node()
    {
        lower = static_cast<long long>(INT_MIN) - 1;
        upper = static_cast<long long>(INT_MAX) + 1;
    }
};

int main()
{   
    ifstream in("bst.in");
    ofstream out("bst.out");
    int n;
    in >> n;
    vector<node> tree(n + 1);
    int fnum;
    in >> fnum;
    tree[1].value = fnum;
    for (int i = 2; i <= n; i++)
    {
        int value, relpos;
        char LRpos;
        in >> value >> relpos >> LRpos;
        if (LRpos == 'L' && tree[relpos].lower < static_cast<long long>(value) && static_cast<long long>(value) < tree[relpos].value)
        {
            tree[i].value = value;
            tree[i].upper = tree[relpos].value;
            tree[i].lower = tree[relpos].lower;
        }
        else if (LRpos == 'R' && tree[relpos].value <= static_cast<long long>(value)  && static_cast<long long>(value) < tree[relpos].upper)
        {
            tree[i].value = value;
            tree[i].upper = tree[relpos].upper;
            tree[i].lower = tree[relpos].value;
        }
        else
        {
            out << "NO";
            return 0;
        }
    }
    out << "YES";
}