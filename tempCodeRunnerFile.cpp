#include <bits/stdc++.h>
using namespace std;
int leastAfter(vector<int>& nums, int k){
    priority_queue<int, vector<int>, greater<int>> q(nums.begin(), nums.end());
    while (k-->0){
        int res = q.top();
        q.pop();
        q.push(res*2);
    }
    return q.top();
};
int main(){
    vector<int> nums {2, 3, 5, 7};
    int k = 3;
    cout << leastAfter(nums, k);

}
