#include <iostream>
#include <vector>
using namespace std;

void NumArray(vector<int>& nums, vector<int>& Prefix)
{
    int n = nums.size();
    Prefix.resize(n + 1, 0);
    for(int i = 0;i < n;i++){
        Prefix[i+1] = Prefix[i] + nums[i];
    }
}

int sumRange(vector<int>& Prefix, int left, int right)
{
    return Prefix[right+1] - Prefix[left];
}

static void Check(const vector<int>& nums, int l, int r, int expect, const char *desc)
{
    vector<int> data = nums;
    vector<int> pre;
    NumArray(data, pre);
    int got = sumRange(pre, l, r);
    cout << desc << "  [" << l << "," << r << "]  expect=" << expect
         << "  got=" << got << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main()
{
    Check({1,2,3,4,5}, 1, 3, 9, "样例(自己造的)");
    Check({-2,0,3,-5,2,-1}, 0, 2, 1, "LC例1");
    Check({-2,0,3,-5,2,-1}, 2, 5, -1, "LC例2");
    Check({-2,0,3,-5,2,-1}, 0, 5, -3, "整段和");
    Check({1}, 0, 0, 1, "单元素");
    Check({5,5,5}, 0, 2, 15, "全段");
    Check({1,-1,1,-1}, 0, 3, 0, "正负抵消");
    Check({0,0,0}, 1, 1, 0, "全零");
    Check({1,2,3,4,5}, 0, 0, 1, "单点(左端)");
    Check({1,2,3,4,5}, 4, 4, 5, "单点(右端)");

    /* 同一份前缀和，多次查询 */
    {
        vector<int> nums = {1,2,3,4,5};
        vector<int> pre;
        NumArray(nums, pre);
        cout << "多次查询: ";
        int q[3][2] = {{0,4},{1,2},{2,3}};
        for (int i = 0; i < 3; i++) {
            cout << sumRange(pre, q[i][0], q[i][1]) << " ";
        }
        cout << " expect=15 5 7" << endl;
    }
    return 0;
}
