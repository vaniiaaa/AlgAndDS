#include <iostream>
#include <vector>
using namespace std;

long long GetSum(int pos, const vector<long long>& v)
{
    long long res = 0;
    for (int i = pos; i > 0; i -= i & (-i)) 
        res += v[i];
    return res;
}

void Update(int pos, int x, vector<long long>& v)
{
    for (int i = pos; i < v.size(); i += i & (-i))
        v[i] += x;
}

int main()
{
    int size;
    cin >> size;
    vector<long long> Ryabko(size + 1, 0);
    int i = 1;
    while (i <= size)
    {
        int temp;
        cin >> temp;
        Update(i, temp, Ryabko);
        i++;
    }
    cin >> size;
    i = 0;
    while (i < size)
    {
        string task;
        cin >> task;
        if (task == "FindSum")
        {
            int l, r;
            cin >> l >> r;
            cout << GetSum(r, Ryabko) - GetSum(l, Ryabko) << '\n';
        }
        else
        {
            int pos, x;
            cin >> pos >> x;
            Update(pos + 1, x, Ryabko);
        }
        i++;
    }
    return 0;
}