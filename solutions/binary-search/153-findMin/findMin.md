# 153. 寻找旋转排序数组中的最小值

## 题目

一个按**升序**排列、且元素互不相同的数组，在某个未知下标处被旋转（如 `[0,1,2,4,5,6,7]` → `[4,5,6,7,0,1,2]`）。
返回数组中的最小元素。要求 $O(\log n)$。

## 思路：和 `nums[right]` 比，而不是和 `nums[left]` 比

旋转数组的形状是"**两段升序 + 一个断崖**"，最小值就在断崖的右侧起点。

二分时看 `nums[mid]` 落在哪一段：

- **`nums[mid] > nums[right]`**：mid 还在"大数段"，断崖在它右边 → `left = mid + 1`
- **`nums[mid] <= nums[right]`**：mid 已经进入"小数段"（包含了最小值），最小值在 mid 或其左边 → `right = mid`

**关键：`right = mid` 而不是 `mid - 1`。** 因为 mid 本身可能就是最小值，不能丢。

### 为什么不能和 `nums[left]` 比

如果写成"`nums[mid] > nums[left]` 就说明 mid 在左段，去右边找"，遇到**未旋转**的数组时：

```
0 1 2 4 5 6 7
```

`nums[mid] > nums[left]` 永远成立（mid 越来越往右），你会一路向右走，最后把真正的最小值 `nums[0]` 丢掉。

**比右端才稳**：右端是"小数段"的锚点。

## 代码

```cpp
int findMin(vector<int>& nums) {
    int left = 0;
    int right = (int)nums.size() - 1;
    while (left < right) {              // 不是 <=
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right]) {
            left = mid + 1;             // mid 出局
        } else {
            right = mid;                // mid 保留
        }
    }
    return nums[left];
}
```

## 复杂度

- 时间 $O(\log n)$：每次区间减半
- 空间 $O(1)$

## 要点

### 1. 什么时候用 `<=`，什么时候用 `<`

二分只有两个模板，**判断依据是你每轮淘汰了谁**：

| | 模板一：闭区间找值 | 模板二：找边界 / 极值 |
|---|---|---|
| 循环条件 | `while (left <= right)` | `while (left < right)` |
| 区间里是什么 | 全部**未检查**的元素 | **答案一定在里面** |
| 循环体 | 必须检查 `nums[mid]`，命中就 `return` | 不 return，退出后取答案 |
| 收缩 | 两边都 `mid ± 1`（mid 出局） | 一边 `right = mid`（**mid 保留**），另一边 `mid ± 1` |
| 典型题 | 704、81 | **153**、69、34 的下界写法 |

一句话：

> **循环体里有 `return` → 用 `<=`（最后一个点还要验）；没有 `return`、退出后再取答案 → 用 `<`。**

### 2. 用了 `<=` 会死循环（实测）

把条件改成 `left <= right`，其余不动，跑 `timeout 3` 得到**退出码 124（超时）**：

当 `left == right` 时，`mid == left == right`：

- `nums[mid] > nums[right]` 变成 `nums[mid] > nums[mid]` → **恒为假**
- 走 `else`：`right = mid` → **right 没变，left 也没变**
- 原地打转，永远出不来

### 3. 通用自检

> **只要有一边写成 `= mid`（保留），另一边必须是 `mid ± 1`（让区间缩小）。**
> **每一轮结束后，区间必须真的变小。**

同理，`left < right` 配上 `left = mid` 也会死循环（剩 2 个元素时 `mid == left`）。

### 4. 边界

`nums.size() - 1` 是 `size_t`，空数组时会下溢成 `4294967295`，习惯上写成 `(int)nums.size() - 1`。

## 相关题目

- 33. 搜索旋转排序数组（无重复，找 target）
- 81. 搜索旋转排序数组 II（有重复，判断失效时"缩两边"）
- **154. 寻找旋转排序数组中的最小值 II**（有重复版：`nums[mid] == nums[right]` 时只能 `right--`）
- 69. x 的平方根（同一个"找边界"模板）
- 34. 在排序数组中查找元素的第一个和最后一个位置（下界/上界）
