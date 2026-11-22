#include <iostream>
#include <vector>
using namespace std;

vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
    vector<int> diff(n + 2, 0);
    for (int i = 0; i < (int)bookings.size(); i++) {
        int l = bookings[i][0];
        int r = bookings[i][1];
        int seats = bookings[i][2];
        diff[l] += seats;
        diff[r + 1] -= seats;
    }
    vector<int> ans(n);
    int preSum = 0;
    for (int i = 1; i <= n; i++) {
        preSum += diff[i];
        ans[i - 1] = preSum;
    }
    return ans;
}

static void Print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << (i + 1 < v.size() ? "," : "");
    }
    cout << "]";
}

static void Check(vector<vector<int>> bookings, int n, vector<int> expect, const char *desc) {
    vector<int> got = corpFlightBookings(bookings, n);
    cout << desc << "  n=" << n << "  expect=";
    Print(expect);
    cout << "  got=";
    Print(got);
    cout << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check({{1,2,10},{2,3,20},{2,5,25}}, 5, {10,55,45,25,25}, "LC样例");
    Check({{1,3,5}}, 3, {5,5,5}, "整段覆盖");
    Check({{1,1,7}}, 1, {7}, "单航班");
    Check({{1,1,3},{2,2,4}}, 2, {3,4}, "两个单点");
    Check({}, 4, {0,0,0,0}, "无预订");
    Check({{5,5,9}}, 5, {0,0,0,0,9}, "只在最后一个");
    Check({{1,5,2}}, 5, {2,2,2,2,2}, "覆盖到 n（测试 r+1 越界）");
    Check({{1,4,1},{2,2,10}}, 4, {1,11,1,1}, "叠加");
    return 0;
}
