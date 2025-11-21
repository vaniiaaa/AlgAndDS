#include <iostream>
#include <vector>
#include <list>
#include <fstream>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int n, m;
    in >> n >> m;
    std::vector<std::list<int>> adjList(n + 1); 
    while (m--) 
    {
        int u, v;
        in >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        
    }
    
    for (int i = 1; i <= n; ++i) 
    {
        out << adjList[i].size() << " ";
        for (const auto& a : adjList[i]) 
        {
            out << a << ' ';
        }
        out << '\n';
    }
}
