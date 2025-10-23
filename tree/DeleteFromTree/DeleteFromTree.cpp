#include <fstream>
#include <string>

#include "..\Tree.hpp"

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int del, root;
    in >> del;
    std::string line;
    std::getline(in, line);
    in >> root;
    BSTree<int>* tree = new BSTree<int>(root);
    while (!in.eof())
    {
        in >> root;
        tree->AddValue(root);
    }
    tree->deleteRight(tree, del);
    tree->PreOrderLeft(out);

}