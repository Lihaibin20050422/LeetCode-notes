# 1. Two Sum（两数之和）

**难度**：Easy ｜ **标签**：数组、哈希表
**首次**：2026-08-06（暴力） ｜ **哈希重做**：2026-10-24

## 题目

给定一个整数数组 `nums` 和一个目标值 `target`，找出数组中和为 `target` 的两个数的下标。
假设每种输入只有一个答案，同一个元素不能使用两次。

示例:
输入: nums = [2,7,11,15], target = 9
输出: [0,1]

## 思路一：暴力 O(n²)

两层循环遍历每一对 `(i, j)`（`j` 从 `i+1` 开始，保证不重复、不用同一个元素）。

## 思路二：哈希表 O(n) ← 正解

遍历到 `nums[i]` 时，先问一句：

> **"我需要的那一半（`target - nums[i]`），以前见过吗？"**

- **见过** → 直接返回 `{它的下标, i}`
- **没见过** → 把 `nums[i]` 和它的下标存进哈希表，继续

一趟扫完就是答案。**用空间换时间：把"回头找"从 O(n) 变成 O(1)。**

## 代码

**暴力**
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};  // 题目保证有解，不会走到这里
    }
};
```

**哈希**
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> mp;      // 值 -> 下标
        for (int i = 0; i < (int)nums.size(); i++) {
            int need = target - nums[i];
            auto it = mp.find(need);
            if (it != mp.end()) {
                return {it->second, i};  // 先查
            }
            mp[nums[i]] = i;             // 后插
        }
        return {};
    }
};
```

## 复杂度

| 写法 | 时间 | 空间 |
|---|---|---|
| 暴力 | $O(n^2)$ | $O(1)$ |
| **哈希** | **$O(n)$** | $O(n)$ |

## 要点

### 1. 「先查后插」—— 本题唯一的陷阱

```cpp
if (mp.find(need) != mp.end()) return ...;   // 先查
mp[nums[i]] = i;                             // 后插
```

**顺序反了会怎样？** 以 `[3,3], target=6` 为例：
- 若先插 `3 -> 0`，再查 `need = 3`，就会命中**自己**，返回 `{0,0}` —— 同一个元素用了两次。

**先查后插**，当前元素就不可能和自己配对。✅

### 2. `unordered_map` 的几个细节

- `find(k)` 返回**迭代器**，`== end()` 表示没找到；
- **`operator[]` 有个坑：查不到会自动插入**。所以别用 `mp[k]` 判断存在，要用 `find` / `count`；
- `find` 之后又用 `[]` 取值，是**查了两遍**。用 `it->second` 一遍就够；
- 变量名别叫 `hash` —— 会和 `std::hash` 撞名（`using namespace std` 时更明显）。

### 3. 考研视角：`unordered_map` 就是「散列表」

它的底层就是 **DS 第 7 章的散列表**（链地址法 / 开放定址 + 装填因子 + 冲突处理）。
**LC 里天天在用的容器，就是课本上那张图。**

### 4. 同一道题，一个半月后的重做

8 月用 $O(n^2)$ 暴力过；10 月用 $O(n)$ 哈希再过一遍。

> 同一道题，两种视角。**这就是"过去的镜子"。**

## 相关题目

- 167. 两数之和 II（**有序数组** → 双指针，$O(1)$ 空间）
- 15. 三数之和（排序 + 双指针）
- 454. 四数相加 II（哈希计数）
- 560. 和为 K 的子数组（前缀和 + 哈希）
