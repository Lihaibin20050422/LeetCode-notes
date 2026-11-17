# 46. 全排列

## 题目

给定一个**不含重复数字**的数组 `nums`，返回其所有可能的全排列。

示例：`[1,2,3]` →
`[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]`

## 思路：`used[]` 标记 + 路径长度判断结束

- `path` 记录当前排列；
- `used[i]` 表示 `nums[i]` 是否已经被放进 `path`；
- 每层循环**从 0 开始**，跳过 `used[i] == true` 的；
- `path.size() == n` 时收集答案。

```cpp
for (int i = 0; i < n; i++) {
    if (used[i]) continue;
    used[i] = true;
    path.push_back(nums[i]);
    backtrack(nums);
    path.pop_back();
    used[i] = false;      // ← 撤销
}
```

### 为什么排列**不需要** `start`

组合（77）需要 `start`，是因为"选过的就不能再选，而且顺序无关"。
排列要求**每个元素都用且只用一次，但顺序有关**——所以：

> **每层都要从头（`i = 0`）看一遍，用 `used[]` 排除已经用掉的。**

| | 77 组合 | **46 排列** |
|---|---|---|
| 每层起点 | `start`（只往后看） | **`i = 0`（每次从头）** |
| 去重手段 | `start` 天然递增 | **`used[]` 标记** |
| 是否需要撤销 | 只需要 `pop_back` | **`pop_back` + `used[i] = false`** |

## 代码

```cpp
vector<vector<int>> res;
vector<int> path;
vector<bool> used;

void backtrack(vector<int>& nums){
    if(path.size() == nums.size()){
        res.push_back(path);
        return ;
    }
    for(int i = 0; i < (int)nums.size(); i++){
        if(used[i]) continue;

        used[i] = true;              // 选
        path.push_back(nums[i]);

        backtrack(nums);             // 递归

        path.pop_back();             // 回溯：撤销选择
        used[i] = false;             // 回溯：撤销标记
    }
}
```

## 复杂度

- 时间 $O(n! \times n)$：$n!$ 个排列，每个拷贝 $n$ 个元素
- 空间 $O(n)$：`path` + `used` + 递归栈

## 要点

### 1. 回溯的"两处撤销"，一处都不能少

| 撤销对象 | 语句 | 漏了会怎样 |
|---|---|---|
| 路径 | `path.pop_back()` | 下一个分支拿到脏数据 |
| 标记 | `used[i] = false` | **后面的分支永远用不了这个元素** |

**排列题必须两处都撤。** 78/77 只有路径要撤，46 多了标记。

### 2. 三种模板，到这里就齐了

| | 78 子集 | 77 组合 | **46 排列** |
|---|---|---|---|
| 树形 | 二叉（选/不选） | 多叉 + `start` | **多叉 + `used`** |
| 每层范围 | — | `start..n` | **`0..n-1`** |
| 结束条件 | 到叶子 | `size == k` | **`size == n`** |
| 撤销 | `pop_back` | `pop_back` | **`pop_back` + `used=false`** |

**记住这张表，回溯的骨架就完整了。**

### 3. `path.size() == nums.size()` 作为结束条件

因为排列**必须用完所有元素**。而组合（77）是"选够 k 个就停"——**结束条件的差别，直接决定了树长什么样。**

### 4. 有重复元素怎么办（47 题）

如果数组有重复（如 `[1,1,2]`），直接套这个会出重复排列。需要：

1. **先排序**
2. 加一条同层去重：`if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;`

## 相关题目

- 47. 全排列 II（有重复，排序 + 同层去重）
- 77. 组合（`start` 模板）
- 78. 子集（选/不选模板）
- 39. 组合总和（可重复选）
- 60. 排列序列（第 k 个排列，数学法）
