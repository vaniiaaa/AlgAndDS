#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

class BSTree {
    static int maxway;
    static std::vector<BSTree*> roots;
    static std::vector<std::pair<std::vector<BSTree*>, BSTree*>> wayfornodes;

    int leftsubtree, rightsubtree;
    int value;
    int size;
    BSTree *left;
    BSTree *right;

public:
    BSTree(int val) : value(val), left(nullptr), right(nullptr), size(1), leftsubtree(0), rightsubtree(0) {}

    ~BSTree() {
        if (left) delete left;
        if (right) delete right;
    }

    int GetValue() const { return value; }

    void CalcSize() {
        size = 1;
        if (left) { left->CalcSize(); size += left->size; }
        if (right) { right->CalcSize(); size += right->size; }
    }
    
    int GetDescendantsCount() const { return size - 1; }

    BSTree* GetDeepest() {
        if (!left && !right) return this;
        if (!left) return right->GetDeepest();
        if (!right) return left->GetDeepest();
        
        if (leftsubtree >= rightsubtree) return left->GetDeepest();
        else return right->GetDeepest();
    }

    void StartFindSubTrees() {
        CalcSize();
        maxway = 0;
        roots.clear();
        wayfornodes.clear();
        FindSubTrees(this);
    }

    int FindSubTrees(BSTree *node) {
        if (node == nullptr) return 0;
        
        int leftH = FindSubTrees(node->left);
        int rightH = FindSubTrees(node->right);

        node->leftsubtree = leftH;
        node->rightsubtree = rightH;

        int fullLen = leftH + rightH + 1;
        BSTree* endL = (node->left) ? node->left->GetDeepest() : node;
        BSTree* endR = (node->right) ? node->right->GetDeepest() : node;


        int validLen = 0;
        
        if (endL->GetDescendantsCount() != endR->GetDescendantsCount()) {
            validLen = fullLen;
        } else {

            validLen = (fullLen > 1) ? fullLen - 1 : 0;
        }

        if (validLen > 0) {
            if (validLen > maxway) {
                maxway = validLen;
                roots.clear();
                roots.push_back(node);
            } else if (validLen == maxway) {
                roots.push_back(node);
            }
        }

        return std::max(leftH, rightH) + 1;
    }

    void MakeWays() {
        for (auto root : roots) {
            std::vector<BSTree*> currentWay;
            
            BuildWayLeft(root->left, currentWay);
            currentWay.push_back(root);
            BuildWayRight(root->right, currentWay);

            if (currentWay.empty()) continue;


            bool fullPathValid = (currentWay.front()->GetDescendantsCount() != currentWay.back()->GetDescendantsCount());
            
            if (currentWay.size() == maxway && fullPathValid) {
                wayfornodes.push_back({currentWay, root});
            }

            else if (currentWay.size() > maxway) {

                if (currentWay.size() - 1 == maxway) {
                    std::vector<BSTree*> p1(currentWay.begin() + 1, currentWay.end());
                    if (p1.front()->GetDescendantsCount() != p1.back()->GetDescendantsCount()) {
                        wayfornodes.push_back({p1, root});
                    }

                    std::vector<BSTree*> p2(currentWay.begin(), currentWay.end() - 1);
                    if (p2.front()->GetDescendantsCount() != p2.back()->GetDescendantsCount()) {
                        wayfornodes.push_back({p2, root});
                    }
                }
            }
        }
    }

    void BuildWayLeft(BSTree *node, std::vector<BSTree*> &currentWay) {
        if (!node) return;
        if (node->leftsubtree >= node->rightsubtree) {
            BuildWayLeft(node->left, currentWay);
            currentWay.push_back(node);
        } else {
            BuildWayLeft(node->right, currentWay);
            currentWay.push_back(node);
        }
    }

    void BuildWayRight(BSTree *node, std::vector<BSTree*> &currentWay) {
        if (!node) return;
        if (node->leftsubtree >= node->rightsubtree) {
            currentWay.push_back(node);
            BuildWayRight(node->left, currentWay);
        } else {
            currentWay.push_back(node);
            BuildWayRight(node->right, currentWay);
        }
    }

    void FindNodeToDelete() {
        if (wayfornodes.empty()) return;

        long long minSum = LLONG_MAX;


        for (auto &pair : wayfornodes) {
            long long s = (long long)pair.first.front()->value + pair.first.back()->value;
            if (s < minSum) minSum = s;
        }

        std::vector<int> candidates;
        for (int i = 0; i < wayfornodes.size(); ++i) {
            long long s = (long long)wayfornodes[i].first.front()->value + wayfornodes[i].first.back()->value;
            if (s == minSum) candidates.push_back(i);
        }

        int minRootVal = INT_MAX;
        for (int i : candidates) {
            if (wayfornodes[i].second->value < minRootVal) 
                minRootVal = wayfornodes[i].second->value;
        }

        std::vector<int> finalCandidates;
        for (int i : candidates) {
            if (wayfornodes[i].second->value == minRootVal)
                finalCandidates.push_back(i);
        }

        std::set<int> distinctMiddleNodes;

        for (int i : finalCandidates) {
            auto &path = wayfornodes[i].first;
        
            if (path.size() % 2 == 0) continue; 
           
            std::vector<BSTree*> sortedPath = path;
            std::sort(sortedPath.begin(), sortedPath.end(), [](BSTree* a, BSTree* b){
                return a->GetValue() < b->GetValue();
            });
            
            distinctMiddleNodes.insert(sortedPath[sortedPath.size() / 2]->GetValue());
        }

        if (distinctMiddleNodes.size() != 1) return;

        int valToDelete = *distinctMiddleNodes.begin();
        
        BSTree* ptr = this; 
        deleteRight(ptr, valToDelete);
    }

    void ShowWays() {
        for (auto a: roots) std::cout << a->value << " ";
        std::cout << '\n';
        for (auto a: wayfornodes) {
            for (auto b: a.first) std::cout << b->value << " ";
            std::cout << "Root: " << a.second->value;
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
        if (node == nullptr) return;
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
            
                node->left = nullptr; 
                node->right = nullptr;
                
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

                minNode->right = nullptr; 
                
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
std::vector<std::pair<std::vector<BSTree*>, BSTree*>> BSTree::wayfornodes = {};

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