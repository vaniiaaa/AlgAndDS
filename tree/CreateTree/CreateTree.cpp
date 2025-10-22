#include <iostream>
#include <fstream>

#include "..\Tree.hpp"

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int temp;
    in >> temp;
    BSTree* tree = new BSTree(temp);
    while (!in.eof())
    {
       in >> temp;
       tree->AddValue(temp);
    }
    tree->PreOrderLeft(out);

}