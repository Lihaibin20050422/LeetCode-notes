#include <iostream>
#include <vector>
using namespace std;

void moveZeroes(vector<int>& nums) {
    int slow = 0;
    for(int fast = 0; fast < nums.size(); fast++){
        if(nums[fast] == 0){
            continue;
        }
        int temp = nums[fast];
        nums[fast] = nums[slow];
        nums[slow] = temp;
        slow++;
    }
}

static void Print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << (i + 1 < v.size() ? "," : "");
    }
    cout << "]";
}

static void Check(vector<int> nums, vector<int> expect, const char *desc) {
    moveZeroes(nums);
    cout << desc << "  expect=";
    Print(expect);
    cout << "  got=";
    Print(nums);
    cout << (nums == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check({0, 1, 0, 3, 12}, {1, 3, 12, 0, 0}, "样例1");
    Check({0},             {0},             "只有一个零");
    Check({1},             {1},             "只有一个非零");
    Check({},              {},              "空数组");
    Check({0, 0, 1},       {1, 0, 0},       "零在前");
    Check({1, 2, 3},       {1, 2, 3},       "没有零");
    Check({0, 0, 0},       {0, 0, 0},       "全是零");
    Check({4, 0, 5, 0, 0, 6}, {4, 5, 6, 0, 0, 0}, "零分散");
    Check({-1, 0, -2},     {-1, -2, 0},     "含负数");
    return 0;
}
