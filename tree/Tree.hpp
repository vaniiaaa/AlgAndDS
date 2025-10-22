
class BTree
{
    int value;
    BTree *left;
    BTree *right;
    BTree() : value(0), left(nullptr), right(nullptr) {}
public:
    
    BTree(int val) : value(val), left(nullptr), right(nullptr) {}
    ~BTree()
    {
        delete left;
        delete right;
    }

    void AddValue(int val)
    {
        if (val < value)
        {
            if (left == nullptr)
                left = new BTree(val);
            else
                left->AddValue(val);
        }
        else
        {
            if (right == nullptr)
                right = new BTree(val);
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

    void deleteValueRight(int val)
    {
        if (value == val)
        {
            
        }
        
    }

private:
    int GetValue() const { return value; }
    
    BTree* FindParent(int val)
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
    }



    BTree* FindNode(int val) //!!!!
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
    }

    
};