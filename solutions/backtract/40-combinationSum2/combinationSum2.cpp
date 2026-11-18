#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> res;
vector<int> path;

void backtrack(vector<int>& candidates, int start, int& sum, int target) {
    if (sum == target) {
        res.push_back(path);
        return;
    }
    for (int i = start; i < (int)candidates.size(); ++i) {
        // 剪枝
        if (sum + candidates[i] > target) {
            break;
        }
        // 去重
        if (i > start && candidates[i] == candidates[i - 1]) {
            continue;
        }
        // 选
        path.push_back(candidates[i]);
        sum += candidates[i];
        // 递归
        backtrack(candidates, i + 1, sum, target);
        // 回溯
        sum -= candidates[i];
        path.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    res.clear();
    path.clear();
    sort(candidates.begin(), candidates.end());
    int sum = 0;
    backtrack(candidates, 0, sum, target);
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

static void Check(vector<int> c, int target, vector<vector<int>> expect, const char *desc) {
    vector<vector<int>> got = combinationSum2(c, target);
    cout << desc << "  target=" << target << "  expect=";
    Print(expect);
    cout << "  got=";
    Print(got);
    cout << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check({10,1,2,7,6,1,5}, 8, {{1,1,6},{1,2,5},{1,7},{2,6}}, "样例1");
    Check({2,5,2,1,2}, 5, {{1,2,2},{5}}, "样例2");
    Check({1,1}, 2, {{1,1}}, "两个相同数");
    Check({1}, 1, {{1}}, "单元素命中");
    Check({1}, 2, {}, "单元素不够");
    Check({1,2,3}, 3, {{1,2},{3}}, "单用与组合");
    Check({1,1,1,1}, 2, {{1,1}}, "多个重复只算一次");
    Check({3,1,3,5,1,1}, 8, {{1,1,1,5},{1,1,3,3},{3,5}}, "多组重复");
    Check({2,2,2}, 4, {{2,2}}, "全相同");
    Check({4,1,1,4,4}, 5, {{1,4}}, "重复元素去重");
    return 0;
}
