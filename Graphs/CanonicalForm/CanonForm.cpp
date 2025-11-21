#include <iostream>
#include <vector>
#include <fstream>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int n;
    in >> n;
    std::vector<int> tree(n);
    n--;
    while (n--) 
    {
        int root, node;
        in >> root >> node;
        tree[node - 1] = root;
    }
    for (const auto& parent : tree) {
        out << parent << ' ';
    }
}