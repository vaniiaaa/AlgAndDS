#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


class BSTree
{
    static int maxway;
    static std::vector<BSTree *> roots;
    static std::vector<std::vector<BSTree *>> wayfornodes;

    int leftsubtree, rightsubtree;
    int value;
    BSTree *left;
    BSTree *right;
    int depth;

    BSTree() : value(0), left(nullptr), right(nullptr) {}

public:
    BSTree(int val) : value(val), left(nullptr), right(nullptr) {}
    ~BSTree()
    {
        left = nullptr;
        right = nullptr;
    }

    int GetValue() const { return value; }

    void StartFindSubTrees()
    {
        int totalCount;
        int leftCount = FindSubTrees(left);
        int rightCount = FindSubTrees(right);
        totalCount = leftCount + rightCount + 1;
        if (totalCount > maxway)
        {
            maxway = totalCount;
            roots.clear();
            roots.push_back(this);
        }
        else if (totalCount == maxway - 1)
        {
            roots.push_back(this);
        }
    }

    int FindSubTrees(BSTree *node)
    {
        if (node == nullptr)
            return 0;

        int leftCount = FindSubTrees(node->left);
        int rightCount = FindSubTrees(node->right);
        int totalCount = leftCount + rightCount + 1;

        if (totalCount > maxway)
        {
            maxway = totalCount;
            roots.clear();
            roots.push_back(node);
        }
        else if (totalCount == maxway)
        {
            roots.push_back(node);
        }

        node->leftsubtree = leftCount;
        node->rightsubtree = rightCount;
        return std::max(leftCount, rightCount) + 1;
    }

    void MakeWays()
    {
        for (auto root : roots)
        {
            std::vector<BSTree *> currentWay;
            BuildWayLeft(root->left, currentWay);
            currentWay.push_back(root);
            BuildWayRight(root->right, currentWay);
            wayfornodes.push_back(currentWay);
        }
    }

    void BuildWayLeft(BSTree *node, std::vector<BSTree *> &currentWay)
    {
        if (!node)
            return;
        if (node->leftsubtree >= node->rightsubtree)
        {
            BuildWayLeft(node->left, currentWay);
            currentWay.push_back(node);
        }
        else
        {
            BuildWayLeft(node->right, currentWay);
            currentWay.push_back(node);
        }
        
    }

    void BuildWayRight(BSTree *node, std::vector<BSTree *> &currentWay)
    {
        if (!node)
            return;
        if (node->leftsubtree >= node->rightsubtree)
        {
            currentWay.push_back(node);
            BuildWayRight(node->left, currentWay);
        }
        else
        {
            currentWay.push_back(node);
            BuildWayRight(node->right, currentWay);
        }
        
    }

    void FindNodeToDelete()
    {
        int minsum = INT_MAX;
        int possubway = -1; //1 - лист - нелист, 2 - нелист лист
        int minindex = -1;
        int currsum1, currsum2;
        for (int index = 0; index < wayfornodes.size(); ++index)
        {
            if (wayfornodes[index][0]->GetValue() == value || wayfornodes[index][wayfornodes[index].size() - 1]->GetValue() == value)
            {
                currsum1 = wayfornodes[index][0]->GetValue() + wayfornodes[index][wayfornodes[index].size() - 1]->GetValue();
                currsum2 = INT_MAX;
            }
            else
            {
                currsum1 = wayfornodes[index][0]->GetValue() + wayfornodes[index][wayfornodes[index].size() - 2]->GetValue();
                currsum2 = wayfornodes[index][1]->GetValue() + wayfornodes[index][wayfornodes[index].size() - 1]->GetValue();
            }
            if (currsum1 < minsum)
            {
                minsum = currsum1;
                possubway = 1;
                minindex = index;
            }
            else if (currsum1 == minsum && roots[index]->GetValue() < roots[minindex]->GetValue())
            {
                minindex = index;
                possubway = 1;
            }
            if (currsum2 < minsum)
            {
                minsum = currsum2;
                possubway = 2;
                minindex = index;
            }
            else if (currsum2 == minsum && roots[index]->GetValue() < roots[minindex]->GetValue())
            {
                minindex = index;
                possubway = 2;
            }
            if (currsum1 == currsum2 && roots[index]->GetValue() == roots[minindex]->GetValue())
                possubway = 3;
        }
        //std::cout << minsum << " " << possubway << " " << minindex << '\n';
        if (minindex >= 0 && !wayfornodes[minindex].empty())
        {
            int valueToDelete;
            if ((wayfornodes[minindex][0]->GetValue() == value || wayfornodes[minindex][wayfornodes[minindex].size() - 1]->GetValue() == value) && wayfornodes[minindex].size() % 2 == 0)
                return;
            else if (wayfornodes[minindex][0]->GetValue() != value && wayfornodes[minindex][wayfornodes[minindex].size() - 1]->GetValue() != value  && wayfornodes[minindex].size() % 2 != 0)
                return;
            if ((wayfornodes[minindex][0]->GetValue() == value || wayfornodes[minindex][wayfornodes[minindex].size() - 1]->GetValue() == value))
                {
                    sort(wayfornodes[minindex].begin(), wayfornodes[minindex].end() - 1, [](const BSTree* n1, const BSTree* n2) {return n1->GetValue() < n2->GetValue();});
                    valueToDelete = wayfornodes[minindex][wayfornodes[minindex].size() / 2]->GetValue();
                }
            else 
            {
                
                if (possubway == 1)
                {
                    sort(wayfornodes[minindex].begin(), wayfornodes[minindex].end() - 1, [](const BSTree* n1, const BSTree* n2) {return n1->GetValue() < n2->GetValue();});
                    valueToDelete = wayfornodes[minindex][wayfornodes[minindex].size() / 2 - 1]->GetValue();
                }
                else if (possubway == 2)
                {
                    sort(wayfornodes[minindex].begin(), wayfornodes[minindex].end() - 1, [](const BSTree* n1, const BSTree* n2) {return n1->GetValue() < n2->GetValue();});
                    valueToDelete = wayfornodes[minindex][wayfornodes[minindex].size() / 2]->GetValue();
                }
                else if (possubway == 3)
                {
                    std::vector<BSTree*> wayfornodes2 (wayfornodes[minindex]);
                    sort(wayfornodes[minindex].begin(), wayfornodes[minindex].end() - 1, [](const BSTree* n1, const BSTree* n2) {return n1->GetValue() < n2->GetValue();});
                    sort(wayfornodes2.begin(), wayfornodes2.end() - 1, [](const BSTree* n1, const BSTree* n2) {return n1->GetValue() < n2->GetValue();});
                    int valueToDelete1 = wayfornodes[minindex][wayfornodes[minindex].size() / 2 - 1]->GetValue();
                    int valueToDelete2 = wayfornodes2[wayfornodes[minindex].size() / 2]->GetValue();
                    if (valueToDelete1 != valueToDelete2) return;
                    else valueToDelete = std::min(valueToDelete1, valueToDelete2);
                }
            }
            BSTree* rootPtr = this;
            deleteRight(rootPtr, valueToDelete);
        }

    }

    void ShowWays()
    {
        for (auto a: roots) std::cout << a->value  << " ";
        std::cout << '\n';
        for (auto a: wayfornodes)
        {
            for (auto b: a)
                std::cout << b->value << " ";
            std::cout << '\n'; 
        }
        std::cout << maxway;
    }

    void AddValue(int val)
    {
        if (val == value)
            return;
        if (val < value)
        {
            if (left == nullptr)
                left = new BSTree(val);
            else
                left->AddValue(val);
        }
        else
        {
            if (right == nullptr)
                right = new BSTree(val);
            else
                right->AddValue(val);
        }
    }

    bool SearchValue(int val)
    {
        if (val == value)
            return true;
        else if (val < value)
        {
            if (left == nullptr)
                return false;
            else
                return left->SearchValue(val);
        }
        else
        {
            if (right == nullptr)
                return false;
            else
                return right->SearchValue(val);
        }
    }

    void deleteTree()
    {
        if (left != nullptr)
            left->deleteTree();
        left = nullptr;
        if (right != nullptr)
            right->deleteTree();
        right = nullptr;
    }

    void deleteRight(BSTree *&node, int val)
    {
        if (node == nullptr)
            return;

        if (val < node->value)
            deleteRight(node->left, val);
        else if (val > node->value)
            deleteRight(node->right, val);
        else
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr || node->right == nullptr)
            {
                BSTree *temp = (node->left != nullptr) ? node->left : node->right;
                delete node;
                node = temp;
            }
            else
            {
                BSTree *parent = node;
                BSTree *minNode = node->right;

                while (minNode->left != nullptr)
                {
                    parent = minNode;
                    minNode = minNode->left;
                }

                node->value = minNode->value;

                if (parent->left == minNode)
                    parent->left = minNode->right;
                else
                    parent->right = minNode->right;
                delete minNode;
            }
        }
    }

    void deleteLeft(BSTree *&node, int val)
    {
        if (node == nullptr)
            return;

        if (val < node->value)
            deleteLeft(node->left, val);
        else if (val > node->value)
            deleteLeft(node->right, val);
        else
        {

            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr || node->right == nullptr)
            {
                BSTree *temp = (node->left != nullptr) ? node->left : node->right;
                delete node;
                node = temp;
            }
            else
            {
                BSTree *parent = node;
                BSTree *maxNode = node->left;
                while (maxNode->right != nullptr)
                {
                    parent = maxNode;
                    maxNode = maxNode->right;
                }
                node->value = maxNode->value;

                if (parent->right == maxNode)
                    parent->right = maxNode->left;
                else
                    parent->left = maxNode->left;

                delete maxNode;
            }
        }
    }
    //-------------------------ПРЯМОЙ ПРАВЫЙ ОБХОД-------------------------

    void PreOrderRight(std::ostream &out)
    {
        out << value << '\n';
        if (right != nullptr)
            right->PreOrderRight(out);
        if (left != nullptr)
            left->PreOrderRight(out);
    }

    //-------------------------ПРЯМОЙ ЛЕВЫЙ ОБХОД-------------------------

    void PreOrderLeft(std::ostream &out)
    {
        out << value << '\n';
        if (left != nullptr)
            left->PreOrderLeft(out);
        if (right != nullptr)
            right->PreOrderLeft(out);
    }
    void PreOrderLeft(std::vector<int>& v)
    {
        v.push_back(value);
        if (left != nullptr)
            left->PreOrderLeft(v);
        if (right != nullptr)
            right->PreOrderLeft(v);
    }

    //-------------------------ОБРАТНЫЙ ПРАВЫЙ ОБХОД-------------------------

    void PostOrderRight(std::ostream &out)
    {
        if (right != nullptr)
            right->PostOrderRight(out);
        if (left != nullptr)
            left->PostOrderRight(out);
        out << value << '\n';
    }

    //-------------------------ОБРАТНЫЙ ЛЕВЫЙ ОБХОД-------------------------

    void PostOrderLeft(std::ostream &out)
    {
        if (left != nullptr)
            left->PostOrderLeft(out);
        if (right != nullptr)
            right->PostOrderLeft(out);
        out << value << '\n';
    }

    //-------------------------ВНУТРЕННИЙ ПРАВЫЙ ОБХОД-------------------------

    void InOrderRight(std::ostream &out)
    {
        if (right != nullptr)
            right->InOrderRight(out);
        out << value << '\n';
        if (left != nullptr)
            left->InOrderRight(out);
    }

    //-------------------------ВНУТРЕННИЙ ЛЕВЫЙ ОБХОД-------------------------

    void InOrderLeft(std::ostream &out)
    {
        if (left != nullptr)
            left->InOrderLeft(out);
        out << value << '\n';
        if (right != nullptr)
            right->InOrderLeft(out);
    }

};

int BSTree::maxway = 0;
std::vector<BSTree *> BSTree::roots = {};
std::vector<std::vector<BSTree *>> BSTree::wayfornodes = {};

int main()
{
    std::ifstream in("tst.in");
    std::ofstream out("tst.out");
    int temp;
    in >> temp;
    BSTree *Tree = new BSTree(temp);
    while (!in.eof())
    {
        in >> temp;
        Tree->AddValue(temp);
    }
    Tree->StartFindSubTrees();
    Tree->MakeWays();
    //Tree->ShowWays();
    Tree->FindNodeToDelete();
    Tree->PreOrderLeft(out);
    in.close();
    out.close();
    return 0;
}