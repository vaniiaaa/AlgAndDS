#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

int Find(std::vector<int>& cities, int x)
{
    if (cities[x] < 0) return x;
    cities[x] = Find(cities, cities[x]);
    return cities[x];
}

void Union(std::vector<int>& cities, int x, int y, int& counter)
{
    x = Find(cities, x);
    y = Find(cities, y);
    if (x == y) return;
    if (cities[x] < cities[y])
    {
        cities[x] += cities[y];
        cities[y] = x;
    }
    else
    {
        cities[y] += cities[x];
        cities[x] = y;
    }
    counter--;
}

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int Ncities, Nroads, Nquakes;
    in >> Ncities >> Nroads >> Nquakes;
    
    if (Ncities == 1) 
    {
        out << Ncities;
        return 0;
    }

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
    std::vector<bool> destroyed(Nroads + 1, false);
    for (int i = 1; i <= Nquakes; i++) 
    {
        destroyed[quakes[i]] = true;
    }

    std::vector<int> cities(Ncities + 1, -1);
    std::string result;
    int i = Nquakes;
    int counter = Ncities;
    for (int j = 0; j <=Nroads; j++)
    {
        if (!destroyed[j]) Union(cities, roads[j].first, roads[j].second, counter);
    }
    while (counter > 1 && i > 0)
    {
        Union(cities, roads[quakes[i]].first, roads[quakes[i]].second, counter);
        result += "0";
        i--;
    }
    while (i > 0)
    {
        result += "1";
        i--;
    }

    for (int i = result.size() - 1; i >= 0; i--)
        out << result[i];
}
