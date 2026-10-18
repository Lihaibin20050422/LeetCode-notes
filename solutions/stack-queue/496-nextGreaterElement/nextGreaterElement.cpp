#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

/*----------------- 解法一：暴力 O(n·m) -----------------*/
vector<int> nextGreaterElement_brute(vector<int>& nums1, vector<int>& nums2)
{
    vector<int> ans;
    for (int i = 0; i < (int)nums1.size(); ++i)
    {
        int x = nums1[i];
        int idx = 0;
        while (nums2[idx] != x)
        {
            idx++;
        }
        int res = -1;
        for (int j = idx + 1; j < (int)nums2.size(); ++j)
        {
            if (nums2[j] > x)
            {
                res = nums2[j];
                break;
            }
        }
        ans.push_back(res);
    }
    return ans;
}

/*----------------- 解法二：单调栈 O(n+m)（正解）-----------------

  从左到右扫 nums2，维护一个【单调递减栈】：
    栈里装的是"还没遇到下一个更大元素"的数，且从上到下递减。
    新来的 x 只要比栈顶大，栈顶的"下一个更大"就是 x → 记账、弹出（可能连弹多个）。
    每个元素入栈出栈各一次 → O(m)。
---------------------------------------------------------------*/
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2)
{
    unordered_map<int,int> nxt;   // 值 -> 它的下一个更大元素
    stack<int> st;                // 单调递减栈

    for (int x : nums2)
    {
        while (!st.empty() && st.top() < x)
        {
            nxt[st.top()] = x;    // x 就是栈顶的"下一个更大"
            st.pop();
        }
        st.push(x);
    }

    vector<int> ans;
    for (int x : nums1)
    {
        ans.push_back(nxt.count(x) ? nxt[x] : -1);
    }
    return ans;
}

/*------------------------ 测试 ------------------------*/
void printVec(const vector<int>& v)
{
    for (int x : v) cout << x << " ";
    cout << endl;
}

int main()
{
    // 示例：nums1 = [4,1,2], nums2 = [1,3,4,2] → [-1,3,-1]
    vector<int> n1 = {4, 1, 2};
    vector<int> n2 = {1, 3, 4, 2};
    cout << "示例  暴力  : "; printVec(nextGreaterElement_brute(n1, n2));  // -1 3 -1
    cout << "示例  单调栈: "; printVec(nextGreaterElement(n1, n2));        // -1 3 -1

    // 递增：nums2 = [1,2,3,4]
    vector<int> a1 = {2, 4};
    vector<int> a2 = {1, 2, 3, 4};
    cout << "递增  暴力  : "; printVec(nextGreaterElement_brute(a1, a2));  // 3 -1
    cout << "递增  单调栈: "; printVec(nextGreaterElement(a1, a2));        // 3 -1

    // 一路递减，最后来个大数 7
    vector<int> b1 = {1, 3, 5, 2, 4};
    vector<int> b2 = {6, 5, 4, 3, 2, 1, 7};
    cout << "递减  暴力  : "; printVec(nextGreaterElement_brute(b1, b2));  // 7 7 7 7 7
    cout << "递减  单调栈: "; printVec(nextGreaterElement(b1, b2));        // 7 7 7 7 7

    return 0;
}
