# 1. Two Sum

**难度**：Easy
**标签**：哈希表、数组
**日期**：2026-08-03

## 题目

给定一个整数数组 nums 和一个目标值 target，返回和为 target 的两个数的下标。

## 思路

暴力双层循环 $O(n^2)$。哈希表优化：遍历时检查 target - nums[i] 是否已在哈希表中，$O(n)$。

## 代码

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (mp.count(complement)) {
                return {mp[complement], i};
            }
            mp[nums[i]] = i;
        }
        return {};
    }
};
```

## 复杂度

- 时间：$O(n)$
- 空间：$O(n)$

## 要点

- `unordered_map` 查找 $O(1)$，`map` 是 $O(\log n)$，这里用前者
- 一边遍历一边插入，不用先建完表再查
