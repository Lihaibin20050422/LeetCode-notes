#include <iostream>
#include <vector>
using namespace std;

bool carPooling(vector<vector<int>>& trips, int capacity) {
    vector<int> diff(1001, 0);
    for (int i = 0; i < (int)trips.size(); i++) {
        int num = trips[i][0];
        int l = trips[i][1];
        int r = trips[i][2];
        diff[l] += num;
        diff[r] -= num;          // [l, r) 左闭右开：到 r 就下车
    }
    int cur = 0;
    for (int i = 0; i < 1001; i++) {
        cur += diff[i];
        if (cur > capacity) {
            return false;
        }
    }
    return true;
}

static void Check(vector<vector<int>> trips, int capacity, bool expect, const char *desc) {
    bool got = carPooling(trips, capacity);
    cout << desc << "  capacity=" << capacity
         << "  expect=" << (expect ? "true" : "false")
         << "  got=" << (got ? "true" : "false")
         << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check({{2,1,5},{3,3,7}}, 4, false, "LC例1（容量不够）");
    Check({{2,1,5},{3,3,7}}, 5, true,  "LC例1（容量够）");
    Check({{2,1,5},{3,5,7}}, 3, true,  "LC例2（5 号站先下后上）");
    Check({{2,1,5},{3,5,7}}, 2, false, "同上但容量 2");
    Check({{3,2,7},{3,7,9},{8,3,9}}, 11, true, "LC例3");
    Check({{3,2,7},{3,7,9},{8,3,9}}, 10, false, "LC例3（容量差 1）");
    Check({{1,0,1}}, 1, true, "单趟（从 0 站出发）");
    Check({{2,0,1}}, 1, false, "单趟超载");
    Check({{1,999,1000}}, 1, true, "到达终点站 1000");
    Check({{1,0,2},{1,1,2}}, 2, true, "两趟重叠一段");
    return 0;
}
