// main.h
#include <bits/stdc++.h>
#include <string>
using namespace std;

// restaurant.cpp
// TODO: huffman tree
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

// TODO: nha hang G

// Function to precompute the
// factorial of 1 to N
void calculateFact(int fact[], int N)
{
	fact[0] = 1;
	for (long long int i = 1; i < N; i++) {
		fact[i] = fact[i - 1] * i;
	}
}

// Function to get the value of nCr
int nCr(int fact[], int N, int R)
{
	if (R > N)
		return 0;

	// nCr= fact(n)/(fact(r)*fact(n-r))
	int res = fact[N] / fact[R];
	res /= fact[N - R];

	return res;
}

// Function to count the number of ways
// to rearrange the array to obtain same BST
int countWays(vector<int>& arr, int fact[])
{
	// Store the size of the array
	int N = arr.size();

	// Base case
	if (N <= 2) {
		return 1;
	}

	// Store the elements of the
	// left subtree of BST
	vector<int> leftSubTree;

	// Store the elements of the
	// right subtree of BST
	vector<int> rightSubTree;

	// Store the root node
	int root = arr[0];

	for (int i = 1; i < N; i++) {

		// Push all the elements
		// of the left subtree
		if (arr[i] < root) {
			leftSubTree.push_back(arr[i]);
		}

		// Push all the elements
		// of the right subtree
		else {
			rightSubTree.push_back(arr[i]);
		}
	}

	// Store the size of leftSubTree
	int N1 = leftSubTree.size();

	// Store the size of rightSubTree
	int N2 = rightSubTree.size();

	// Recurrence relation
	int countLeft
		= countWays(leftSubTree, fact);
	int countRight
		= countWays(rightSubTree, fact);

	return nCr(fact, N - 1, N1) * countLeft * countRight;
}

class G
{   
    struct Node{
        int val;
        Node *left;
        Node *right;
        int result; // add later
    public:
        Node() {}
        Node(int val) : val(val), left(nullptr), right(nullptr) {}
        Node(int val, Node *left, Node *right) : val(val), left(left), right(right) {}
        ~Node() {}
    };
    class bst{
        public:
        Node* root;
        queue<int> history;
        public:
        Node* addhelper(Node* root, int value){
        if (!root) return new Node(value);
        if (root->val > value){
            root->left = addhelper(root->left,value);
        } else {
            root->right = addhelper(root->right,value);
        }
        return root;
        }
        int getSize(Node* root){
            //get tree size
            if (!root) return 0;
            return 1 + getSize(root->left) + getSize(root->right);
        }
        void add(int value){
            //TODO
            history.push(value);
            root = addhelper(root, value);
        }
        Node* deletehelper(Node* root, int value){
            if (!root){
                return nullptr;
            }
            if (root->val > value){ //succ
                root->left = deletehelper(root->left,value);
            } else if (root->val < value){
                root->right = deletehelper(root->right,value);
            } else {
                if (!root->left){
                    return root->right;
                } else if (!root->right){
                    return root->left;
                }
                else{
                    Node* succParent = root;
                    Node* succ= root->right;
                    while(succ->left){
                        succParent = succ;
                        succ = succ->left;
                    }
                    if (succParent!=root){
                        succParent->left = succ->right;
                    } else {
                        succParent->right = succ->right;
                    }
                    root->val = succ->val;
                }
            }
            return root;
            }
            void deleteNode(int value){
                //TODO
                root = deletehelper(root, value);
            }
    };

    public:
    vector<bst*> list;
    int maxsize; // để cho vui hihi
    G(int maxsize){
        list = vector<bst*>(maxsize);
        for (int i=0; i<maxsize; i++){
            list[i] = nullptr;
        }
    }
    ~G(){
    }
    void insertG(int result){ //result is a decimal number
        result = result % list.size(); // nhớ +1 
        bst* temp = list[result];
        temp->add(result);
    }
        void preorder(Node* root, vector <int>& res){
            if (!root) return;
            res.push_back(root->val);
            preorder(root->left, res);
            preorder(root->right, res);
        }
    void removeG(){
        // lap lai tat ca khu vuc
        for (int i=0; i<list.size(); i++){
            bst* temp = list[i];
            // chuyen cay thanh mang de xem bao nhieu hoan vi 
            vector<int> res;
            preorder(temp->root, res);
            // xoa hoan vi % maxsize phan tu theo thu tu FIFO
            int N = res.size();
            // Store the factorial up to N
            int fact[N];
            // Precompute the factorial up to N
            calculateFact(fact, N);
            int deletenum = countWays(res, fact);
            // xoa nguoi 
            // them ham get size cho cay
            if (deletenum > temp->getSize(temp->root)){
            	temp = nullptr;
            } else {
            	for (int i = 0; i < deletenum; i++){
            		temp->deleteNode(temp->history.front());
            		temp->history.pop();
            	}
            }
        }
    }
    void printhelper(Node* root){
        printhelper(root->left);
        cout << root->val << " ";
        printhelper(root->right);
    }
    void printG(int number){
        //TODO:
        bst* temp = list[--number]; //index thầy cho là 1 nên phải trừ đi 1 về 0
        if (!temp) return;
        printhelper(temp->root);
    }
};

// TODO: nha hang S
class S { 
    struct Node { //lệnh của từng vùng (một list)
    int id;
    vector<int> list; //trong đây cũng có size
    Node(int id){
        this->id = id; // từ 1->maxsize
    }
    int size() { // số khách
        return list.size();
    }
    void insert(int result){
        list.insert(list.begin(), result); // vào cuối ở đầu
    }
    void remove(){
        if (list.size() == 0) return;
        // result - id
        cout << list[list.size()-1] << "-" << id << endl;
        list.pop_back(); // ra cuối ở cuối
    }
    int findindex(int result){ // vào sớm -> index lớn hơn, vào trễ -> index nhỏ
        for (int i=0; i<list.size(); i++){
            if (list[i] == result){
                return i;
            }
        }
        return -1;
    }
    void removeat(int index){ // xoá ở vị trí
        list.erase(list.begin() + index);
    }
};

    private:
    int maxsize;
    vector<Node*> area; // min heap
    vector<int> history; // index bé hơn là thay đổi sớm hơn
    private:
    // hàm hỗ trợ hàm chính
    void reheapdown(int position){ 
        // bé hơn -> lên đầu heap
        // bằng nhau -> vô trước -> bé hơn -> lên đầu heap
        int leftChild = 2 * position + 1;
        int rightChild = 2 * position + 2;
        int min = position; // min heap
        if (leftChild < area.size()){
            min = (area[leftChild]->size() < area[min]->size()) ? position : leftChild; 
        }
        if(rightChild < area.size()){
            min = (area[rightChild]->size() < area[min]->size()) ? min : rightChild;
        }
        // check neu left child = right child -> min = child duoc thay doi som hon trong history
        if (rightChild < area.size() && area[leftChild]->size() == area[rightChild]->size() && area[leftChild]->size() < area[min]->size()){
            // index left < index right ? index left : index right
            int indexleft;
            int indexright;
            for (int i=0; i<history.size(); i++){
                if (history[i] == area[leftChild]->id){
                    indexleft = i;
                }
                if (history[i] == area[rightChild]->id){
                    indexright = i;
                }
            }
            min = indexleft < indexright ? leftChild : rightChild;
        }
        if(min != position){
            swap(area[min], area[position]);
            reheapdown(min);
        }
    }
    int reheapuphelper(vector<int> history, int id){
        for (int i=0; i<history.size(); i++){
            if (history[i] == id){
                return i;
            }
        }
        return -1;
    }
    void reheapup(int position){
        int parent = (position - 1) / 2;
        while(position > 0 && area[position]->size() < area[parent]->size()
        || (position > 0 && area[position]->size() == area[parent]->size() && 
        reheapuphelper(history, area[position]->id) < reheapuphelper(history, area[parent]->id)
        )){ // check nếu 2 khu vực có số khách bằng nhau thì chọn khu vực có index nhỏ hơn
            swap(area[position], area[parent]);
            position = parent;
            parent = (position - 1) / 2;
        }
    }
    int findindex(int id){ // tìm index của khu vực (id)
        for (int i=0; i<area.size();i++){
            if (area[i]->id == id){
                return i;
            }
        }
        return -1;
    }
    void push(int id){ // thêm node mới vào
        Node* newnode = new Node(id);
        area.push_back(newnode);
        // reheapup(area.size()-1); chưa cần reheapup vì chưa có giá trị gì?
    }
    void remove(int id){ // xoa cai node với mã "id"
        int index = findindex(id);
        if (index == -1) return;
        area[index] = area[area.size() - 1];
        area.pop_back();
        reheapdown(index);
        reheapup(index);
    }
    public:
    S(int maxsize){
        this->maxsize = maxsize;
    }
    // lệnh của nhà hàng
    void insertarea(int result){ //min heap 
        // tìm id
        int ID = (result % maxsize) + 1; //từ 1 -> maxsize
        if (findindex(ID) != -1){ // đã có khu vực này
        // có rồi -> add người vào 
        //TODO: hàm int findindex
        int index = findindex(ID);
        //TODO: hàm Node::insert
        area[index]->insert(result); 
        reheapup(index);
        reheapdown(index);
        }
        else{
        //TODO: hàm S::push 
        push(ID);
        int index = findindex(ID);
        area[index]->insert(result); //reheap?
        reheapup(index);
        reheapdown(index);
        }
        // them vao history
        // check có chưa
        // nếu chưa có add tại 0
        // nếu có -> find vào xoá -> add tại 0
        int index = -1;
        for (int i=0; i<history.size(); i++){
            if (history[i] == ID){
                index = i;
            }
        }
        if (index != -1){ // tìm dc
            history.erase(history.begin() + index);
            history.insert(history.begin(), ID);
        } else { // ko tìm dc
            history.insert(history.begin(), ID); // vào càng sớm càng bé
        }
    }
    void keiteiken(int value){
        // đuổi num khách ở trong num khu vực
        for (int i=0; i<value; i++){
            bool deleted = false;
            int tempindex = area[0]->id;
            for (int j=0; j<value; j++){
                area[i]->remove(); // hàm này có in rồi
                if (area[i]->size() == 0){
                    remove(area[i]->id); // xoá khu vực
                    deleted = true;
                }
            }
            //update history
            // i là khu vực
            // j là khách
            if (deleted){ // nếu bị xoá thì xoá khỏi history
                int index;
                for (int i=0; i<history.size(); i++){
                    if (history[i] == tempindex){
                        index = i;
                    }
                }
                history.erase(history.begin() + index);
            } else { // nếu ko bị xoá thì đưa lên đầu history
                int index;
                for (int i=0; i<history.size(); i++){
                    if (history[i] == tempindex){
                        index = i;
                    }
                }
                history.erase(history.begin() + index);
                history.insert(history.begin(), tempindex);
            }
        }
    }
        void printpreorder(vector<Node*> arr, int size, int index) {
            if (index >= size) {
                return;
            }
            for (int i=0; i<arr[index]->list.size(); i++){
                cout << arr[index]->id << " " << arr[index]->list[i] << endl;
            }
            printpreorder(arr, size, 2 * index + 1);

            printpreorder(arr, size, 2 * index + 2);
        }
    void cleave(int num){
        // traverse preorder
        // in num khác last in first out preorder trong min heap
        // id - result \name
        printpreorder(area, area.size(), 0);
    }
};
class Restaurant
{
    private:
    G* g;
    S* s;
    HuffTree* latesthuff; // hihi
    public:
    Restaurant(int MAXSIZE){
        g = new G(MAXSIZE);
        s = new S(MAXSIZE);
    }
    ~Restaurant(){
    }
    void LAPSE(string name){ // nhớ edit latest huff
        vector<pair<char, int>> list;
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

        latesthuff = huffman; // lưu vào lịch sử có gì dùng hand

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
        // res lẻ -> G
        // res chẵn -> S
        if (decimal % 2 == 1){
            g->insertG(decimal);
        }
        else s->insertarea(decimal);
    }
    void KOKUSEN(){
        g->removeG();
    }
    void KEITEIKEN(int num){
        s->keiteiken(num);
    }
    void HAND(){ // In huffman khách gần nhất in order
        printtreeinorder(latesthuff->getroot());
    }
    void LIMITLESS(int num){
        g->printG(num);
    }
    void CLEAVE(int num){
        s->cleave(num);
    }
};
void simulate(string filename)
{
    ifstream ss(filename);
    int MAXSIZE;
    string str, maxsize, name, num;
    ss >> maxsize;
    MAXSIZE = stoi(maxsize);
    Restaurant *r = new Restaurant(MAXSIZE);
    while (ss >> str)
    {
        if (str == "LAPSE") // LAPSE <NAME>
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
