#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int majorityElement(vector<int>& nums) {
    unordered_map<int, int> cnt;
    int n = nums.size();
    // 统计每个数字出现次数
    for (int x : nums) {
        cnt[x]++;
    }
    // 遍历哈希表找多数元素
    for (auto& p : cnt) {
        if (p.second > n / 2) {
            return p.first;
        }
    }
    return -1;
}

int main() {
    vector<int> a = {2,2,1,1,1,2,2};
    cout << "[2,2,1,1,1,2,2] -> " << majorityElement(a) << "  (期望 2)" << endl;

    vector<int> b = {3};
    cout << "[3]             -> " << majorityElement(b) << "  (期望 3)" << endl;

    vector<int> c = {3,3,4};
    cout << "[3,3,4]         -> " << majorityElement(c) << "  (期望 3)" << endl;

    vector<int> d = {1,1,2,2,2};
    cout << "[1,1,2,2,2]     -> " << majorityElement(d) << "  (期望 2)" << endl;

    vector<int> e = {6,5,5};
    cout << "[6,5,5]         -> " << majorityElement(e) << "  (期望 5)" << endl;

    return 0;
}
