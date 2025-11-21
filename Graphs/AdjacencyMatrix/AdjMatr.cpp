#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int n, m;
    in >> n >> m;
    std::vector<std::vector<int>> matr(n, std::vector<int>(n));
    while (m--)
    {
        int m1, m2;
        in >> m1 >> m2;
        matr[m1 - 1][m2 - 1] = matr[m2 - 1][m1 - 1] = 1;
    }
    for (auto v: matr)
    {
        for (auto a: v)
        {
            out << a << " ";
        }
        out << '\n';
    }
}