# 47. 全排列 II

## 题目

给定一个**可能含重复数字**的序列，返回所有**不重复**的全排列。

示例：`[1,1,2]` → `[[1,1,2],[1,2,1],[2,1,1]]`

## 思路：46 的骨架 + 排序 + **树层去重**

1. **排序**——让相同的数相邻；
2. **`used[]`**——记录哪些位置已经被放进 `path`（46 的模板）；
3. **去重**：`nums[i] == nums[i-1] && !used[i-1]` → `continue`。

## 关键：为什么是 `!used[i-1]`

```cpp
if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) {
    continue;
}
```

这个条件在区分**两种"相同数字"**：

| `used[i-1]` | 含义 | 处理 |
|---|---|---|
| **`false`** | 上一个相同的数在本层被选过、又撤销了 → **同一层的重复分支** | **跳过** |
| `true` | 上一个相同的数还在 `path` 里 → **它是我上面的祖先** | **允许**（不同层，合法） |

画出来就清楚了：

```
            根
        ├─ 选第1个1  ← used[0]=true
        │     └─ 选第2个1  ← 此时 used[0]=true，允许 → [1,1,2] ✅
        └─ 选第2个1  ← used[0]=false（第1个1已撤销），跳过 ❌
```

- 走**左分支**时，`nums[i-1]` 还在路径里（`used=true`）→ 允许
- 回到**同一层再选第二个 1** 时，`used[0]` 已经撤销成 `false` → 跳过

**这就是"树层去重"：只跳过同一层的重复分支，不跳过不同层的相同值。**

## 代码

```cpp
void backtrack(vector<int>& nums) {
    if (path.size() == nums.size()) {
        res.push_back(path);
        return;
    }
    for (int i = 0; i < (int)nums.size(); i++) {
        if (used[i]) {
            continue;
        }
        // 去重：同一层出现相同的数字，只取第一个
        if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) {
            continue;
        }
        used[i] = true;
        path.push_back(nums[i]);

        backtrack(nums);

        used[i] = false;
        path.pop_back();
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    res.clear();
    path.clear();
    used.assign(nums.size(), false);
    sort(nums.begin(), nums.end());
    backtrack(nums);
    return res;
}
```

## 复杂度

- 时间：$O(n! \times n)$（最坏情况；有重复时实际远小于此）
- 空间 $O(n)$

## 要点

### 1. 40 题和 47 题的去重，是同一套逻辑的两种形态

| | 40 组合总和 II | **47 全排列 II** |
|---|---|---|
| 排序 | 需要 | 需要 |
| 去重条件 | `i > start && c[i] == c[i-1]` | **`i > 0 && n[i] == n[i-1] && !used[i-1]`** |
| 为什么不同 | 没有 `used`，靠 `start` 划层 | 有 `used`，靠它判断"是否同层" |

> **本质都一样：同一层里，相同的值只走第一个分支。**
> 区别只是"怎么判断是不是同一层"——组合用 `i > start`，排列用 `!used[i-1]`。

### 2. 两处撤销，位置和 46 一样

```cpp
used[i] = false;
path.pop_back();
```

**顺序不影响结果，但要成对出现。**

### 3. 如果写成 `used[i-1]`（不加 `!`）会怎样

```cpp
if (i > 0 && nums[i] == nums[i-1] && used[i-1]) continue;   // 错的写法之一
```

这是"树枝去重"——它也能得到正确答案，但**剪枝效率更低**（会走更多重复分支再上层的 `used[i]` 检查里被拦下）。

> **标准写法是 `!used[i-1]`（树层去重）。记这一个就够了。**

### 4. 别忘了 `sort`

**去重的前提是有序**。不排序，相同的数不相邻，`nums[i] == nums[i-1]` 根本比不出来。

## 相关题目

- 46. 全排列（无重复，`used[]` 模板）
- 40. 组合总和 II（树层去重，`i > start` 版）
- 90. 子集 II（同样的去重套路）
- 77. 组合（`start` 模板）
- 78. 子集（选/不选模板）
