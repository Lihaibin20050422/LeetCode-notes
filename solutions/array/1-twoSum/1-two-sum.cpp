/*
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target 的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。
*/

#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};  // 题目保证有解，不会走到这里
    }
};

class Solution_hash {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++) {
            int need = target - nums[i];
            if (hash.find(need) != hash.end()) {
                return {hash[need], i};
            }
            hash[nums[i]] = i;
        }
        return {};
    }
};

void printVec(const vector<int>& v){
    for(int x : v) cout << x << " ";
    cout << endl;
}

int main(){
    Solution      brute;
    Solution_hash hs;

    vector<int> a = {2,7,11,15};
    cout << "暴力 [2,7,11,15],9 : "; printVec(brute.twoSum(a,9));   // 0 1
    cout << "哈希 [2,7,11,15],9 : "; printVec(hs.twoSum(a,9));      // 0 1

    vector<int> b = {3,2,4};
    cout << "暴力 [3,2,4],6     : "; printVec(brute.twoSum(b,6));   // 1 2
    cout << "哈希 [3,2,4],6     : "; printVec(hs.twoSum(b,6));      // 1 2

    vector<int> c = {3,3};
    cout << "暴力 [3,3],6       : "; printVec(brute.twoSum(c,6));   // 0 1
    cout << "哈希 [3,3],6       : "; printVec(hs.twoSum(c,6));      // 0 1

    vector<int> d = {-1,-2,-3,-4,-5};
    cout << "暴力 [-1..-5],-8   : "; printVec(brute.twoSum(d,-8));  // 2 4
    cout << "哈希 [-1..-5],-8   : "; printVec(hs.twoSum(d,-8));     // 2 4

    return 0;
}
