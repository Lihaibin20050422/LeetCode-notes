# 704.search(二分查找)

## 题目
给定一个 **n 个元素有序的（升序）**整型数组 nums 和一个目标值 target，搜索 nums 中的 target：存在返回下标，否则返回 -1。

示例:
输入: nums = [-1,0,3,5,9,12], target = 9 → 4
输入: nums = [-1,0,3,5,9,12], target = 2 → -1

## 思路：闭区间二分

维护**闭区间 `[left, right]`**，每次取中点 `mid`：
- `nums[mid] == target` → 返回 mid；
- `nums[mid] < target` → 答案在右半 → `left = mid + 1`；
- `nums[mid] > target` → 答案在左半 → `right = mid - 1`。

`left > right` 时区间为空 → 没找到。

## 代码
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = (int)nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;   // 防溢出
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) left = mid + 1;
            else                    right = mid - 1;
        }
        return -1;
    }
};
```

## 复杂度
- 时间：$O(\log n)$
- 空间：$O(1)$

## 要点

### 1. `left + (right - left) / 2` —— 防溢出，你写对了 ✅

`(left + right) / 2` 在 left、right 都接近 `INT_MAX` 时会**溢出**；`left + (right-left)/2` 不会。
**这是一个不显然的细节，你直接写对了。**

### 2. 闭区间 vs 左闭右开 —— **别混用**

| 写法 | 循环条件 | 区间 |
|---|---|---|
| **闭区间**（你用的）| `left <= right` | `[left, right]` |
| 左闭右开 | `left < right` | `[left, right)` |

**两套是配套的**：
- 闭区间：`right = mid - 1`；
- 左闭右开：`right = mid`。

**混着写，就是死循环或漏元素。** 你这一版是标准的闭区间，配套正确。

### 3. ⚠️ 一个潜在坑：`nums.size() - 1`

`nums.size()` 是**无符号** `size_t`。**空数组时 `0 - 1` 会下溢成 SIZE_MAX**，
赋给 `int` 一般是 `-1`（碰巧让循环不跑，所以测试能过）——**但这是依赖实现的**。

稳妥写法：
```cpp
int right = (int)nums.size() - 1;
```

### 4. 这题没有"重复元素"问题

数组有重复时，"找到就返回"返回的是**任意一个**。
要找**第一个 / 最后一个**，就得用 **34 的边界二分**——**那才是二分的下一关。**

## 相关题目
- 35. 搜索插入位置（等价于"找第一个 >= target"）
- **34. 查找元素的第一个和最后一个位置**（左右边界，二分的真正难点）
- 69. x 的平方根
- 33. 搜索旋转排序数组
