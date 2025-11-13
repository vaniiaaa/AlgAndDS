#include <iostream>
#include <fstream>
#include <vector>

void Hash(std::vector<int>& hash, int x, int m, int c) 
{
    for (int i = 0; i < m; i++) 
    {
        int index = ((x % m) + c * i) % m;
        if (hash[index] == x)
            return;
        if (hash[index] == -1) 
        {
            hash[index] = x;
            return;
        }
    }
}


int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int n = 0, m = 0, c = 0;
    in >> m >> c >> n;
    std::vector<int> hash(m, -1);
    int i = 0;
    while (n > 0)
    {
        i = 0;
        int num = 0;
        in >> num;
        Hash(hash, num, m, c);
        n--;
    }
    for (int a: hash)
        out << a << " ";
    return 0;
    
}