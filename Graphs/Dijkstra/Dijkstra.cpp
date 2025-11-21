#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

class Graph
{
    int nodes;
    vector<vector<pair<int, int>>> g;
    vector<bool> processed;
    vector<long long> dist;
public:
    Graph(int v) :nodes(v), g(v + 1), processed(v + 1, false), dist(v + 1, LLONG_MAX) {}

    void Dijkstra(int v1)
    {
        dist[v1] = 0;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        pq.push(pair(0, v1));
        while (!pq.empty())
        {
            pair<long long, int> curr = pq.top();
            pq.pop();
            if (processed[curr.second]) continue;
            processed[curr.second] = true;
            dist[curr.second] = curr.first;
            for (auto l: g[curr.second])
                {
                    if (!processed[l.second] && l.first + curr.first < dist[l.second]) 
                        pq.push(pair(l.first + curr.first, l.second));
                }
            
        }
    }
    long long GetChain(int v)
    {
        return dist[v];
    }
    
    friend ifstream& operator>>(ifstream& in, Graph& Gr)
    {
        int m, i = 1;
        in >> m;
        while (i <= m)
        {
            int v1, v2, w;
            in >> v1 >> v2 >> w;
            Gr.g[v1].push_back(pair(w, v2));
            Gr.g[v2].push_back(pair(w, v1));
            i++;
        }
        return in;
    }
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int v;
    in >> v;
    Graph G(v);
    in >> G;
    G.Dijkstra(1);
    out << G.GetChain(v);
}