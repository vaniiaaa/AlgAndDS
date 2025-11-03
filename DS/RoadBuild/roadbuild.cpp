#include <iostream>
#include <fstream>
#include <vector>

int Find(std::vector<int>& cities, int x)
{
    if (cities[x] < 0) return x;
    cities[x] = Find(cities, cities[x]);
    return cities[x];
}

bool Union(std::vector<int>& cities, int x, int y)
{
    x = Find(cities, x);
    y = Find(cities, y);
    if (x == y) return false;
    if (cities[x] > cities[y])
    {
        cities[y] += cities[x];
        cities[x] = y;  
        
    }
    else 
    {
        cities[x] += cities[y];
        cities[y] = x;
        
    }
    return true;
}

void show(std::vector<int> c)
{
    for (int a: c) std::cout << a << " ";
    std::cout << '\n';
}
int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int Ncities, Nroads;
    in >> Ncities >> Nroads;
    std::vector<int> cities(Ncities + 1, -1);
    int i = Nroads;
    int num1, num2;
    while (i != 1)
    {
        int num1, num2;
        in >> num1 >> num2;
        if(Union(cities, num1, num2)) Ncities--;
        out << Ncities << '\n';
        i--;
    }
    in >> num1 >> num2;
    if(Union(cities, num1, num2)) Ncities--;
        out << Ncities;
    return 0;

}