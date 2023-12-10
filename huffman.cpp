// main.h
#include <bits/stdc++.h>
#include <string>
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
void printNSpace(int n);
void printHuffmanCodingTree(Node* node);

class HuffTree
{
public:
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
    char getValue() { return root->getvalue(); } // Leaf check
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
        while (getBalance(root)>1||getBalance(root)< -1) {
            root = BalancingTree(root, time);
            // printHuffmanCodingTree(root);
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
                    if (islower(a->getValue()) && islower(b->getValue())
                    || isupper(a->getValue()) && isupper(b->getValue())){
                        return a->getValue() > b->getValue(); // đúng là ra sau // lớn là ra sau
                    }
                    // check ascii a > A hay // A nhỏ hơn // A ra sau
                    else {
                        return a->getValue() < b->getValue();
                    }
                }
                else if (a->isLeaf() && !b->isLeaf()) // b ko phải leaf, b ra sau
                {   
                    // 
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
                    return false; // ko hieu tai sao
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
        int time = 0;
        HuffTree* temp1 = forest->top(); // Pull first two trees
        forest->pop();
        HuffTree* temp2 = forest->top(); // off the list
        forest->pop();
        HuffTree* temp3 = new HuffTree(temp1, temp2);
        // quay cây ở đây
        temp3->root = balanceTree(temp3->getroot(), time);
        forest->push(temp3); // Put the new tree back on the list
        // printHuffmanCodingTree(temp3->getroot());
    }

    return forest->top(); // Return the final tree
}
void printTree(Node *root){
    if (!root->isLeafType()) {printTree(root->left); }
    cout << root->weight << " " << endl;
    if (!root->isLeafType()) {printTree(root->right); }
}
void printtreeinorder(Node *root){
    if (!root->isLeafType()) {printtreeinorder(root->left);}
    if (root->isLeafType()) cout << root->value << endl;
    if (!root->isLeafType()) cout << root->weight << endl;
    if (!root->isLeafType()) {printtreeinorder(root->right);}
}
string HuffManFind(Node *root, char find, string res){
    //traverse through huffman tree to find the character
    if (root->isLeaf()){
        if (root->value == find){
            return res;
        }
        else return "";
    }
    else {
        string temp = HuffManFind(root->left, find, res + "0");
        if (temp != "") return temp;
        temp = HuffManFind(root->right, find, res + "1");
        if (temp != "") return temp;
        return "";
    }
}
int binToDec(string bin){
    int res = 0;
    for (int i=0; i<bin.length(); i++){
        res = res*2 + (bin[i] - '0');
    }
    return res;
}
void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printHuffmanCodingTree(Node* node){
            int height = getHeightRec(node) ;
            if(node == NULL){
                cout<< "NULL\n";
                return;
            }
            queue<Node*> q;
            q.push(node);
            Node* temp;
            int count = 0;
            int maxNode = 1;
            int level = 0;
            int space = pow(3, height);
            printNSpace(space / 2);
            while(!q.empty()){
                temp = q.front();
                q.pop();
                if(!temp){
                    cout<< " ";
                    q.push(NULL);
                    q.push(NULL);
                }
                else 
                {
                    cout<< temp->value<<", "<<temp->weight;
                    q.push(temp->left);
                    q.push(temp->right);
                }
                printNSpace(space);
                ++ count;
                if(count == maxNode){
                    cout<<endl;
                    count = 0;
                    maxNode *= 2;
                    level++;
                    space /= 2;
                    printNSpace(space / 2);
                }
                if( level == height){
                    return;
                }
            }

        }


int main(){
    vector<pair<char, int>> list;
    string name = "abcdeeeee";
    for (int i = 0; i < name.length(); i++)
    {
        bool found = false;
        for (int j = 0; j < list.size(); j++)
        {
            if (list[j].first == name[i])
            {
                list[j].second++;
                found = true;
                break;
            }
        }
        if (!found) list.push_back(make_pair(name[i], 1));
    }
    // caesar cipher the letter of the list, shift equals to frequency of the letter
    // for example a+2 = c and z+2 = b and Z+2 = B
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].first >= 'a' && list[i].first <= 'z')
        {
            list[i].first += list[i].second;
            if (list[i].first > 'z')
            {
                list[i].first -= 26;
            }
        }
        else if (list[i].first >= 'A' && list[i].first <= 'Z')
        {
            list[i].first += list[i].second;
            if (list[i].first > 'Z')
            {
                list[i].first -= 26;
            }
        }
        else //để cho vui thôi, không có chữ cái nào khác cả
        {
            list[i].first += list[i].second;
        }
    }
    // if there are 2 letters that is the same, combine them into 1
    for (int i = 0; i < list.size(); i++)
    {
        for (int j = i + 1; j < list.size(); j++)
        {
            if (list[i].first == list[j].first)
            {
                list[i].second += list[j].second;
                list.erase(list.begin() + j);
            }
        }
    }
    vector<HuffTree*> TreeArray;
    for (int i = 0; i < list.size(); i++)
    {
        TreeArray.push_back(new HuffTree(list[i].first, list[i].second));
    }
    HuffTree *huffman = buildHuffvector(TreeArray, list.size());
    // traverse the tree to translate list[i].first to huffman code (binary), take 10 first letter
    string newname = "";
    for (int i=0; i<list.size(); i++){
        for (int j=0; j<list[i].second; j++){
            newname += list[i].first;
        }
    }
    string res = "";
    for (int i=0; i<newname.length(); i++){
        res = res + HuffManFind(huffman->getroot(), newname[i], "");
    }
    // take first 10 letter
    res = res.substr(0, 10);
    // translate binary to decimal
    int decimal = binToDec(res);
    // printHuffmanCodingTree(huffman->getroot());
    // res lẻ -> G
    // res chẵn -> S
    // if (decimal % 2 == 1){
    //     cout << "G" << endl;
    // }
    // else cout << "S" << endl;
}