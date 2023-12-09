bool sortlist(pair<char, int> a, pair<char, int> b)
    {
        return a.second > b.second;
    }
//  Huffman tree node abstract base class
template <typename E>
class HuffNode
{
public:
    virtual ~HuffNode() {}     // Base destructor
    virtual int weight() = 0;  // Return frequency
    virtual bool isLeaf() = 0; // Determine type
};

template <typename E> // Leaf node subclass
class LeafNode : public HuffNode<E>
{
private:
    E it;    // Value
    int wgt; // Weight
public:
    LeafNode(const E &val, int freq) // Constructor
    {
        it = val;
        wgt = freq;
    }
    int weight() { return wgt; }
    E val() { return it; }
    bool isLeaf() { return true; }
};

template <typename E> // Internal node subclass
class IntlNode : public HuffNode<E>
{
private:
    HuffNode<E> *lc; // Left child
    HuffNode<E> *rc; // Right child
    int wgt;         // Subtree weight
public:
    IntlNode(HuffNode<E> *l, HuffNode<E> *r)
    {
        wgt = l->weight() + r->weight();
        lc = l;
        rc = r;
    }
    int weight() { return wgt; }
    bool isLeaf() { return false; }
    HuffNode<E> *left() const { return lc; }
    void setLeft(HuffNode<E> *b)
    {
        lc = (HuffNode<E> *)b;
    }
    HuffNode<E> *right() const { return rc; }
    void setRight(HuffNode<E> *b)
    {
        rc = (HuffNode<E> *)b;
    }
};
// HuffTree is a template of two parameters: the element
// type being coded and a comparator for two such elements.
template <typename E>
class HuffTree
{
private:
    HuffNode<E> *Root; // Tree root
public:
    HuffTree(E &val, int freq) // Leaf constructor
    {
        Root = new LeafNode<E>(val, freq);
    }
    // Internal node constructor
    HuffTree(HuffTree<E> *l, HuffTree<E> *r)
    {
        Root = new IntlNode<E>(l->root(), r->root());
    }
    ~HuffTree() {}                          // Destructor
    HuffNode<E> *root() { return Root; }    // Get root
    int weight() { return Root->weight(); } // Root weight
};
// Build a Huffman tree from a collection of frequencies
//rotate left
Node* rotateLeft(Node* subroot){
        Node* newRoot = subroot->pRight;
        Node* newSubTree = newRoot->pLeft;
        newRoot->pLeft = subroot;
        subroot->pRight = newSubTree;
        return newRoot;
    }
//rotate right
Node* rotateRight(Node* subroot){
    Node* newRoot = subroot->pLeft;
    Node* newSubTree = newRoot->pRight;
    newRoot->pRight = subroot;
    subroot->pLeft = newSubTree;
    return newRoot;
}
// check balance
int checkBalance(Node* root){
    if (!root){
        return 0;
    }
    return this->getHeightRec(root->pLeft) - this->getHeightRec(root->pRight);
    /*if (!root) return 0;
    return getHeightRes(root->pLeft) - getHeightRec(root->pRight);*/
}
// balancing tree + thêm limit là 3 lần quay
Node* BalancingTree(Node* root, int &time){
        int BalancingNum = this->getBalance(root);
        if( BalancingNum > 1 && getBalance(root->pLeft) >= 0){ //getBalance(root->pLeft) >= 0
            time++;
            return rotateRight(root);
        }else if (BalancingNum > 1 && getBalance(root->pLeft) < 0){ // getBalance(root->pLeft) < 0
            if (time+2 > 3) {time+=2; return root;} // cộng dư thì ko xoay dc nữa
            root->pLeft = rotateLeft(root->pLeft);
            return rotateRight(root);
        }else if ( BalancingNum < -1 && getBalance(root->pRight) <= 0){ // getBalance(root->pRight) <= 0
            time++;
            return rotateLeft(root);
        }else if (BalancingNum < -1 && getBalance(root->pRight) > 0){ // getBalance(root->pRight) > 0
            if (time+2 > 3) {time+=2; return root;}
            root->pRight = rotateRight(root->pRight);
            return rotateLeft(root);
        }
        return root;
    }
// balance tree recursively max 3 time // cho time = 0
Node* balanceTree(Node* root, int &time){
        if (!root){
            return nullptr;
        }
        if (time > 3){
            return root;
        }
        root = BalancingTree(root, time);
        root->pLeft = balanceTree(root->pLeft, time);
        root->pRight = balanceTree(root->pRight, time);
        return root;
    }

template <typename E>
HuffTree<E> *buildHuffvector(vector<HuffTree<E>*> TreeArray, int count)
{
    // queue xep theo thu tu tang dan
    struct compare {
        bool operator()(HuffTree<E>* a, HuffTree<E>* b) {
            // a : 1 -> d : 1 -> A : 1 -> B : 1 -> D : 1 -> c : 2 -> C : 2 -> D : 3
            // if frequency a == frequency b -> a > b
            // if same character -> a > A
            if (a->weight() == b->weight())
            {
                if (a->root()->isLeaf() && b->root()->isLeaf())
                {
                    // check ascii a > b
                    if (((LeafNode<char>*)(a->root()))->val() >= 'a' && ((LeafNode<char>*)a->root())->val() <= 'z' && ((LeafNode<char>*)b->root())->val() >= 'a' && ((LeafNode<char>*)b->root())->val() <= 'z'
                    || ((LeafNode<char>*)a->root())->val() >= 'A' && ((LeafNode<char>*)a->root())->val() <= 'Z' && ((LeafNode<char>*)b->root())->val() >= 'A' && ((LeafNode<char>*)b->root())->val() <= 'Z'){
                        return ((LeafNode<char>*)(a->root()))->val() > ((LeafNode<char>*)b->root())->val();
                    }
                    // check ascii a > A
                    else {
                        return ((LeafNode<char>*)(a->root()))->val() < ((LeafNode<char>*)b->root())->val();
                    }
                }
                else if (a->root()->isLeaf() && !b->root()->isLeaf())
                {   
                    // cho b ra trước
                    return false;
                }
                else if (!a->root()->isLeaf() && b->root()->isLeaf())
                {   
                    // cho a ra trước
                    return true;
                }
                else // cả 2 
                {
                    // return thằng nào tồn tại lâu hơn
                    // lên trên
                    return true;
                }
            }
            // frequecy a < frequency b
            return a->weight() >= b->weight();
        }
    };

    priority_queue<HuffTree<E>*, vector<HuffTree<E>*>, compare> *forest = new priority_queue<HuffTree<E>*, vector<HuffTree<E>*>, compare>;
    for (int i = 0; i < count; i++)
    {
        forest->push(TreeArray[i]);
    }
    // print the queue
    while (forest->size() > 1)
    {
        HuffTree<E>* temp1 = forest->top(); // Pull first two trees
        forest->pop();
        HuffTree<E>* temp2 = forest->top(); // off the list
        forest->pop();
        HuffTree<E>* temp3 = new HuffTree<E>(temp1, temp2);
        // quay cây ở đây

        forest->push(temp3); // Put the new tree back on the list
    }

    return forest->top(); // Return the final tree
}