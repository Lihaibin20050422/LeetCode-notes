# 35.searchInsert(搜索插入位置)

## 题目
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
请必须使用时间复杂度为 $O(\log n)$ 的算法。
示例 1:
输入: nums = [1,3,5,6], target = 5
输出: 2
示例 2:
输入: nums = [1,3,5,6], target = 2
输出: 1
示例 3:
输入: nums = [1,3,5,6], target = 7
输出: 4

## 思路

**二分查找（左闭右闭区间）**：在有序数组中，用 `left` 和 `right` 两个指针夹逼，每次取中点 `mid` 和目标值比较，砍掉一半范围，直到 `left > right` 退出。

1. `left = 0`，`right = nums.size()-1`（左闭右闭区间 `[0, n-1]`）
2. 循环条件 `left <= right`（区间里还有元素就继续）
3. `mid = (left+right)/2`，比较 `nums[mid]` 和 `target`：
   - `target <= nums[mid]` → 目标在左半边，`right = mid - 1`
   - `target > nums[mid]` → 目标在右半边，`left = mid + 1`
4. 退出循环时，`left` 就是 `target` 应该插入的位置（第一个 `>= target` 的下标）

用一个例子理解：`nums = [1,3,5,6]`, `target = 2`

```
left=0, right=3, mid=1, nums[1]=3
  target(2) <= 3 → right=0
left=0, right=0, mid=0, nums[0]=1
  target(2) > 1 → left=1
left=1, right=0 → 退出，返回 left=1（2 应该插在下标1，即1和3之间）
```

## 代码
```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size()-1;
        while(left<=right){
            int mid = (left+right)/2;
            if(target<=nums[mid]){
                right = mid-1;
            }else{
                left = mid+1;
            }
        }
        return left;
    }
};
```

## 复杂度

- 时间：$O(\log n)$，每次砍掉一半范围
- 空间：$O(1)$，只用了几个变量

## 要点

- **`left` 和 `right` 是”夹逼分界线”，不是”探测器”**：二分查找不是在”找”某个元素，而是在不断缩小”答案可能存在的区间”，直到夹出答案。
- **`+1` / `-1` 的规则**：`mid` 被检查后就被”定性”了，连同它能代表的半边一起踢出未知区：
  - `nums[mid] < target` → mid 及其左半边都不够格 → `left = mid + 1`
  - `nums[mid] >= target` → mid 够格，但可能不是第一个 → `right = mid - 1`
- **等号归哪边，答案停哪侧**：
  - 本题要”第一个 `>= target` 的位置”，所以等号归左边（`target <= nums[mid]` 走左缩），退出时 `left` 就是答案
- **`mid = (left+right)/2` 的溢出隐患**：当 `left+right` 很大时可能溢出。规范写法是 `mid = left + (right-left)/2`。本题数组不会那么大，但面试问到要知道这个优化点。

## 相关题目

- 704. 二分查找（最基本的二分，找到就 return mid）
- 34. 在排序数组中查找元素的第一个和最后一个位置（本题的进阶，找左右边界）