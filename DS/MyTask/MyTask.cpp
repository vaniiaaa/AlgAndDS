#include <iostream>
#include <fstream>
#include <vector>

struct team
{
    int x, y, z;
    team(): x(0), y(0), z(0) {}
    team(int a, int b, int c): x(a), y(b), z(c) {}
    bool operator<(const team& other) const
    {
        if (x < other.x && y < other.y && z < other.z)
            return true;
        else 
            return false;
    }
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
    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            if (teams[i] < teams[j])
                ++count;
        }
    }
    out << count;
    return 0;
}