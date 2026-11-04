#include <iostream>
using namespace std;

int mySqrt(int x) {
    int low = 1;
    int high = x;
    int res = 0;                    // 已验证过的最大可行解，x = 0 时直接返回它
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (mid <= x / mid) {       // 用除法比较，避免 mid * mid 溢出
            res = mid;              // mid 可行，先记下来再往右试
            low = mid + 1;
        } else {
            high = mid - 1;         // mid 太大，往左找
        }
    }
    return res;
}

static void Check(int x, int expect) {
    int got = mySqrt(x);
    cout << "x=" << x << "  expect=" << expect << "  got=" << got
         << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check(0, 0);
    Check(1, 1);
    Check(2, 1);
    Check(3, 1);
    Check(4, 2);
    Check(8, 2);
    Check(9, 3);
    Check(15, 3);
    Check(16, 4);
    Check(2147483647, 46340);
    return 0;
}
