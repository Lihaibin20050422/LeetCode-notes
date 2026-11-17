#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<vector<int>> res;
vector<int> path;
vector<bool> used;

void backtrack(vector<int>& nums){
    if(path.size() == nums.size()){
        res.push_back(path);
        return ;
    }
    for(int i = 0; i < (int)nums.size(); i++){
        if(used[i]){
            continue;
        }
        // 选
        used[i] = true;
        path.push_back(nums[i]);
        // 递归
        backtrack(nums);
        // 回溯+撤销选择标记
        path.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    res.clear();
    path.clear();
    used.assign(nums.size(), false);
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
    vector<vector<int>> got = permute(nums);
    cout << desc << "  expect=";
    Print(expect);
    cout << "  got=";
    Print(got);
    cout << (got == expect ? "  PASS" : "  FAIL") << endl;
}

static void CheckCount(vector<int> nums, int expectCount, const char *desc) {
    vector<vector<int>> got = permute(nums);
    set<vector<int>> uniq(got.begin(), got.end());
    bool ok = ((int)got.size() == expectCount) && ((int)uniq.size() == expectCount);
    cout << desc << "  expect个数=" << expectCount << "  got个数=" << got.size()
         << "  去重后=" << uniq.size() << (ok ? "  PASS" : "  FAIL") << endl;
}

int main()
{
    Check({1, 2, 3},
          {{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}}, "样例1");
    Check({1}, {{1}}, "单元素");
    Check({0, 1}, {{0,1},{1,0}}, "两元素");
    Check({-1, 2}, {{-1,2},{2,-1}}, "含负数");
    CheckCount({1, 2, 3, 4}, 24, "四元素（24 个且不重复）");
    CheckCount({1, 2, 3, 4, 5}, 120, "五元素（120 个且不重复）");
    return 0;
}
