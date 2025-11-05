#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::ifstream in("huffman.in");
    std::ofstream out("huffman.out");
    
    long long size;
    in >> size;
    
    if (size == 1) 
    {
        out << 0;
        return 0;
    }
    
    std::vector<long long> data(size);
    for (int i = 0; i < size; ++i) 
    {
        in >> data[i];
    }

    int index = 0;
    std::queue<long long> q2;
    
    long long result = 0;
    
    while (index < size || q2.size() > 1) 
    {
        long long first, second;
        if (q2.empty() || (index < size && data[index] <= q2.front())) 
        {
            first = data[index++];
        } 
        else 
        {
            first = q2.front();
            q2.pop();
        }

        if (q2.empty() || (index < size && data[index] <= q2.front())) 
        {
            second = data[index++];
        } 
        else 
        {
            second = q2.front();
            q2.pop();
        }
        long long sum = first + second;
        result += sum;
        q2.push(sum);
    }
    
    out << result;
    
    return 0;
}
