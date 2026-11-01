# 81.searchII(搜索旋转排序数组 II)

## 题目
已知存在一个按**非降序**排列的整数数组 nums，它在预先未知的某个下标上进行了旋转。
给你旋转后的数组 nums 和一个整数 target，判断目标值是否存在于数组中：存在返回 `true`，否则 `false`。

**与 33 的唯一区别：nums 可能包含重复元素。**

示例:
输入: nums = [2,5,6,0,0,1,2], target = 0 → true
输入: nums = [2,5,6,0,0,1,2], target = 3 → false

## 思路：33 + 一个"缩两边"的补丁

**33 的核心**：每次二分，"必有一半有序"，在有序的那半里判 target 在不在。

**但 81 有重复 → `nums[left] <= nums[mid]` 可能判断不出哪半有序**，
例如 `[1,0,1,1,1]`：`nums[left] == nums[mid]`，但左边根本不有序。

**补丁**：当 `nums[left] == nums[mid] == nums[right]` 时，**两端一起往中间缩一格**。

### 为什么"缩两边"是安全的（不是猜）

- 前面已经判过 `nums[mid] == target`，走到这里说明 **`nums[mid] != target`**；
- 而条件告诉你 `nums[left] == nums[mid] == nums[right]`；
- **所以 `nums[left]`、`nums[right]` 也一定 `!= target`。**

> **⇒ 两端都不可能是答案，丢掉它们，不会漏。**
> 缩两边不是"试一试"，是"确定这两个不是"之后的安全丢弃。

## 代码
```cpp
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left = 0;
        int right = (int)nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return true;

            if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
                left++;                 // 两端相等且都 != target → 安全丢弃
                right--;
            } else if (nums[left] <= nums[mid]) {          // 左半有序
                if (target >= nums[left] && target < nums[mid]) right = mid - 1;
                else                                            left  = mid + 1;
            } else {                                       // 右半有序
                if (target > nums[mid] && target <= nums[right]) left  = mid + 1;
                else                                             right = mid - 1;
            }
        }
        return false;
    }
};
```

## 复杂度
- 平均：$O(\log n)$
- **最坏：$O(n)$**（全是重复元素时，一次只能缩两个）

## 要点

### 1. 81 vs 33

| | 33 | **81** |
|---|---|---|
| 重复元素 | 无 | **有** |
| "哪半有序" | 一定能判 | **可能判不出** |
| 额外动作 | — | **缩两边** |

> **81 = 33 + 一个"判断失效时"的兜底动作。**

### 2. 为什么最坏是 O(n)
全是相同元素时，`nums[left]==nums[mid]==nums[right]` 永远成立 → 每次只缩 2 个 → 共 O(n) 次。
**（这也是"有重复就退化成线性"的典型例子。）**

### 3. 边界
`nums.size() - 1` 在空数组时无符号下溢（`size_t`），写成 `(int)nums.size() - 1` 更稳。

## 相关题目
- 33. 搜索旋转排序数组（无重复，干净版）
- 154. 寻找旋转排序数组中的最小值 II（有重复）
- 153. 寻找旋转排序数组中的最小值
- 704. 二分查找
