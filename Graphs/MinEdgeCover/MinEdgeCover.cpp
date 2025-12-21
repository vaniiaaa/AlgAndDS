#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <climits>

class Network;

class Graph
{
    int size;
    std::vector<std::list<std::pair<int, int>>> adjlist;
    std::vector<int> Edges;
public:
    Graph(int n): size(n), adjlist(n + 1), Edges(n + 1) {}
    
    void AddEdge(int u, int v, int weight)
    {
        adjlist[u].push_back(std::pair(weight, v));
    }
    
    int GetSize() {return size;}
    std::vector<std::list<std::pair<int, int>>>& GetList() {return adjlist;}
    
    bool MakeEdges(const Network& n);
    
    bool distance()
    {
        std::vector<int> dist(2 * size + 1, 0); 
        std::vector<int> pred(2 * size + 1, -1);
        int last_change_node;

        for (int i = 0; i < 2 * size; ++i)
        {
            last_change_node = -1;
            for (int u = 1; u <= size; ++u)
            {
                for (auto pair : adjlist[u])
                {
                    int risk = pair.first;     
                    int ind_v = pair.second + size;   
                    if (Edges[u] == pair.second)
                    {
                        if (dist[u] > dist[ind_v] - risk)
                        {
                            dist[u] = dist[ind_v] - risk;
                            pred[u] = ind_v;
                            last_change_node = u;
                        }
                    }
                    else
                    {
                        if (dist[ind_v] > dist[u] + risk)
                        {
                            dist[ind_v] = dist[u] + risk;
                            pred[ind_v] = u;
                            last_change_node = ind_v;
                        }
                    }
                }
            }
        }
        if (last_change_node != -1)
        {
            for (int i = 0; i < 2 * size; ++i) last_change_node = pred[last_change_node];
            std::vector<int> cycle_nodes;
            int cur = last_change_node;
            while (true)
            {
                cycle_nodes.push_back(cur);
                if (cur == last_change_node && cycle_nodes.size() > 1) break;
                cur = pred[cur];
            }
            for (int k = 0; k < cycle_nodes.size() - 1; ++k)
            {
                int to = cycle_nodes[k];   
                int from = cycle_nodes[k+1]; 
                if (from <= size && to > size)
                {
                    Edges[from] = to - size;
                }
            }
            return true;
        }

        return false; 
    }

    void Output(std::ofstream& out)
    {
        for (int i = 1; i < Edges.size(); ++i)
        {
            out << Edges[i] << " ";
        }
    }

    int Count()
    {
        int sum = 0;
        for (int u = 1; u <= size; ++u)
        {
            for (auto pair: adjlist[u])
            {
                if (pair.second == Edges[u])
                {
                    sum += pair.first;
                    break;
                }
            }
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

        for (int v = N + 1; v <= 2 * N; ++v)
        {
            Net[v].push_back(i);
            Edges.push_back(edge(v, size - 1, 1));
            Net[size - 1].push_back(++i);
            Edges.push_back(edge(size - 1, v, 0));
            i++;
        }
    }

    bool IsAvailable(int u) { return Edges[u].weight != 0; }
    
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
            if(visited[size - 1] == false) break; 
            Rebuild(size - 1);  
        }
    }

};

bool Graph::MakeEdges(const Network& n)
{
    for (int i = 1; i <= size; i++)
    {
        bool flag(false);
        for (auto a: n.Net[i])
        {
            if (n.Edges[a].weight == 0 && n.Edges[a].target > size) 
            {
                flag = true;
                Edges[i] = n.Edges[a].target - size;
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
            G.AddEdge(day, i, risk);
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
    while(G.distance()); 
    
    out << G.Count() << '\n';
    G.Output(out);
    return 0;
}
