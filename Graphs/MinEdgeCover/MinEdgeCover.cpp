#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <stack>

class Graph
{
    int size;
    std::vector<std::list<std::pair<int, int>>> adjlist;
public:
    Graph(int n): size(n), adjlist(n + 1) {}
    void AddEdge(int u, int v, int weight)
    {
        adjlist[u].push_back(std::pair(weight, v));
    }
    int GetSize() {return size;}
    std::vector<std::list<std::pair<int, int>>>& GetList() {return adjlist;}
};

class Network
{
    int size;
    struct edge
    {
        int source, target, weight;
        edge(int u, int v, int to): source(u), target(v), weight(to) {};
    };
    std::vector<std::list<int>> Net;
    std::vector<edge> Edges;
    std::vector<bool> visited;
    std::vector<int> pred;
    Network(Graph& G) : Net(2 * G.GetSize() + 2), visited(2 * G.GetSize() + 2), pred(2 * G.GetSize() + 2)
    {
        size = 2 * G.GetSize() + 2;
        int i = 0, k = 1;
        while (k <= G.GetSize())
        {
            Net[0].push_back(i);
            Edges.push_back(edge(0, k, 1));
            Net[k].push_back(++i);
            Edges.push_back(edge(k, 0, 0));
            k++;
            i++;
        }
        auto vect = G.GetList();
        int v = 1;
        int last = size;
        while (v < size)
        {
            for (auto list: vect)
            {
                for (auto pair: list)
                {
                    Net[v].push_back(i);
                    Edges.push_back(edge(v, pair.second, 1));
                    Net[pair.second].push_back(++i);
                    Edges.push_back(edge(pair.second, v, 0)); 
                    i++;
                }
            }
            v++;
        }
        while (v < 2 * G.GetSize())
        {
            Net[v].push_back(i);
            Edges.push_back(edge(v, size, 1));
            Net[size].push_back(++i);
            Edges.push_back(edge(size, v, 0)); 
            i++;
            v++;
        }
    }
    bool IsAvailable(int u)
    {
        return Edges[u].weight != 0;
    }
    void Rebuild(int v)
    {
        if (v == 0) return;
        int edge = pred[v];
        v = Edges[edge].source;
        Edges[edge].weight = 0;
        Edges[edge + 1].weight = 1;
        Rebuild(v);
    }
    void dfs(int v)
    {
        if (visited[v]) return;
        else 
        {
            visited[v] = true;
            for (auto u: Net[v])
            {
                if(IsAvailable(u))
                {
                    pred[u] = v;
                    dfs(u);
                }
            }
        }

    }
    void max_flow()
    {
        while (true)
        {
            for (int i = 0; i < pred.size(); i++)
            {
                pred[i] = -1;
                visited[i] = false;
            }
            dfs(0);
            if(visited[size] == false) break;
            Rebuild(size);
        }
    }
};

int main()
{
    std::ifstream in("arms.in");
    std::ofstream out("arms.out");
}