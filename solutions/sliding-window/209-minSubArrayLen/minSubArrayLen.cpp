#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int minSubArrayLen(int target, vector<int>& nums) {
    int left = 0;
    int sum = 0;
    int minLen = INT_MAX;
    int n = (int)nums.size();
    for (int right = 0; right < n; right++) {
        sum += nums[right];             // 右指针扩张
        while (sum >= target) {         // 满足就缩，可能连续缩多次
            minLen = min(minLen, right - left + 1);
            sum -= nums[left];          // 先记录长度，再缩左端
            left++;
        }
    }
    return minLen == INT_MAX ? 0 : minLen;
}

static void Check(int target, vector<int> nums, int expect, const char *desc) {
    int got = minSubArrayLen(target, nums);
    cout << desc << "  target=" << target << "  expect=" << expect
         << "  got=" << got << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check(7,  {2, 3, 1, 2, 4, 3},            2, "样例1");
    Check(4,  {1, 4, 4},                      1, "样例2");
    Check(11, {1, 1, 1, 1, 1, 1, 1, 1},       0, "样例3（无解）");
    Check(15, {1, 2, 3, 4, 5},                5, "整段才够");
    Check(11, {1, 2, 3, 4, 5},                3, "末尾一段");
    Check(7,  {1, 2, 3, 4, 5},                2, "中间一段");
    Check(1,  {1},                            1, "单元素命中");
    Check(100,{1, 2, 3},                      0, "和不够");
    Check(3,  {1, 1, 1},                      3, "全都要");
    Check(6,  {10, 2, 3},                     1, "一个数就够");
    Check(5,  {2, 3, 1, 1, 1, 1, 1},          2, "需要连续缩多次");
    Check(3,  {},                             0, "空数组");
    return 0;
}
