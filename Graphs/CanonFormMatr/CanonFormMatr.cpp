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
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j) 
        {
            int val;
            in >> val;
            if (val == 1) 
            {
                tree[j] = i + 1;  
            }
        }
    }
    for (const auto& parent : tree) {
        out << parent << ' ';
    }
}