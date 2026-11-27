#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
    for(int i = 0; i < n; i++){
        reverse(matrix[i].begin(), matrix[i].end());
    }
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

static void Check(vector<vector<int>> mat, vector<vector<int>> expect, const char *desc) {
    vector<vector<int>> got = mat;
    rotate(got);
    cout << desc << "  " << (got == expect ? "PASS" : "FAIL") << endl;
    if (got != expect) {
        cout << "  期望："; Print(expect); cout << "\n  实际："; Print(got); cout << endl;
    }
}

int main()
{
    Check({{1,2,3},{4,5,6},{7,8,9}},
          {{7,4,1},{8,5,2},{9,6,3}}, "3×3（LC 样例 1）");

    Check({{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}},
          {{15,13,2,5},{14,3,4,1},{12,6,8,9},{16,7,10,11}}, "4×4（LC 样例 2）");

    Check({{1,2},{3,4}}, {{3,1},{4,2}}, "2×2");
    Check({{1}}, {{1}}, "1×1");

    /* 转 4 次应该回到原样 */
    {
        vector<vector<int>> orig = {{1,2,3},{4,5,6},{7,8,9}};
        vector<vector<int>> m = orig;
        for (int t = 0; t < 4; t++) rotate(m);
        cout << "转 4 次回到原样: " << (m == orig ? "PASS" : "FAIL") << endl;
    }

    /* 转 1 次 + 转 3 次 = 不变；转 2 次 = 中心对称 */
    {
        vector<vector<int>> orig = {{1,2,3},{4,5,6},{7,8,9}};
        vector<vector<int>> twice = orig;
        rotate(twice); rotate(twice);
        vector<vector<int>> expect2 = {{9,8,7},{6,5,4},{3,2,1}};
        cout << "转 2 次 = 上下左右都翻转: " << (twice == expect2 ? "PASS" : "FAIL") << endl;
    }
    return 0;
}
