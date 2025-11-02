#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int i;
    in >> i;
    if (i == 1) 
    {
        out << "Yes";
        return 0;
    }
    if (i == 2) 
    {
        int n1, n2;
        in >> n1 >> n2;
        if (n1 > n2) out << "No";
        else out << "Yes";
        return 0;
    }
    std::vector<int> heap(i + 1);
    int index = 1;
    in >> heap[index];
    index++;
    while (index <= i)
    {
        in >> heap[index];
        if (heap[index] < heap[index / 2]) 
        {
            out << "No";
            return 0;
        }
        index++;
    }
    out << "Yes";
    return 0;
}