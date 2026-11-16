#include <iostream>
#include <vector>

using namespace std;


vector<vector<int>> result;
vector<int> path;


void backtrack(int n, int k, int start) {
    // 终止条件：当路径长度等于 k 时，说明找到了一个组合
    if (path.size() == k) {
        result.push_back(path);
        return;
    }

    // 单层搜索 + 剪枝
    for (int i = start; i <= n - (k - path.size()) + 1; i++) {
        path.push_back(i);          // 处理节点
        backtrack(n, k, i + 1);     // 递归
        path.pop_back();            // 回溯，撤销处理的节点
    }
}


vector<vector<int>> combine(int n, int k) {
    result.clear();
    path.clear();
    backtrack(n, k, 1);
    return result;
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

static void Check(int n, int k, vector<vector<int>> expect, const char *desc) {
    vector<vector<int>> got = combine(n, k);
    cout << desc << "  n=" << n << " k=" << k << "  expect=";
    Print(expect);
    cout << "  got=";
    Print(got);
    cout << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check(4, 2, {{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}}, "样例1");
    Check(1, 1, {{1}}, "最小规模");
    Check(5, 1, {{1},{2},{3},{4},{5}}, "k = 1");
    Check(3, 3, {{1,2,3}}, "k = n");
    Check(5, 4, {{1,2,3,4},{1,2,3,5},{1,2,4,5},{1,3,4,5},{2,3,4,5}}, "k = n-1");
    Check(6, 2,
          {{1,2},{1,3},{1,4},{1,5},{1,6},{2,3},{2,4},{2,5},{2,6},
           {3,4},{3,5},{3,6},{4,5},{4,6},{5,6}}, "n=6 k=2（15 个）");
    Check(4, 3, {{1,2,3},{1,2,4},{1,3,4},{2,3,4}}, "剪枝生效的情况");
    return 0;
}
