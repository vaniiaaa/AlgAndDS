#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main()
{
    int lily;
    vector<int> mosq;
    set<int> set_way;
    cin >> lily;
    for (int i = 0; i < lily; i++)
    {
        int temp;
        cin >> temp;
        mosq.push_back(temp);
    }
    if (lily == 1) 
    {
        cout << mosq[0] << endl << 1;
        return 0;
    }
    if (lily < 3)
    {
        cout << -1;
        return 0;
    }
    vector<int> max_mosq(lily, -1);
    max_mosq[0] = mosq[0];
    vector<int> way(lily, -1);
    if (lily >= 3)
    {
        max_mosq[2] = mosq[0] + mosq[2];
        way[2] = 0;
    }
    if (lily >= 4)
    {
        max_mosq[3] = mosq[0] + mosq[3];
        way[3] = 0;
    }
    for (int i = 4; i < lily; i++)
    {
        max_mosq[i] = mosq[i];
        if (i > 2 && max_mosq[i - 2] > max_mosq[i - 3])
        {
            max_mosq[i] = max_mosq[i - 2] + mosq[i];
            way[i] = i - 2;
        }
        else if (i > 2 && max_mosq[i - 2] < max_mosq[i - 3])
        {
            max_mosq[i] = max_mosq[i - 3] + mosq[i];
            way[i] = i - 3;
        }
        else
        {
            max_mosq[i] = max_mosq[i - 2] + mosq[i];
            way[i] = i - 2;
        }
    }
    cout << max_mosq[lily - 1] << endl;
    for (int i = lily - 1; i >= 0;)
    {
        set_way.insert(++i);
        i = way[--i];
    }
    if (max_mosq[lily - 1] == -1)
    {
        cout << -1;
        return 0;
    }
    if (*(set_way.begin()) != 1)
    {
        cout << -1;
        return 0;
    }
    for (const int &a : set_way)
    {
        cout << a << " ";
    }
}