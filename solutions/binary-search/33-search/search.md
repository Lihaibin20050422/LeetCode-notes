# 33.search(搜索旋转排序数组)

## 题目
整数数组 nums 按升序排列，数组中的值**互不相同**。给你旋转后的数组 nums 和一个目标值 target：
存在返回下标，否则返回 -1。**必须 $O(\log n)$。**

示例:
输入: nums = [4,5,6,7,0,1,2], target = 0 → 4
输入: nums = [4,5,6,7,0,1,2], target = 3 → -1

## 思路：**每次二分，必有一半是有序的**

直接拿 `nums[mid]` 和 `target` 比是不行的——数组被"转"过，不是全局有序的。
但有一个关键事实：

> **旋转数组做一次二分，`[left, mid]` 和 `[mid, right]` 这两半，必然有一半是完整升序的。**
> 因为"折断点"只可能落在其中一半里。

于是策略就出来了：
1. **先判断哪一半有序**：`nums[left] <= nums[mid]` → 左半 `[left,mid]` 有序；否则右半 `[mid,right]` 有序；
2. **在有序的那一半里，用普通二分判断 target 在不在**；
3. 在 → 收缩到那一半；不在 → 答案只能在另一半。

## 代码
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;   // 防无符号下溢
        while (left <= right) {
            int mid = left + (right - left) / 2;         // 防溢出
            if (nums[mid] == target) return mid;

            if (nums[left] <= nums[mid]) {               // 左半有序
                if (target >= nums[left] && target < nums[mid]) right = mid - 1;
                else                                            left  = mid + 1;
            } else {                                     // 右半有序
                if (target > nums[mid] && target <= nums[right]) left  = mid + 1;
                else                                             right = mid - 1;
            }
        }
        return -1;
    }
};
```

## 复杂度
- 时间：$O(\log n)$
- 空间：$O(1)$

## 要点

### 1. 本质：二分要的不是"有序"，是"能砍一半"

> **二分的本质不是"全局有序"，是"每一步都能排除一半"。**
> 旋转破坏了全局有序，但**局部一定有序**——这就是它还能二分的理由。

### 2. 两个区间判断的边界

| 哪半有序 | `target` 在其中的条件 | 往哪走 |
|---|---|---|
| 左半 `[left, mid]` | `nums[left] <= target < nums[mid]` | `right = mid - 1` |
| 右半 `[mid, right]` | `nums[mid] < target <= nums[right]` | `left = mid + 1` |

> `nums[mid]` 本身不用包含进去——开头已经判过 `nums[mid] == target`。

### 3. 两个防坑细节（你已经做对了）
- `static_cast<int>(nums.size()) - 1` —— 防无符号下溢（704 那个坑）；
- `left + (right - left) / 2` —— 防溢出 mid。

### 4. 下一关：81（允许重复元素）
如果数组**有重复**，`nums[left] <= nums[mid]` 可能判断不出哪半有序（例如 `[1,1,1,3,1]`）——
那时要**先 `left++` 缩一格，再重新判断**。

**33 是"干净版"，81 才是"脏版"。**

## 相关题目
- 81. 搜索旋转排序数组 II（有重复）
- 153. 寻找旋转排序数组中的最小值
- 704. 二分查找
- 34. 查找第一个和最后一个位置
