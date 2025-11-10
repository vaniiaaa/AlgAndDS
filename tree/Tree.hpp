template<typename T>
class BSTree
{
    T value;
    BSTree<T> *left;
    BSTree<T> *right;
    BSTree() : value(0), left(nullptr), right(nullptr) {}
public:
    
    BSTree(int val) : value(val), left(nullptr), right(nullptr) {}
    ~BSTree()
    {
        left = nullptr;
        right = nullptr;
    }

    void AddValue(int val)
    {
        if (val == value) return;
        if (val < value)
        {
            if (left == nullptr)
                left = new BSTree<T>(val);
            else
                left->AddValue(val);
        }
        else
        {
            if (right == nullptr)
                right = new BSTree<T>(val);
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
        if (left != nullptr) left->deleteTree();
        left = nullptr;
        if (right != nullptr) right->deleteTree();
        right = nullptr;
    }

    void deleteRight(BSTree<T>*& node, int val)
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
                BSTree<T>* temp = (node->left != nullptr) ? node->left : node->right;
                delete node;
                node = temp;
            }
            else
            {
                BSTree<T>* parent = node;
                BSTree<T>* minNode = node->right;

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

    void deleteLeft(BSTree<T>*& node, int val)
    {
        if (node == nullptr) return;

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
                BSTree<T>* temp = (node->left != nullptr) ? node->left : node->right;
                delete node;
                node = temp;
            }
            else
            {
                BSTree<T>* parent = node;
                BSTree<T>* maxNode = node->left;
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

    void PreOrderRight(std::ostream& out)
    {
        out << value << '\n';
        if (right != nullptr)
            right->PreOrderRight(out);
        if (left != nullptr)
            left->PreOrderRight(out);
    }

//-------------------------ПРЯМОЙ ЛЕВЫЙ ОБХОД-------------------------

    void PreOrderLeft(std::ostream& out)
    {
        out << value << '\n';
        if (left != nullptr)
            left->PreOrderLeft(out);
        if (right != nullptr)
            right->PreOrderLeft(out);
    }

//-------------------------ОБРАТНЫЙ ПРАВЫЙ ОБХОД-------------------------

    void PostOrderRight(std::ostream& out)
    {
        if (right != nullptr)
            right->PostOrderRight(out);
        if (left != nullptr)
            left->PostOrderRight(out);
        out << value << '\n';
    }

//-------------------------ОБРАТНЫЙ ЛЕВЫЙ ОБХОД-------------------------
    
    void PostOrderLeft(std::ostream& out)
    {
        if (left != nullptr)
            left->PostOrderLeft(out);
        if (right != nullptr)
            right->PostOrderLeft(out);
        out << value << '\n';
    }

//-------------------------ВНУТРЕННИЙ ПРАВЫЙ ОБХОД-------------------------


    void InOrderRight(std::ostream& out)
    {
        if (right != nullptr)
            right->InOrderRight(out);
        out << value << '\n';
        if (left != nullptr)
            left->InOrderRight(out);
    }

//-------------------------ВНУТРЕННИЙ ЛЕВЫЙ ОБХОД-------------------------

    void InOrderLeft(std::ostream& out)
    {
        if (left != nullptr)
            left->InOrderLeft(out);
        out << value << '\n';
        if (right != nullptr)
            right->InOrderLeft(out);
    }


private:
    int GetValue() const { return value; }
    
    /*BSTree<T>* FindParent(int val)
    {
        if ((left != nullptr && left->value == val) || (right != nullptr && right->value == val))
            return this;
        else if (val < value)
        {
            if (left == nullptr)
                return nullptr;
            else
                return left->FindParent(val);
        }
        else
        {
            if (right == nullptr)
                return nullptr;
            else
                return right->FindParent(val);
        }
    }*/



    /*BSTree<T><T>* FindNode(int val) 
    {
        if (val == value)
            return this;
        else if (val < value)
        {
            if (left == nullptr)
                return nullptr;
            else
                return left->FindNode(val);
        }
        else
        {
            if (right == nullptr)
                return nullptr;
            else
                return right->FindNode(val);
        }
    }*/

    /*void SeparateWays()
    {
        int index = wayfornodes.size() - 1;
        if (value == wayfornodes[index][0]->GetValue()) 
        {
            wayfornodes.push_back(wayfornodes[index]);
        }
        std::vector<BSTree*> way1(wayfornodes[index].begin(), wayfornodes[index].end() - 1);
        std::vector<BSTree*> way2(wayfornodes[index].begin() + 1, wayfornodes[index].end());
        wayfornodes[index] = way1;
        wayfornodes.push_back(way2);
    }*/
    
};