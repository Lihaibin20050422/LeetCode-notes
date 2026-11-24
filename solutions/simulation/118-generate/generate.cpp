#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> generate(int numRows) {
    if (numRows == 0) {
        return {};
    }

    vector<vector<int>> res;
    for (int i = 0; i < numRows; i++) {
        // 第i行有i+1个元素，由于首尾都是1，直接全部初始化为1，后续处理中间即可
        vector<int> row(i + 1, 1);
        for (int j = 1; j < i; j++) {
            row[j] = res[i - 1][j - 1] + res[i - 1][j];
        }
        res.push_back(row);
    }
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

static void Check(int n, vector<vector<int>> expect, const char *desc) {
    vector<vector<int>> got = generate(n);
    cout << desc << "  n=" << n << "  expect=";
    Print(expect);
    cout << "  got=";
    Print(got);
    cout << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check(1, {{1}}, "1 行");
    Check(2, {{1},{1,1}}, "2 行");
    Check(5, {{1},{1,1},{1,2,1},{1,3,3,1},{1,4,6,4,1}}, "样例（5 行）");
    Check(0, {}, "0 行");
    Check(6, {{1},{1,1},{1,2,1},{1,3,3,1},{1,4,6,4,1},{1,5,10,10,5,1}}, "6 行");
    Check(7, {{1},{1,1},{1,2,1},{1,3,3,1},{1,4,6,4,1},
              {1,5,10,10,5,1},{1,6,15,20,15,6,1}}, "7 行（对称性）");

    /* 对称性检查：每行首尾为 1，且左右对称 */
    {
        vector<vector<int>> r = generate(10);
        bool ok = true;
        for (size_t i = 0; i < r.size() && ok; i++) {
            if (r[i].front() != 1 || r[i].back() != 1) ok = false;
            for (size_t j = 0; j < r[i].size() / 2; j++) {
                if (r[i][j] != r[i][r[i].size() - 1 - j]) ok = false;
            }
        }
        cout << "10 行的首尾=1 且左右对称: " << (ok ? "PASS" : "FAIL") << endl;
    }
    return 0;
}
