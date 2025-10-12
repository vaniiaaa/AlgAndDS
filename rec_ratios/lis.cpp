#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int Acount;
    in >> Acount;
    vector<int> A(Acount);
    for (int i = 0; i < Acount; i++)
    {
        in >> A[i];
    }
    
    vector<int> res;

    for(int a: A)
    {
        vector<int>::iterator it = lower_bound(res.begin(), res.end(), a);
        if (it == res.end()) res.push_back(a);    
        else *it = a;
    }
    out << res.size();
}