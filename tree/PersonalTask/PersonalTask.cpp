#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

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
            BuildWay(root->left, currentWay);
            currentWay.push_back(root);
            BuildWay(root->right, currentWay);
            wayfornodes.push_back(currentWay);
        }
    }

    void SeparateWays()
    {
        int index = wayfornodes.size() - 1;
        if (value == wayfornodes[index][0]->GetValue()) return;
        
    }
    

    void BuildWay(BSTree *node, std::vector<BSTree *> &currentWay)
    {
        if (!node)
            return;
        if (node->leftsubtree >= node->rightsubtree)
            BuildWay(node->left, currentWay);
        else
            BuildWay(node->right, currentWay);
        currentWay.push_back(node);
    }

    void FindNodeToDelete()
    {
        int minsum = INT_MAX;
        int minindex = -1;
        for (size_t index = 0; index < wayfornodes.size(); ++index)
        {
            if (wayfornodes[index].size() < 2)
                continue;
            int currsum1 = wayfornodes[index][0]->GetValue() + wayfornodes[index].back()->GetValue();
            int currsum2 = INT_MAX;
            if (wayfornodes[index].size() >= 3)
            {
                currsum2 = wayfornodes[index][1]->GetValue() + wayfornodes[index][wayfornodes[index].size() - 2]->GetValue();
            }
            int currsum = std::min(currsum1, currsum2);
            if (currsum < minsum)
            {
                minsum = currsum;
                minindex = index;
            }
            else if (currsum == minsum && minindex >= 0)
            {
                if (roots[index]->GetValue() < roots[minindex]->GetValue())
                    minindex = index;
            }
        }
        if (minindex >= 0 && !wayfornodes[minindex].empty())
        {
            const std::vector<BSTree*>& path = wayfornodes[minindex];
            int sum = 0;
            for (const auto* node : path)
                sum += node->GetValue();
            double avg = static_cast<double>(sum) / path.size();
            int minDiff = INT_MAX;
            int valueToDelete = path[0]->GetValue();
            for (const auto* node : path)
            {
                int diff = std::abs(node->GetValue() - avg);
                if (diff < minDiff)
                {
                    minDiff = diff;
                    valueToDelete = node->GetValue();
                }
            }
            BSTree* rootPtr = this;
            deleteRight(rootPtr, valueToDelete);
        }

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
    Tree->FindSubTrees(Tree);
    Tree->MakeWays();
    Tree->FindNodeToDelete();
    Tree->PreOrderLeft(out);
    in.close();
    out.close();
    return 0;
}
