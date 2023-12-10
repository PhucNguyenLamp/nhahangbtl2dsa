#include <bits/stdc++.h>
#include <string>
using namespace std;
// class heap{
//     int *arr;
//     int capacity;
//     int size;
//     public:
//     heap(int capacity){
//         this->capacity = capacity;
//         arr = new int[capacity];
//         size = 0;
//     }
//     int size(){
//         return size;
//     }
//     int peek(){
//         if (size == 0) return -1;
//         return arr[0];
//     }
//     void push(int value){
//         if (size == capacity) return;
//         arr[size] = value;
//         reheapup(size);
//         size++;
//     }
//     void remove(int value){
//         int index = getItem(item);
//         if (index == -1) return;
//         elements[index] = elements[count - 1];
//         count--;
//         reheapDown(index);
//         reheapUp(index);
//     }
//     void reheapup(int position){
//         int parent = (position - 1) / 2; //* Floor
//         while(position > 0 && arr[position] > arr[parent]){
//             swap(arr[position], arr[parent]);
//             position = parent;
//             parent = (position - 1) / 2;
//         }
//     }
//     void reheapdown(int position){
//         int leftChild = 2 * position + 1;
//         int rightChild = 2 * position + 2;
//         int max = position;
//         if ( leftChild < size){
//             max = (arr[leftChild] <= arr[max])? position : leftChild; 
//         }
//         if(rightChild < size){
//             max = (arr[rightChild] <= arr[max])? max : rightChild;
//         }
//         if(max != position){
//             swap(arr[max], arr[position]);
//             reheapDown(arr, size, max);
//         }
//     }
//     bool search(int value){
//         for(int i = 0; i < size; i++){
//             if(arr[i] == value){
//                 return true;
//             }
//         }
//         return false;
//     }
//     int getItem(int item){
//         for (int i=0; i<size;i++){
//             if (arr[i] == item){
//                 return i;
//             }
//         }
//         return -1;
//     }
//     bool pop(){
//         if(size == 0){
//             return false;
//         }
//         arr[0] = arr[size - 1];
//         size--;
//         reheapdown(0);
//         return true;
//     }
//     void clear(){
//         count = 0;
//     }
//     ~heap(){
//         delete[] arr;
//     }
// };
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