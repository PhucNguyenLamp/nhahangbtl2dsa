#include <bits/stdc++.h>
using namespace std;

bool sortlist(pair<char, int> a, pair<char, int> b)
    {
        return a.second > b.second;
    }
//  Huffman tree node abstract base class
struct Node {
    Node* left; // Left child
    Node* right; // Right child
    char value;    // Value
    int weight;   
    public:
    Node(char value, int weight) {
        this->value = value;
        this->weight = weight;
        this->left = nullptr;
        this->right = nullptr;
    }
    Node(Node* left, Node* right) {
        this->value = '0';
        this->weight = left->weight + right->weight;
        this->left = left;
        this->right = right;
    }
    int getweight() { return weight; }
    char getvalue() { return value; }
    bool isLeaf() { return (left == nullptr) && (right == nullptr);}
    bool isLeafType() { 
        return value != '0';
    }
};

class HuffTree
{
private:
    Node* root; // Tree root
public:
    HuffTree(char &value, int weight) // Leaf constructor
    {
        root = new Node(value, weight);
    }
    // Internal node constructor
    HuffTree(HuffTree *left, HuffTree *right) //nhận vào hufftree
    {
        root = new Node(left->root, right->root);
    }
    ~HuffTree() {}                          // Destructor
    Node* getroot() { return root; }    // Get root
    int getweight() { return root->getweight(); } // Root weight
    bool isLeaf() { return root->isLeafType(); } // Leaf check
    bool getValue() { return root->getvalue(); } // Leaf check
};
// Build a Huffman tree from a collection of frequencies
//rotate left
Node* rotateLeft(Node* subroot){
        Node* newRoot = subroot->right;
        Node* newSubTree = newRoot->left;
        newRoot->left = subroot;
        subroot->right = newSubTree;
        return newRoot;
    }
//rotate right
Node* rotateRight(Node* subroot){
    Node* newRoot = subroot->left;
    Node* newSubTree = newRoot->right;
    newRoot->right = subroot;
    subroot->left = newSubTree;
    return newRoot;
}
// check balance
int getHeightRec(Node* root){
    if (!root){
        return 0;
    }
    return 1 + max(getHeightRec(root->left), getHeightRec(root->right));
}
int getBalance(Node* root){
    if (!root){
        return 0;
    }
    return getHeightRec(root->left) - getHeightRec(root->right);
}
// balancing tree + thêm limit là 3 lần quay
Node* BalancingTree(Node* root, int &time){
        int BalancingNum = getBalance(root);
        if( BalancingNum > 1 && getBalance(root->left) >= 0){ //getBalance(root->left) >= 0
            time++;
            return rotateRight(root);
        }else if (BalancingNum > 1 && getBalance(root->left) < 0){ // getBalance(root->left) < 0
            time++;
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }else if ( BalancingNum < -1 && getBalance(root->right) <= 0){ // getBalance(root->right) <= 0
            time++;
            return rotateLeft(root);
        }else if (BalancingNum < -1 && getBalance(root->right) > 0){ // getBalance(root->right) > 0
            time++;
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        return root;
    }
// balance tree recursively max 3 time // cho time = 0
// check từ root
Node* balanceTree(Node* root, int &time){
        if (!root){
            return nullptr;
        }
        while (getBalance(root)>1||getBalance(root)<-1) {
            root = BalancingTree(root, time);
            if (time == 3) return root;
            }
        root->left = balanceTree(root->left, time);
        root->right = balanceTree(root->right, time);
        return root;
    }

HuffTree *buildHuffvector(vector<HuffTree*> TreeArray, int count)
{
    // queue xep theo thu tu tang dan
    struct compare {
        bool operator()(HuffTree* a, HuffTree* b) {
            // a : 1 -> d : 1 -> A : 1 -> B : 1 -> D : 1 -> c : 2 -> C : 2 -> D : 3
            // if frequency a == frequency b -> a > b
            // if same character -> a > A
            if (a->getweight() == b->getweight()) // bằng nhau
            {
                if (a->isLeaf() && b->isLeaf()) //2 lá
                {
                    // check ascii a > b
                    if (islower(a->isLeaf()) && islower(b->isLeaf())
                    || isupper(a->isLeaf()) && isupper(b->isLeaf())){
                        return a->getValue() > b->getValue(); // đúng là ra sau // lớn là ra sau
                    }
                    // check ascii a > A hay // A nhỏ hơn // A ra sau
                    else {
                        return a->getValue() < b->getValue();
                    }
                }
                else if (a->isLeaf() && !b->isLeaf()) // b ko phải leaf, b ra sau
                {   
                    // cho a ra trước
                    return false;
                }
                else if (!a->isLeaf() && b->isLeaf()) // a ko phải leaf, a ra sau
                {   
                    // cho b ra trước
                    return true;
                }
                else // cả 2 ko phải leaf, thằng chèn ra sau (a)
                {
                    // cho a ra sau
                    return true;
                }
            }
            // frequecy a < frequency b
            return a->getweight() >= b->getweight();
        }
    };

    priority_queue<HuffTree*, vector<HuffTree*>, compare> *forest = new priority_queue<HuffTree*, vector<HuffTree*>, compare>;
    for (int i = 0; i < count; i++)
    {
        forest->push(TreeArray[i]);
    }
    // print the queue
    if (forest->size() == 1) return forest->top(); // cho đáp án = 1
    while (forest->size() > 1)
    {
        HuffTree* temp1 = forest->top(); // Pull first two trees
        forest->pop();
        HuffTree* temp2 = forest->top(); // off the list
        forest->pop();
        HuffTree* temp3 = new HuffTree(temp1, temp2);
        // quay cây ở đây

        forest->push(temp3); // Put the new tree back on the list
    }

    return forest->top(); // Return the final tree
}