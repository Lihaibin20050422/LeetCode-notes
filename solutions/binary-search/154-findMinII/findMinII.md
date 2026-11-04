# 154. 寻找旋转排序数组中的最小值 II

## 题目

一个按**非降序**排列的数组，在某个下标处被旋转，**元素可能重复**。
返回数组中的最小元素。要求尽量 $O(\log n)$。

## 思路：153 + 一个"相等时缩右端"的补丁

153 的核心是拿 `nums[mid]` 和 `nums[right]` 比：

- `nums[mid] > nums[right]`：mid 在大数段 → `left = mid + 1`
- `nums[mid] < nums[right]`：mid 已进入小数段 → `right = mid`

但有了重复元素，会出现**相等**，这时分不清 mid 在哪一段：

- **`nums[mid] == nums[right]`：`right--`**

### 为什么缩右端是安全的

条件 `nums[mid] == nums[right]` 且 `mid < right`。

- 最小值如果就是 `nums[right]`，那 `nums[mid]` 也是同一个值，**丢掉的不是唯一的解**；
- 最小值如果不在右端，那它一定还在 `[left, right-1]` 里。

**⇒ `nums[right]` 是"可被顶替"的，丢掉它不会漏答案。**

### 但缩左端是错的（实测）

把 `right--` 改成 `left++`，跑三组数据：

```
输入 [1,2,2,2,2]  → 输出 2   （正确答案 1）
输入 [2,2,2,0,2]  → 输出 0   （碰巧对）
输入 [2,5,6,0,0,1,2] → 输出 0（碰巧对）
```

第一组就翻车：**最小值恰好在左端**，而 `left++` 会把它直接扔掉。
右端不同——右端的值已经在 mid 那里出现过一次，丢了不亏。

## 代码

```cpp
int findMin(vector<int>& nums) {
    int left = 0;
    int right = (int)nums.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else if (nums[mid] < nums[right]) {
            right = mid;
        } else {
            right--;              // 相等：右端可被 mid 顶替
        }
    }
    return nums[left];
}
```

## 复杂度

- 平均 $O(\log n)$
- **最坏 $O(n)$**：全是相同元素时，每次只 `right--` 一个，退化成线性

## 要点

### 1. 154 与 81：一个缩一边，一个缩两边

| | 81（找 target） | **154（找最小值）** |
|---|---|---|
| 失效条件 | `nums[left]==nums[mid]==nums[right]` | `nums[mid]==nums[right]` |
| 动作 | **两端都缩**（`left++; right--;`） | **只缩右端**（`right--;`） |
| 理由 | 已证明两端都 `!= target`，都能丢 | 只关心最小值，右端被 mid 顶替 |

> 同样叫"有重复时要缩"，缩哪边、缩几个，**取决于你在找什么**。

### 2. 循环条件仍是 `<`，不是 `<=`

和 153 一样：答案恒在 `[left, right]` 中，`left == right` 时区间只剩一个点，
它就是答案，不必再进循环。用了 `<=` 配 `right = mid` 会死循环。

### 3. 边界

`nums.size() - 1` 是 `size_t`，习惯写成 `(int)nums.size() - 1`。

## 相关题目

- 153. 寻找旋转排序数组中的最小值（无重复，干净版）
- 33. 搜索旋转排序数组
- 81. 搜索旋转排序数组 II（有重复，判断失效时缩两边）
- 704. 二分查找
