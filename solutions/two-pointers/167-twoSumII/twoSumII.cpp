#include <iostream>
#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& numbers, int target) {
    int left = 0;
    int right = numbers.size() - 1;
    while(left < right){
        int sum = numbers[left] + numbers[right];
        if(sum < target){
            left++;
        }
        else if(sum > target){
            right--;
        }
        else if(sum == target){
            return {left + 1, right + 1};
        }
    }
    return {};
}

static void Print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << (i + 1 < v.size() ? "," : "");
    }
    cout << "]";
}

static void Check(vector<int> numbers, int target, vector<int> expect, const char *desc) {
    vector<int> got = twoSum(numbers, target);
    cout << desc << "  target=" << target << "  expect=";
    Print(expect);
    cout << "  got=";
    Print(got);
    cout << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check({2, 7, 11, 15}, 9, {1, 2}, "样例1");
    Check({2, 3, 4}, 6, {1, 3}, "样例2");
    Check({-1, 0}, -1, {1, 2}, "样例3(含负数)");
    Check({1, 2, 3, 4, 4, 9, 56, 90}, 8, {4, 5}, "样例4(重复元素)");
    Check({5, 25, 75}, 100, {2, 3}, "样例5");
    Check({1, 1}, 2, {1, 2}, "两个相同数");
    Check({-3, 3}, 0, {1, 2}, "对称的负数");
    Check({0, 0, 3, 4}, 0, {1, 2}, "目标为 0");
    Check({1, 2}, 3, {1, 2}, "最小规模");
    Check({-10, -8, -2, 1, 2, 5, 6}, 0, {3, 5}, "负数区与正数区配对");
    return 0;
}
