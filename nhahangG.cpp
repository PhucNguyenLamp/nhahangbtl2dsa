#include <bits/stdc++.h>
#include <string>
using namespace std;
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
class G
{   
    public:
    vector<bst*> list;
    G(int maxsize){
        list = vector<bst*>(maxsize);
        for (int i=0; i<maxsize; i++){
            list[i] = nullptr;
        }
    }
    ~G(){
    }
    void insertS(int result){ //result is a decimal number
        result = result % list.size();
        bst* temp = list[result];
        temp->add(result);
    }
        void preorder(Node* root, vector <int>& res){
            if (!root) return;
            res.push_back(root->val);
            preorder(root->left, res);
            preorder(root->right, res);
        }
    void removeS(){
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
    void printS(int number){
        //TODO:
        bst* temp = list[--number]; //index thầy cho là 1 nên phải trừ đi 1 về 0
        if (!temp) return;
        printhelper(temp->root);
    }
};
