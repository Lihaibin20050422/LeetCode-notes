#include <iostream>
#include <vector>
using namespace std;

void gameOfLife(vector<vector<int>>& board) {
    int m = board.size();
    if(m == 0){
        return ;
    }
    int n = board[0].size();
    vector<vector<int>> copyBoard = board;
    //周围8个位置的偏移量
    int dirs[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            int livecnt = 0;
            for(int d = 0; d < 8; d++){
                int ni = i + dirs[d][0];
                int nj = j + dirs[d][1];
                if(ni >= 0 && ni < m && nj >= 0 && nj < n){
                    if(copyBoard[ni][nj] == 1){
                        livecnt++;
                    }
                }
            }
            if(copyBoard[i][j] == 1){
                if(livecnt < 2 || livecnt > 3){
                    board[i][j] = 0;
                }
            }else{
                if(livecnt == 3){
                    board[i][j] = 1;
                }
            }
        }
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
    gameOfLife(got);
    cout << desc << "  " << (got == expect ? "PASS" : "FAIL") << endl;
    if (got != expect) {
        cout << "  期望："; Print(expect); cout << "\n  实际："; Print(got); cout << endl;
    }
}

int main()
{
    Check({{0,1,0},{0,0,1},{1,1,1},{0,0,0}},
          {{0,0,0},{1,0,1},{0,1,1},{0,1,0}}, "LC 样例1");

    Check({{1,1},{1,0}}, {{1,1},{1,1}}, "LC 样例2（2×2）");

    Check({{1}}, {{0}}, "单个活细胞（0 邻居 → 死）");
    Check({{0}}, {{0}}, "单个死细胞（不变）");

    Check({{0,1,0},{0,1,0},{0,1,0}},
          {{0,0,0},{1,1,1},{0,0,0}}, "闪烁器（横竖交替）");

    Check({{1,1,1},{1,1,1},{1,1,1}},
          {{1,0,1},{0,0,0},{1,0,1}}, "全活 → 四角存活（各 3 邻居），其余死亡");

    Check({{0,0,0},{0,0,0},{0,0,0}},
          {{0,0,0},{0,0,0},{0,0,0}}, "全死 → 保持全死");

    Check({}, {}, "空棋盘");

    Check({{1,1,0},{1,0,0},{0,0,0}},
          {{1,1,0},{1,1,0},{0,0,0}}, "方块（稳定形态）");

    return 0;
}
