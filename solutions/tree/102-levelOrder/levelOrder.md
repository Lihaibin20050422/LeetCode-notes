# 102.levelOrder(二叉树的层序遍历)

## 题目
给你二叉树的根节点 root，返回其节点值的 **层序遍历**（即逐层地，从左到右访问所有节点）。

示例 1:
输入: root = [3,9,20,null,null,15,7]
输出: [[3],[9,20],[15,7]]

示例 2:
输入: root = []
输出: []

示例 3:
输入: root = [1]
输出: [[1]]

## 思路

**BFS + 队列**。

层序遍历 = 一行一行地访问。用队列从上到下、从左到右依次出队入队即可。
**唯一的难点是：怎么知道"一层"到哪里结束？**

**关键技巧：每轮循环一开始，先记下 `int levelSize = q.size();`**
此刻队列里正好装着"当前这一层的全部结点"（上一层的孩子还没进来）。这次只出队 `levelSize` 个，本层就恰好处理完，同时把下一层的孩子依次压入队列。

1. 根入队
2. while 队列不空：
   - a. `levelSize = q.size()` ← **冻结本层结点数**
   - b. 循环 `levelSize` 次：出队一个结点，值存进 `level`；左右孩子非空就入队
   - c. 把 `level` 收进 `res`

## 代码
```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(root == nullptr) return res;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int levelSize = q.size();   // 关键：先冻结本层结点数
            vector<int> level;
            for(int i = 0; i < levelSize; i++){
                TreeNode* cur = q.front(); q.pop();
                level.push_back(cur->val);
                if(cur->left)  q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            res.push_back(level);
        }
        return res;
    }
};
```

## 复杂度

- 时间：$O(n)$，每个结点入队、出队各一次
- 空间：$O(n)$，队列最坏存一整层（宽树可达 $n/2$），加上返回的结果

## 要点

### 1. `levelSize = q.size()` —— 这题唯一的难点

不记录它，你就不知道当前层什么时候结束。

**必须在 for 之前记**：因为 for 里会不停往队列后面压孩子，`q.size()` 是**一直变**的，不能拿它当循环条件。

### 2. 另一种写法：哨兵 `nullptr`

每层结束时往队列压一个 `nullptr` 当分隔符，遇到 `nullptr` 就"换行"（本层结束）。也能做，但比 `levelSize` 略繁、更容易写错。

### 3. 和 DFS 的关系

**层序 = BFS（队列）**；前/中/后序 = DFS（栈 / 递归）。
四种遍历里，**只有层序用队列**。

## 相关题目

- 107. 二叉树的层序遍历 II（自底向上：把 `res` 整体 `reverse` 即可）
- 199. 二叉树的右视图（每层只取最后一个）
- 103. 锯齿形层序遍历（偶数层把 `level` 反转）
