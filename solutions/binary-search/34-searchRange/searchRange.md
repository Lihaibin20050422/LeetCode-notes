# 34.searchRange(在排序数组中查找元素的第一个和最后一个位置)

## 题目
给你一个按照**非递减顺序**排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的**开始位置和结束位置**。
如果数组中不存在目标值，返回 `[-1, -1]`。
**必须实现 $O(\log n)$ 的算法。**

示例:
输入: nums = [5,7,7,8,8,10], target = 8 → [3,4]
输入: nums = [5,7,7,8,8,10], target = 6 → [-1,-1]

## 思路：两次二分——找"下界"和"上界"

**关键：`nums[mid] == target` 时不能直接返回，要"继续往左/右挤"。**

**findLeft（下界）**：找**第一个 `>= target`** 的位置
- `nums[mid] >= target` → 答案在左半（**含 mid**）→ `r = mid - 1`
- 否则 → `l = mid + 1`
- 结束时 `l` 就是下界

**findRight（上界）**：找**最后一个 `<= target`** 的位置
- `nums[mid] <= target` → 答案在右半（**含 mid**）→ `l = mid + 1`
- 否则 → `r = mid - 1`
- 结束时 `r` 就是上界

## 代码
```cpp
class Solution {
public:
    int findLeft(vector<int>& nums, int target) {
        int l = 0, r = (int)nums.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (target <= nums[mid]) r = mid - 1;   // 往左挤
            else                     l = mid + 1;
        }
        return l;                                   // 第一个 >= target
    }

    int findRight(vector<int>& nums, int target) {
        int l = 0, r = (int)nums.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (target >= nums[mid]) l = mid + 1;   // 往右挤
            else                     r = mid - 1;
        }
        return r;                                   // 最后一个 <= target
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int left = findLeft(nums, target);
        int right = findRight(nums, target);
        if (left >= (int)nums.size() || nums[left] != target) return {-1, -1};
        return {left, right};
    }
};
```

## 复杂度
- 时间：$O(\log n)$（两次二分）
- 空间：$O(1)$

## 要点

### 1. ⚠️ 判断顺序：**先判越界，再取 `nums[left]`**（就是你 WA 后改对的那个）

```cpp
if (left >= (int)nums.size() || nums[left] != target)
```

- **`left >= size` 必须写在前面**——`||` 是**短路求值**；
- 反过来写 `nums[left] != target || left >= size`，**前面越界直接崩**。

**这两条顺序不能换。**

### 2. 为什么必须有这个判断

`findLeft` 返回的只是"**第一个 `>= target` 的位置**"，它可能：
- **等于 `size()`**（target 比所有元素都大）→ 越界；
- 指向一个 `!= target` 的元素（target 压根不存在）。

**这两种情况都要返回 `[-1,-1]`。** 少了这一步，就是"答案位置有了，但不是答案"。

### 3. "取等方向"是边界二分的灵魂

| 找什么 | `nums[mid] == target` 时怎么动 | 结束时取谁 |
|---|---|---|
| 第一个 `>= target` | `r = mid - 1`（往左挤）| `l` |
| 最后一个 `<= target` | `l = mid + 1`（往右挤）| `r` |

> **`==` 时往哪边走，决定了你找到的是"第一个"还是"最后一个"。**

### 4. 空数组
`nums.size() - 1` 在空数组时下溢成 `-1`（`size_t` 无符号），循环不跑，然后 `left=0 >= size=0` → `[-1,-1]` ✓。
稳妥写法：`(int)nums.size() - 1`。

## 相关题目
- 704. 二分查找（裸二分）
- 35. 搜索插入位置（就是"下界"）
- 278. 第一个错误的版本（下界）
- 69. x 的平方根
- 33. 搜索旋转排序数组
