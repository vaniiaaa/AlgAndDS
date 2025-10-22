#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

struct node
{
    long long value;
    char LRpos;
    long long relpos;
    long long lower, upper;
    node()
    {
        lower = INT_MIN;
        upper = (long long)INT_MAX + 1;
    }
};

int main()
{
    ifstream in("bst.in");
    ofstream out("bst.out");
    long long n;
    in >> n;
    vector<node> tree(n + 1);
    long long fnum;
    in >> fnum;
    tree[1].value = fnum;
    for (long long i = 2; i <= n; i++)
    {
        long long value, relpos;
        char LRpos;
        in >> value >> relpos >> LRpos;
        if (LRpos == 'L' && tree[relpos].lower < (long long)value && (long long)value < tree[relpos].value)
        {
            tree[i].value = value;
            tree[i].upper = tree[relpos].value;
            tree[i].lower = tree[relpos].lower;
        }
        else if (LRpos == 'R' && (long long)value >= tree[relpos].value && (long long)value < tree[relpos].upper)
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