# 40. 组合总和 II

## 题目

给定一个**可能含重复元素**的数组 `candidates` 和目标数 `target`，找出所有和为 `target` 的组合。
**每个数字在每个组合中只能用一次**，结果中不能有重复组合。

示例：`candidates = [10,1,2,7,6,1,5], target = 8` →
`[[1,1,6],[1,2,5],[1,7],[2,6]]`

## 思路：排序 + 多叉树 + 剪枝 + **树层去重**

四步：

1. **排序**——让相同的数挨在一起，去重和剪枝才有依据；
2. **多叉树**：每层从 `start` 往后选一个；
3. **剪枝**：`sum + c[i] > target` → `break`（后面只会更大）；
4. **去重**：`i > start && c[i] == c[i-1]` → `continue`。

### 关键：去重条件是 `i > start`，不是 `i > 0`

这是全题最容易写错的一行。

| 写法 | 含义 | 结果 |
|---|---|---|
| `i > start` | **同一层**里，相同的数只用第一个 | ✅ 正确 |
| `i > 0` | 整个数组里，相同的数只用第一个 | ❌ 会漏掉 `[1,1,6]` 这种"同一组合内重复用值"的答案 |

**为什么 `i > start` 是对的：**

```
        从 start 这一层开始选
        ├─ 选第 1 个 1  →  递归时 start = 该位置+1，**第二个 1 还能被选**
        └─ 选第 2 个 1  →  和上一支结果完全相同，**跳过**
```

而 `[1,1,6]` 里两个 1 是在**不同层**选的（第二层 `start` 已经往后移了），所以 `i > start` 不会把它们挡住。

> **一句话：去重去的是"同一层的重复分支"，不是"同一组合里的重复数字"。**

### 和 39 题（组合总和）的差别

| | 39 组合总和 | **40 组合总和 II** |
|---|---|---|
| 数组有无重复 | 无 | **有** |
| 每个数能否重复用 | **能** | **不能** |
| 递归传什么 | `i`（原地，还能再选） | **`i + 1`（往后走）** |
| 是否需要去重 | 不需要 | **需要** |

## 代码

```cpp
void backtrack(vector<int>& candidates, int start, int& sum, int target) {
    if (sum == target) {
        res.push_back(path);
        return;
    }
    for (int i = start; i < (int)candidates.size(); ++i) {
        if (sum + candidates[i] > target) {
            break;                          // 剪枝：后面更大，直接结束本层
        }
        if (i > start && candidates[i] == candidates[i - 1]) {
            continue;                       // 树层去重
        }
        path.push_back(candidates[i]);
        sum += candidates[i];

        backtrack(candidates, i + 1, sum, target);

        sum -= candidates[i];
        path.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    res.clear();
    path.clear();
    sort(candidates.begin(), candidates.end());   // 去重和剪枝的前提
    int sum = 0;
    backtrack(candidates, 0, sum, target);
    return res;
}
```

## 复杂度

- 时间：最坏 $O(2^n \times n)$（每个元素选/不选，剪枝后远小于此）
- 空间 $O(n)$：递归栈 + `path`

## 要点

### 1. `break` 和 `continue` 不能互换

| 语句 | 用于 | 理由 |
|---|---|---|
| **`break`** | 剪枝 | 数组已排序，当前数超了，**后面的更大，全都不行** |
| **`continue`** | 去重 | 只跳过**这一个**重复分支，后面的数还得看 |

**写反了：去重用了 `break` 会丢答案，剪枝用了 `continue` 会白跑一堆无效分支。**

### 2. 和 15 三数之和的去重，是同一招但不同场景

| | 15 三数之和 | **40 组合总和 II** |
|---|---|---|
| 去重写法 | `i > 0 && nums[i] == nums[i-1]` | **`i > start && c[i] == c[i-1]`** |
| 场景 | 固定外层循环 | **递归的每一层** |

**区别的根源**：15 题的外层循环只有一个"起点"；而回溯的**每一层**都有一个"起点"（`start`）。所以 15 用 `i > 0`，回溯用 `i > start`。

> **记住这句话：回溯里去重，永远和 `start` 比。**

### 3. 剪枝必须在去重之前

```cpp
if (sum + candidates[i] > target) break;              // 先
if (i > start && candidates[i] == candidates[i-1]) continue;   // 后
```

顺序反了也不影响正确性，但**先剪枝能少做一次比较**，而且逻辑上更清楚：**先判断"这条路还能不能走"，再判断"这条路是不是重复"。**

### 4. 别忘了 `sum` 的两次修改

```cpp
sum += candidates[i];          // 选
backtrack(...);
sum -= candidates[i];          // 撤销
```

`sum` 用引用传递，**和 `path` 一样，选完必须撤。**

## 相关题目

- 39. 组合总和（可重复选，无重复元素）
- 78. 子集 / 90. 子集 II（90 是同样的"树层去重"）
- 47. 全排列 II（去重 + `used[]`）
- 15. 三数之和（固定循环里的去重）
- 216. 组合总和 III（固定 k + 目标和）
