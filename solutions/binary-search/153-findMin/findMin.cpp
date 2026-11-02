#include <iostream>
#include <vector>
using namespace std;

int findMin(vector<int>& nums) {
    int left = 0;
    int right = (int)nums.size() - 1;
    while (left < right) {          // 答案只在 [left, right] 中，left == right 时即为答案
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right]) {
            left = mid + 1;         // mid 在右半段，最小值在 mid 右边
        } else {
            right = mid;            // mid 可能是最小值，不能丢
        }
    }
    return nums[left];
}

static void Check(vector<int> nums, int expect, const char *desc) {
    int got = findMin(nums);
    cout << desc << "  expect=" << expect << "  got=" << got
         << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check({4, 5, 6, 7, 0, 1, 2}, 0, "样例1（旋转4位）");
    Check({0, 1, 2, 4, 5, 6, 7}, 0, "未旋转");
    Check({1}, 1, "只有一个元素");
    Check({2, 1}, 1, "两个元素（已旋转）");
    Check({1, 2}, 1, "两个元素（未旋转）");
    Check({3, 4, 5, 1, 2}, 1, "最小值在中间");
    Check({5, 1, 2, 3, 4}, 1, "最小值在第二个");
    Check({2, 3, 4, 5, 1}, 1, "最小值在末尾");
    Check({3, 1, 2}, 1, "旋转两位");
    Check({11, 13, 15, 17}, 11, "无旋转且全部大于10");
    return 0;
}
