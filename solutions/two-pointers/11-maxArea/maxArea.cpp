#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxArea(vector<int>& height) {
    int left = 0;
    int right = height.size() - 1;
    int maxWater = 0;
    while(left < right){
        int h = min(height[left], height[right]);
        int w = right - left;
        maxWater = max(maxWater, h * w);
        if(height[left] < height[right]){
            left++;
        }else{
            right--;
        }
    }
    return maxWater;
}

static void Check(vector<int> h, int expect, const char *desc) {
    int got = maxArea(h);
    cout << desc << "  expect=" << expect << "  got=" << got
         << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main()
{
    Check({1,8,6,2,5,4,8,3,7}, 49, "样例1");
    Check({1,1},               1,  "样例2");
    Check({4,3,2,1,4},         16, "两端同为最高");
    Check({1,2,1},             2,  "中间高两边低");
    Check({2,3,10,5,7,8,9},    36, "一边极高");
    Check({1,2,3,4,5},         6,  "单调递增");
    Check({5,4,3,2,1},         6,  "单调递减");
    Check({1,2},               1,  "只有两根");
    Check({10000,1,10000},     20000, "大数（检查溢出）");
    Check({2,3,4,5,18,17,6},   17, "样例3");
    return 0;
}
