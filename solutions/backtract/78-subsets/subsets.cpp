#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> ans;
vector<int> path;

void backtrack(int idx, vector<int>& nums) {
    if (idx == (int)nums.size()) {
        ans.push_back(path);
        return;
    }
    //分支1：不选nums[idx]
    backtrack(idx + 1, nums);
    //分支2：选nums[idx]
    path.push_back(nums[idx]);
    backtrack(idx + 1, nums);
    path.pop_back(); //回溯
}

vector<vector<int>> subsets(vector<int>& nums) {
    ans.clear();
    path.clear();
    backtrack(0, nums);
    return ans;
}

static void Canon(vector<vector<int>>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        sort(v[i].begin(), v[i].end());
    }
    sort(v.begin(), v.end());
}

static void Print(const vector<vector<int>>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << "[";
        for (size_t j = 0; j < v[i].size(); j++) {
            cout << v[i][j] << (j + 1 < v[i].size() ? "," : "");
        }
        cout << "]" << (i + 1 < v.size() ? "," : "");
    }
    cout << "]";
}

static void Check(vector<int> nums, vector<vector<int>> expect, const char *desc) {
    vector<vector<int>> got = subsets(nums);
    Canon(got);
    Canon(expect);
    cout << desc << "  expect=";
    Print(expect);
    cout << "  got=";
    Print(got);
    cout << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check({1, 2, 3},
          {{}, {1}, {2}, {3}, {1,2}, {1,3}, {2,3}, {1,2,3}}, "样例1");
    Check({0}, {{}, {0}}, "单元素");
    Check({}, {{}}, "空数组（只有一个空集）");
    Check({1, 2}, {{}, {1}, {2}, {1,2}}, "两元素");
    Check({5, 6, 7, 8},
          {{}, {5}, {6}, {7}, {8}, {5,6}, {5,7}, {5,8}, {6,7}, {6,8}, {7,8},
           {5,6,7}, {5,6,8}, {5,7,8}, {6,7,8}, {5,6,7,8}}, "四元素（16 个）");
    Check({-1, 0}, {{}, {-1}, {0}, {-1,0}}, "含负数");
    return 0;
}
