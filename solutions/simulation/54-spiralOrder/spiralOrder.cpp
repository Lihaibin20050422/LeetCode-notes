#include <iostream>
#include <vector>
using namespace std;

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> res;
    if(matrix.empty()){
        return res;
    }
    int m = matrix.size();
    int n = matrix[0].size();
    int count = m * n;
    int top = 0;
    int bottom = m - 1;
    int left = 0;
    int right = n - 1;
    while(count > 0){
        //左->右
        for(int i = left; i <= right && count > 0; i++){
            res.push_back(matrix[top][i]);
            count--;
        }
        top++;
        //上->下
        for(int i = top; i <= bottom && count > 0; i++){
            res.push_back(matrix[i][right]);
            count--;
        }
        right--;
        //右->左
        for(int i = right; i >= left && count > 0; i--){
            res.push_back(matrix[bottom][i]);
            count--;
        }
        bottom--;
        //下->上
        for(int i = bottom; i >= top && count > 0; i--){
            res.push_back(matrix[i][left]);
            count--;
        }
        left++;
    }
    return res;
}

static void Print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << (i + 1 < v.size() ? "," : "");
    }
    cout << "]";
}

static void Check(vector<vector<int>> mat, vector<int> expect, const char *desc) {
    vector<int> got = spiralOrder(mat);
    cout << desc << "  expect=";
    Print(expect);
    cout << "  got=";
    Print(got);
    cout << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main()
{
    Check({{1,2,3},{4,5,6},{7,8,9}},
          {1,2,3,6,9,8,7,4,5}, "样例（3×3）");

    Check({{1,2,3,4},{5,6,7,8},{9,10,11,12}},
          {1,2,3,4,8,12,11,10,9,5,6,7}, "3×4（行多）");

    Check({{1,2,3},{4,5,6},{7,8,9},{10,11,12}},
          {1,2,3,6,9,12,11,10,7,4,5,8}, "4×3（列多）");

    Check({{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}},
          {1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10}, "4×4（偶数阶）");

    Check({{1,2,3}}, {1,2,3}, "只有一行");
    Check({{1},{2},{3}}, {1,2,3}, "只有一列");
    Check({{1}}, {1}, "单元素");
    Check({}, {}, "空矩阵");
    Check({{1,2},{3,4}}, {1,2,4,3}, "2×2");
    Check({{1,2,3,4,5}}, {1,2,3,4,5}, "1×5");

    return 0;
}
