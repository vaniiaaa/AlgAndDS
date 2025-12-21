#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
class Network;

class Graph
{
    int size;
    std::vector<std::list<std::pair<int, int>>> adjlist;
    std::vector<int> Edges;
public:
    Graph(int n): size(n), adjlist(2*n + 1), Edges(n + 1) {}
    void AddEdge(int u, int v, int weight)
    {
        adjlist[u].push_back(std::pair(weight, v));
    }
    int GetSize() {return size;}
    std::vector<std::list<std::pair<int, int>>>& GetList() {return adjlist;}
    bool MakeEdges(const Network& n);
    
    void distance(int start)
    {
        std::vector<int> dist(2 * size + 1, INT_MAX);
        std::vector<int> pred(2 * size + 1, -1);

        dist[start] = 0;
        int i = 0;

        while (i < size)
        {
            int index = 1;
            for (auto list : adjlist)
            {
                for (auto pair : list)
                {
                    int c = (Edges[index] == pair.second) ? pair.first * -1 : pair.first;

                    if (dist[index] != INT_MAX && dist[pair.second] > dist[index] + c)
                    {
                        dist[pair.second] = dist[index] + c;
                        pred[pair.second] = index;

                        if (i == size - 1)
                        {
                            int y = pair.second;
                            for (int k = 0; k < size; ++k)
                            {
                                if (pred[y] != -1)
                                {
                                    y = pred[y];
                                }
                            }

                            std::vector<int> cycle_nodes;
                            int cur = y;
                            while (true)
                            {
                                cycle_nodes.push_back(cur);
                                if (cur == y && cycle_nodes.size() > 1)
                                {
                                    break;
                                }
                                cur = pred[cur];
                            }

                            std::reverse(cycle_nodes.begin(), cycle_nodes.end());

                            for (size_t k = 0; k < cycle_nodes.size() - 1; ++k)
                            {
                                int u = cycle_nodes[k];
                                int v = cycle_nodes[k + 1];

                                if (u <= size)
                                {
                                    Edges[u] = v;
                                }
                            }
                            return;
                        }
                    }
                }
                index++;
            }
            i++;
        }
    }
    void Output(std::ofstream& out)
    {
        for (auto a: Edges)
        {
            out << a << " ";
        }
    }
    int Count()
    {
        int sum = 0;
        int index = 1;
        for (auto list: adjlist)
        {
            for (auto pair: list)
            {
                if (Edges[index] == pair.second)
                {
                    sum += pair.first;
                    break;
                }
            }
            index++;
        }
        return sum;
    }

};

class Network
{
public:
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
        int N = G.GetSize();
        int i = 0;

        for (int k = 1; k <= N; ++k)
        {
            Net[0].push_back(i);
            Edges.push_back(edge(0, k, 1));
            Net[k].push_back(++i);
            Edges.push_back(edge(k, 0, 0));
            i++;
        }

        auto vect = G.GetList();
        for (int u = 1; u <= N; ++u)
        {
            for (auto pair : vect[u])
            {
                int v = pair.second + N;
                Net[u].push_back(i);
                Edges.push_back(edge(u, v, 1));
                Net[v].push_back(++i);
                Edges.push_back(edge(v, u, 0));
                i++;
            }
        }

        int sink = size - 1;
        for (int v = N + 1; v <= 2 * N; ++v)
        {
            Net[v].push_back(i);
            Edges.push_back(edge(v, sink, 1));
            Net[sink].push_back(++i);
            Edges.push_back(edge(sink, v, 0));
            i++;
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
        int u = Edges[edge].source;
        
        Edges[edge].weight = 0;
        Edges[edge ^ 1].weight = 1;
        
        Rebuild(u);
    }

    void dfs(int v)
    {
        
        visited[v] = true;
        for (int edge_index : Net[v])
        {
            if (IsAvailable(edge_index))
            {
                int to = Edges[edge_index].target;
                
                if (!visited[to])
                {
                    pred[to] = edge_index;
                    dfs(to);
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
    std::vector<std::list<int>>& GetNet() {return Net;}
    std::vector<edge>& GetEdges() {return Edges;}
};

bool Graph::MakeEdges(const Network& n)
    {
        for (int i = 1; i <= size; i++)
        {
            bool flag(false);
            for (auto a: n.Net[i])
            {
                if (n.Edges[a].weight == 0)
                {
                    flag = true;
                    Edges[i] = n.Edges[a].target;
                    break;
                }
            }
            if (!flag) return false;
        }
        return true;
    }

int main()
{
    std::ifstream in("arms.in");
    std::ofstream out("arms.out");
    int size;
    in >> size;
    Graph G(size);
    for (int i = 1; i <= size; i++)
    {
        int j;
        in >> j;
        while (j)
        {
            int day, risk;
            in >> day >> risk;
            G.AddEdge(i, day, risk);
            j--;
        }
    }
    Network Net(G);
    Net.max_flow();
    if (!G.MakeEdges(Net))
    {
        out << -1;
        return 0;
    }
    for (int i = 1; i <= size; i++)
    {
        G.distance(i);
    }
    out << G.Count() << '\n';
    G.Output(out);
    return 0;
}