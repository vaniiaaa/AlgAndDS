#include <iostream>
#include <fstream>
#include <queue>

int main()
{
    std::ifstream in("huffman.in");
    std::ofstream out("huffman.out");
    int res = 0, size;
    in >> size;
    res = 0;
    std::priority_queue<long long, std::vector<long long>, std::greater<long long>> nums;
    while(size > 0)
    {
        int temp;
        in >> temp;
        nums.push(temp);
        size--;
    }
    while(nums.size() > 1)
    {
        int n1, n2;
        n1 = nums.top();
        nums.pop();
        n2 = nums.top();
        nums.pop();
        res += n1 + n2;
        nums.push(n1 + n2);
    }
    out << res;
}