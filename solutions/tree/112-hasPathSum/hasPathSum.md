# 112.hasPathSum(路径总和)

## 题目
给你二叉树的根节点 root 和一个表示目标和的整数 targetSum。
判断该树中是否存在**根节点到叶子节点**的路径，这条路径上所有节点值相加等于目标和 targetSum。
如果存在，返回 true；否则，返回 false。

**叶子节点**是指没有子节点的节点。

示例 1:
输入: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
输出: true

示例 2:
输入: root = [1,2,3], targetSum = 5
输出: false

示例 3:
输入: root = [], targetSum = 0
输出: false

## 思路

**递归（DFS）+ 在叶子处判断**：

从根往下走，一路累计路径和；**只有在"叶子结点"处**，才判断"累计和 == targetSum"。

1. 空结点 → false
2. 累加当前结点的值
3. **是叶子**（左右都空）→ 返回 `sum == targetSum`
4. 不是叶子 → 递归左、右（任一为真即可）

## 代码
```cpp
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        return dfs(root, 0, targetSum);
    }

    bool dfs(TreeNode* node, int sum, int targetSum){
        if(node == nullptr) return false;
        sum += node->val;
        if(node->left == nullptr && node->right == nullptr){
            return sum == targetSum;              // 叶子处才判断
        }
        return dfs(node->left, sum, targetSum)
            || dfs(node->right, sum, targetSum);
    }
};
```

## 复杂度

- 时间：$O(n)$
- 空间：$O(h)$（递归栈深度）

## 要点

### 1. ⚠️ 唯一的坑：**必须在"叶子"处判断**

题目要求的是"**根 → 叶子**"的路径，所以比较**只能在叶子做**。

**如果每一层都比较**（`if(sum == targetSum) return true`），会有两类错：

- 路径**还没走完就相等** → 误判为真
- 结点值有**负数**时，中途相等、但继续走又不相等 → 误判

### 2. 另一种更简洁的写法：把"累加"改成"递减"

**关键：改造参数的含义，而不是加新参数。**

| | 参数含义 | 需要辅助函数吗 |
|---|---|---|
| **累加**（上面那版）| `sum` = **"已经走了多少"** → 要额外记 | ✅ 需要（多一个参数）|
| **递减** | `targetSum` = **"还差多少"** → 参数自己够用 | ❌ 不需要 |

```cpp
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root == nullptr) return false;
        if(root->left == nullptr && root->right == nullptr)
            return root->val == targetSum;        // 叶子：剩余的正好等于自己的值
        return hasPathSum(root->left,  targetSum - root->val)
            || hasPathSum(root->right, targetSum - root->val);
    }
};
```

> **把"已经走了多少"换成"还差多少"，参数就能自洽，递归可以直接调自己。**

**这个小技巧（换个角度定义参数的含义）是可迁移的**——DP、回溯里经常用。

### 3. 这道题的"族"

| 题 | 区别 |
|---|---|
| **112**（本题）| 只问"**有没有**" |
| 113 | 返回**所有**满足的路径 |
| 437 | 不要求从**根**开始 |
| 124 | 求**最大路径和** |

## 相关题目

- 113. 路径总和 II（返回所有路径）
- 437. 路径总和 III
- 124. 二叉树中的最大路径和
- 129. 求根节点到叶节点数字之和
