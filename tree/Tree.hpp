class BSTree
{
    int value;
    BSTree *left;
    BSTree *right;
    BSTree() : value(0), left(nullptr), right(nullptr) {}
public:
    
    BSTree(int val) : value(val), left(nullptr), right(nullptr) {}
    ~BSTree()
    {
        delete left;
        delete right;
    }

    void AddValue(int val)
    {
        if (val == value) return;
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
        while (left != nullptr)
        {
            left->deleteTree();
            delete left;
            left = nullptr;
        }
        while (right != nullptr)
        {
            right->deleteTree();
            delete right;
            right = nullptr;
        }
    }

    void deleteRight(BSTree*& node, int val)
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
                BSTree* temp = (node->left != nullptr) ? node->left : node->right;
                delete node;
                node = temp;
            }
            else
            {
                BSTree* minNode = node->right;
                while (minNode->left != nullptr)
                    minNode = minNode->left;

                node->value = minNode->value;
                deleteRight(node->right, minNode->value);
            }
        }
    }
    
    void deleteLeft(BSTree*& node, int val)
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
                BSTree* temp = (node->left != nullptr) ? node->left : node->right;
                delete node;
                node = temp;
            }
            else
            {
                BSTree* maxNode = node->left;
                while (maxNode->right != nullptr)
                    maxNode = maxNode->right;

                node->value = maxNode->value;
                deleteLeft(node->left, maxNode->value);
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
    
    /*BSTree* FindParent(int val)
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



    /*BSTree* FindNode(int val) 
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

    
};