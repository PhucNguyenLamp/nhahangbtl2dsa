// main.h
#include <bits/stdc++.h>
#include <string>
using namespace std;

// restaurant.cpp
//  Huffman tree node abstract base class
template <typename E>
class HuffNode
{
public:
    virtual ~HuffNode() {}     // Base destructor
    virtual int weight() = 0; // Return frequency
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
template <typename E>
HuffTree<E> *
buildHuff(HuffTree<E> **TreeArray, int count)
{
    heap<HuffTree<E> *, minTreeComp> *forest =
        new heap<HuffTree<E> *, minTreeComp>(TreeArray,
                                             count, count);
    HuffTree<char> *temp1, *temp2, *temp3 = NULL;
    while (forest->size() > 1)
    {
        temp1 = forest->removefirst(); // Pull first two trees
        temp2 = forest->removefirst(); // off the list
        temp3 = new HuffTree<E>(temp1, temp2);
        forest->insert(temp3); // Put the new tree back on list
        delete temp1;          // Must delete the remnants
        delete temp2;          // of the trees we created
    }
    return temp3;
}


class G
{   
    struct customer{
        string name;
        customer *left;
        customer *right;
        int result; // add later
    public:
        customer() {}
        customer(string name, customer *left, customer *right) : name(name), left(left), right(right) {}
        ~customer() {}
    };
    class bst{

    };
    

};
class S
{   
    struct area {
        int id;
        vector<int> head;
        public:
        area(int id, vector<int> head) : id(id), head(head) {}
    };
    class heap{
        
    };
};
class Restaurant
{
public:

    HuffTree<char> *huffman;
    
    bool sortlist(pair<char, int> a, pair<char, int> b)
    {
        return a.second > b.second;
    }
public:
    Restaurant(){

    };
    ~Restaurant(){

    };
    
    void LAPSE(string name)
    {
        // create a list that have the letter frequency of the name
        vector<pair<char, int>> list;
        for (int i = 0; i < name.length(); i++)
        {
            for (int j = 0; j < list.size(); j++)
            {
                if (list[j].first == name[i])
                {
                    list[j].second++;
                    break;
                }
                list.push_back(make_pair(name[i], 1));
            }
        }
        // sort the list from the highest frequency to the lowest
        sort(list.begin(), list.end(), sortlist);
        // caesar cipher the letter of the list, shift equals to frequency of the letter
        for (int i = 0; i < list.size(); i++)
        {
            list[i].first += list[i].second;
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

        // create a huffman tree (AVL tree) from the list
        
        // result = 10 fist letter the name inside of the huffman tree -> binary code -> decimal

        // add into G or S restaurant

        // choose place
    };
    void KOKUSEN(){

    };
    void KEITEIKEN(int num){

    };
        void printHuffMan(HuffNode<char> *root)
        {
            // print inorder
            if (!root->isLeaf()) {printHuffMan(((IntlNode<char> *)root)->left());}
            if (root->isLeaf()) cout << ((LeafNode<char>*)root)->val() << endl;
            if (!root->isLeaf()) cout << root->weight() << endl;
            if (!root->isLeaf()) {printHuffMan(((IntlNode<char> *)root)->right());}      
        };
    void HAND(){ 
        printHuffMan(huffman->root());
    };
    void LIMITLESS(int num){

    };
    void CLEAVE(int num){

    };
};

void simulate(string filename)
{
    ifstream ss(filename);
    int MAXSIZE;
    string str, maxsize, name, num;
    Restaurant *r = new Restaurant();
    while (ss >> str)
    {
        if (str == "MAXSIZE") // MAXSIZE <NUM>
        {
            ss >> maxsize;
            MAXSIZE = stoi(maxsize);
        }
        else if (str == "LAPSE") // LAPSE <NAME>
        {
            ss >> name;
            r->LAPSE(name);
        }
        else if (str == "KOKUSEN") // KOKUSEN
        {
            ss >> num;
            r->KOKUSEN();
        }
        else if (str == "KEITEIKEN") // KEITEIKEN <NUM>
        {
            r->KEITEIKEN(stoi(num));
        }
        else if (str == "HAND") // HAND
        {
            r->HAND();
        }
        else if (str == "LIMITLESS") // LIMITLESS <NUM>
        {
            r->LIMITLESS(stoi(num));
        }
        else // CLEAVE <NUM>
        {
            ss >> num;
            r->CLEAVE(stoi(num));
        }
    }
}

// main.cpp
int main(int argc, char *argv[])
{
    string fileName = "test.txt";
    simulate(fileName);

    return 0;
}
