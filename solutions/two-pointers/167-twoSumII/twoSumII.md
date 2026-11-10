# 167. 两数之和 II - 输入有序数组

## 题目

给定一个**已按非递减顺序排列**的整数数组 `numbers` 和目标值 `target`，找出两个数，使它们之和等于 `target`。
返回这两个数的下标（**从 1 开始**），且同一元素不能重复使用。保证恰好存在一组答案。

示例：`numbers = [2,7,11,15], target = 9` → `[1,2]`

## 思路：有序 → 相向双指针

两个指针放两端：

- `sum < target`：**左指针右移**（换一个更大的数）
- `sum > target`：**右指针左移**（换一个更小的数）
- `sum == target`：返回

### 为什么这样可以"排除"一整行/一整列

这不是猜，是**证明了可以丢**：

> 若 `numbers[left] + numbers[right] < target`，
> 那么 `numbers[left]` 与任何**不超过** `numbers[right]` 的数相加，都只会更小。
> 而右指针左边的所有数都 ≤ `numbers[right]`——
> **所以 `numbers[left]` 不可能和任何人组成答案，直接排除。**

反之，`sum > target` 时，`numbers[right]` 与任何不小于 `numbers[left]` 的数相加都只会更大，同样可以排除。

**每一步排除掉一个元素，所以最多走 n 步。**

## 代码

```cpp
vector<int> twoSum(vector<int>& numbers, int target) {
    int left = 0;
    int right = numbers.size() - 1;
    while(left < right){
        int sum = numbers[left] + numbers[right];
        if(sum < target){
            left++;
        }
        else if(sum > target){
            right--;
        }
        else if(sum == target){
            return {left + 1, right + 1};
        }
    }
    return {};
}
```

## 复杂度

- 时间 $O(n)$：每个元素最多被排除一次
- 空间 $O(1)$

## 要点

### 1. 返回的是 **1 下标**，别忘了 `+1`

这是本题最容易丢分的地方（纯细心问题）。

### 2. 和 1. 两数之和 的对比

| | 1. twoSum | **167. twoSumII** |
|---|---|---|
| 数组有序？ | 无序 | **有序** |
| 做法 | 哈希表 | **相向双指针** |
| 空间 | $O(n)$ | **$O(1)$** |

> **有序性是白送的信息**——用哈希等于把这份信息扔掉了。

### 3. 和 125（验证回文串）的对比

两道题的骨架完全一样，区别只在"**怎么决定移动哪一边**"：

| | 125 | 167 |
|---|---|---|
| 移动依据 | 跳过**非字母数字** | 依据**和的大小** |
| 判断句 | "这个字符要不要管" | "这个和偏大还是偏小" |

> **双指针的核心问题永远只有一个：这一步该动哪边？依据是什么单调性？**

### 4. 溢出的可能

`int sum = numbers[left] + numbers[right];` 本题数据范围小，不会溢出。
但如果数值接近 $2^{31}$，两个正数相加会溢出成负数——那时要用 `long long`，或者比较 `numbers[left] > target - numbers[right]`。

### 5. `numbers.size() - 1`

`size_t` 下溢问题，本题长度 ≥ 2 无影响；写成 `(int)numbers.size() - 1` 更保险。

## 相关题目

- 1. 两数之和（无序版，哈希）
- 15. 三数之和（排序 + 固定一个数 + 双指针 + 去重）
- 11. 盛最多水的容器（相向双指针 + 贪心：移动短的那边）
- 18. 四数之和
- 125. 验证回文串（相向双指针的另一种形态）
