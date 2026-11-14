#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> res;
    if (n < 3) {
        return res;
    }

    sort(nums.begin(), nums.end());

    for (int i = 0; i < n - 2; i++) {
        if (nums[i] > 0) {
            break;
        }
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }

        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum == 0) {
                res.push_back({nums[i], nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1]) {
                    left++;
                }
                while (left < right && nums[right] == nums[right - 1]) {
                    right--;
                }
                left++;
                right--;
            }
            else if (sum < 0) {
                left++;
            }
            else {
                right--;
            }
        }
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

static void Check(vector<int> nums, vector<vector<int>> expect, const char *desc) {
    vector<vector<int>> got = threeSum(nums);
    cout << desc << "  expect=";
    Print(expect);
    cout << "  got=";
    Print(got);
    cout << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check({-1, 0, 1, 2, -1, -4}, {{-1,-1,2}, {-1,0,1}}, "样例1");
    Check({0, 1, 1}, {}, "样例2");
    Check({0, 0, 0}, {{0,0,0}}, "样例3");
    Check({}, {}, "空数组");
    Check({1, 2}, {}, "不足三个");
    Check({1, 2, 3}, {}, "全是正数");
    Check({-1, -2, -3}, {}, "全是负数");
    Check({0, 0, 0, 0}, {{0,0,0}}, "多个零只算一次");
    Check({-1, 0, 1, 0}, {{-1,0,1}}, "重复元素去重");
    Check({-2, 0, 1, 1, 2}, {{-2,0,2}, {-2,1,1}}, "两组答案");
    Check({3, 0, -2, -1, 1, 2}, {{-2,-1,3}, {-2,0,2}, {-1,0,1}}, "乱序输入");
    Check({-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6},
          {{-4,-2,6}, {-4,0,4}, {-4,1,3}, {-4,2,2},
           {-2,-2,4}, {-2,0,2}}, "长样例（6 组）");
    return 0;
}
