#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> res(n, vector<int>(n));
    int count = n * n;
    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = n - 1;
    int num = 1;
    while (count > 0) {
        // 左->右
        for (int i = left; i <= right && count > 0; i++) {
            res[top][i] = num++;
            count--;
        }
        top++;
        // 上到下
        for (int i = top; i <= bottom && count > 0; i++) {
            res[i][right] = num++;
            count--;
        }
        right--;
        // 右->左
        for (int i = right; i >= left && count > 0; i--) {
            res[bottom][i] = num++;
            count--;
        }
        bottom--;
        // 下->上
        for (int i = bottom; i >= top && count > 0; i--) {
            res[i][left] = num++;
            count--;
        }
        left++;
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
    vector<vector<int>> got = generateMatrix(n);
    cout << desc << "  n=" << n << "  " << (got == expect ? "PASS" : "FAIL") << endl;
    if (got != expect) {
        cout << "  期望："; Print(expect); cout << "\n  实际："; Print(got); cout << endl;
    }
}

/* 通用校验：n×n 里必须恰好出现 1..n² 各一次，且相邻数字在网格上相邻 */
static void Validate(int n) {
    vector<vector<int>> m = generateMatrix(n);
    set<int> s;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            s.insert(m[i][j]);
    bool ok = ((int)s.size() == n * n) && (*s.begin() == 1) && (*s.rbegin() == n * n);

    // 记录每个数字的位置
    vector<int> pr(n * n + 1), pc(n * n + 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            pr[m[i][j]] = i;
            pc[m[i][j]] = j;
        }
    for (int v = 1; v < n * n && ok; v++) {
        int d = abs(pr[v] - pr[v + 1]) + abs(pc[v] - pc[v + 1]);
        if (d != 1) ok = false;      // 相邻数字必须四邻接
    }
    cout << "n=" << n << " 完整性与相邻性: " << (ok ? "PASS" : "FAIL") << endl;
}

int main() {
    Check(1, {{1}}, "n=1");
    Check(2, {{1,2},{4,3}}, "n=2");
    Check(3, {{1,2,3},{8,9,4},{7,6,5}}, "n=3");
    Check(4, {{1,2,3,4},{12,13,14,5},{11,16,15,6},{10,9,8,7}}, "n=4");
    Check(5, {{1,2,3,4,5},{16,17,18,19,6},{15,24,25,20,7},
              {14,23,22,21,8},{13,12,11,10,9}}, "n=5");

    for (int n = 1; n <= 10; n++) Validate(n);
    return 0;
}
