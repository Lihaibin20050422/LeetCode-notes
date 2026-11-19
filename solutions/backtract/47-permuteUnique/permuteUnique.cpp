#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> res;
vector<int> path;
vector<bool> used;

void backtrack(vector<int>& nums) {
    if (path.size() == nums.size()) {
        res.push_back(path);
        return;
    }
    for (int i = 0; i < (int)nums.size(); i++) {
        if (used[i]) {
            continue;
        }
        // 去重
        if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) {
            continue;
        }
        // 选
        used[i] = true;
        path.push_back(nums[i]);
        backtrack(nums);
        //回溯撤销
        used[i] = false;
        path.pop_back();
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    res.clear();
    path.clear();
    used.assign(nums.size(), false);
    sort(nums.begin(), nums.end());
    backtrack(nums);
    return res;
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
    vector<vector<int>> got = permuteUnique(nums);
    cout << desc << "  expect=";
    Print(expect);
    cout << "  got=";
    Print(got);
    cout << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check({1,1,2}, {{1,1,2},{1,2,1},{2,1,1}}, "样例1");
    Check({1,2,3}, {{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}}, "无重复");
    Check({1}, {{1}}, "单元素");
    Check({1,1}, {{1,1}}, "两个相同");
    Check({1,1,1}, {{1,1,1}}, "三个相同");
    Check({2,2,1,1},
          {{1,1,2,2},{1,2,1,2},{1,2,2,1},{2,1,1,2},{2,1,2,1},{2,2,1,1}}, "两组重复");
    Check({3,3,0,3},
          {{0,3,3,3},{3,0,3,3},{3,3,0,3},{3,3,3,0}}, "含 0 的三重重复");
    return 0;
}
