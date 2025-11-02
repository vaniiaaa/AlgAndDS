#include <iostream>
#include <fstream>
#include <vector>

int Find(std::vector<int>& cities, int x)
{
    if (cities[x] < 0) return x;
    cities[x] = Find(cities, cities[x]);
    return x;
}

void Union(std::vector<int>& cities, int x, int y)
{
    x = Find(cities, x);
    y = Find(cities, y);
    if (x != y && cities[x] > cities[y])
    {
        cities[y] += cities[x];
        cities[x] = y;   
    }
    else if (x != y)
    {
        cities[x] += cities[y];
        cities[y] = x;
    }
}

bool IsConnect(const std::vector<int>& cities)
{
    int size = cities.size();
    int negcount;
    int i = 1;
    while (i <= size)
    {
        if (cities[i] < 0) negcount++;
        if (negcount == 2) return false;
        i++;
    }
    return true;
}

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int Ncities, Nroads, Nquakes;
    in >> Ncities >> Nroads >> Nquakes;
    std::vector<std::pair<int, int>> roads(Nroads + 1);
    for (int i = 1; i <= Nroads; i++)
    {
        in >> roads[i].first >> roads[i].second;
    }
    std::vector<int> quakes(Nquakes + 1);
    for (int i = 1; i <= Nquakes; i++)
    {
        in >> quakes[i];
    }
    std::vector<int> cities(Ncities + 1, -1);
    std::string result;
    int i = Nquakes;
    while (true)
    {
        Union(cities, roads[quakes[i]].first, roads[quakes[i]].second);
        if ((Ncities - 1 <= Nquakes - i + 1) && IsConnect(cities)) break;   
        result += '0';
        i--;
    }
    i--;
    result += '1';
    while (i > 0)
    {
        result += '1';
        i--;
    }
    for (int i = result.size() - 1; i >= 0; i--) out << result[i];
    return 0;
}