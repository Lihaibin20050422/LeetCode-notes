#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int subarraySum(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
    unordered_map<int, int> hash;
    hash[prefix[0]] = 1;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int target = prefix[i] - k;
        if (hash.find(target) != hash.end()) {
            ans += hash[target];
        }
        hash[prefix[i]]++;
    }
    return ans;
}

static void Check(vector<int> nums, int k, int expect, const char *desc) {
    int got = subarraySum(nums, k);
    cout << desc << "  k=" << k << "  expect=" << expect
         << "  got=" << got << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check({1,1,1}, 2, 2, "样例1");
    Check({1,2,3}, 3, 2, "样例2");
    Check({0,0,0}, 0, 6, "样例3(全零)");
    Check({1}, 0, 0, "单元素无解");
    Check({1}, 1, 1, "单元素命中");
    Check({-1,-1,1}, 0, 1, "含负数");
    Check({3,4,7,2,-3,1,4,2}, 7, 4, "长样例");
    Check({1,-1,0}, 0, 3, "正负抵消含 0");
    Check({0,0}, 0, 3, "两个零");
    Check({1,2,3}, 100, 0, "k 比总和还大");
    Check({-1,-1,-1}, -2, 2, "k 为负数");
    return 0;
}
