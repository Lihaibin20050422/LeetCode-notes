#include <iostream>
#include <vector>
using namespace std;

int findMin(vector<int>& nums) {
    int left = 0;
    int right = (int)nums.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right]) {
            left = mid + 1;         // mid 在大数段，断崖在右边
        } else if (nums[mid] < nums[right]) {
            right = mid;            // mid 已是候选，不能丢
        } else {
            right--;                // 相等：右端可被 mid 顶替，安全丢弃
        }
    }
    return nums[left];
}

static void Check(const vector<int>& nums, int expect, const char *desc) {
    vector<int> v = nums;
    int got = findMin(v);
    cout << desc << "  expect=" << expect << "  got=" << got
         << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check({2, 2, 2, 0, 2}, 0, "样例1");
    Check({1, 3, 5}, 1, "未旋转");
    Check({3, 3, 1, 3}, 1, "重复包裹最小值");
    Check({10, 1, 10, 10, 10}, 1, "样例2");
    Check({2, 2, 2, 2}, 2, "全相等");
    Check({1}, 1, "单元素");
    Check({3, 1}, 1, "两元素(旋转)");
    Check({1, 3}, 1, "两元素(未旋转)");
    Check({1, 0, 1, 1, 1}, 0, "两边相等中间小");
    Check({3, 3, 3, 1, 3}, 1, "多个重复后接断崖");
    return 0;
}
