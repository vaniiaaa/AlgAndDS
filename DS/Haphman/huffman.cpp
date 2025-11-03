#include <iostream>
#include <fstream>

int main()
{
    std::ifstream in("huffman.in");
    std::ofstream out("huffman.out");
    int res = 0, size;
    in >> size;
    res = 0;
    int first, second;
    in >> first >> second;
    res += first + second;
    first = res;
    while(size > 2)
    {
        in >> second;
        first += second;
        res += first;
        size--;
    }
    out << res;
}