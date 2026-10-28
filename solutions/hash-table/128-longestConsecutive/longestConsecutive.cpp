#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int longestConsecutive(vector<int>& nums) {
    unordered_set<int> st(nums.begin(),nums.end());
    int maxLen = 0;
    for(int num : st){
        if(!st.count(num - 1)){
            int cur = num;
            int curLen = 1;
            while(st.count(cur + 1)){
                cur++;
                curLen++;
            }
            maxLen = max(maxLen, curLen);
        }
    }
    return maxLen;
}

int main() {
    vector<int> a = {100,4,200,1,3,2};
    cout << "[100,4,200,1,3,2] -> " << longestConsecutive(a) << "  (期望 4)" << endl;

    vector<int> b = {0,3,7,2,5,8,4,6,0,1};
    cout << "[0..8,再0,1]      -> " << longestConsecutive(b) << "  (期望 9)" << endl;

    vector<int> c = {};
    cout << "[]                -> " << longestConsecutive(c) << "  (期望 0)" << endl;

    vector<int> d = {1,2,0,1};
    cout << "[1,2,0,1]         -> " << longestConsecutive(d) << "  (期望 3)" << endl;

    vector<int> e = {-1,0,1,-2};
    cout << "[-1,0,1,-2]       -> " << longestConsecutive(e) << "  (期望 4，含负数)" << endl;

    vector<int> f = {5,5,5};
    cout << "[5,5,5]           -> " << longestConsecutive(f) << "  (期望 1)" << endl;

    return 0;
}
