# 145.postorderTraversal(二叉树的后序遍历)

## 题目
给你一棵二叉树的根节点 root，返回它节点值的 **后序** 遍历。

示例 1:
输入: root = [1,null,2,3]
输出: [3,2,1]

示例 2:
输入: root = []
输出: []

示例 3:
输入: root = [1]
输出: [1]

## 思路

**递归 + 辅助函数传引用**（和 94、144 同一套）：

后序遍历的顺序是 **左 → 右 → 根**。

用辅助函数 `dfs(root, res)`，结果 vector 以引用传入，所有递归层共用同一个 vector。

1. 空结点 → 返回
2. 递归左子树
3. 递归右子树
4. **最后**把当前结点值加入 res（根）

## 代码
```cpp
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        dfs(root, res);
        return res;
    }

    void dfs(TreeNode* root, vector<int>& res){
        if(root == nullptr) return;
        dfs(root->left, res);       // 左
        dfs(root->right, res);      // 右
        res.push_back(root->val);   // 根
    }
};
```

## 复杂度

- 时间：$O(n)$
- 空间：$O(h)$

## 要点

### 1. 三种遍历，只差 `push_back` 那一行的位置

| 遍历 | `push_back` 放在哪 |
|---|---|
| **前序**（144）| **最前** |
| **中序**（94）| 中间 |
| **后序**（本题）| **最后** |

**——这是理解三种遍历最直观的方式。**

### 2. 迭代版是三种里**最难**的

| 遍历 | 迭代难度 |
|---|---|
| 前序 | ⭐ 容易（先压右、后压左）|
| 中序 | ⭐⭐ 中等（一路向左入栈）|
| **后序** | ⭐⭐⭐ **最难** |

**为什么后序难？** 因为它要求"**左右子树都访问完，才访问根**"——根要**最后**处理，
不能像前序那样"处理完根就自由地压两个子结点"。

**两种常见做法：**

**① 变通法（推荐）**

按"**根 → 右 → 左**"遍历（把前序的压栈顺序反过来），得到的序列再**整体反转**，就是后序：

```cpp
vector<int> postorderTraversal(TreeNode* root) {
    vector<int> res;
    if(root == nullptr) return res;
    stack<TreeNode*> st;
    st.push(root);
    while(!st.empty()){
        TreeNode* p = st.top(); st.pop();
        res.push_back(p->val);
        if(p->left)  st.push(p->left);    // 先压左
        if(p->right) st.push(p->right);   // 后压右
    }
    reverse(res.begin(), res.end());       // 整体反转
    return res;
}
```

**原理**：前序是"根左右"，把压栈顺序反过来得到"根右左"，再整体反转 → "左右根" = 后序 ✓

**② 标记法**：给每个结点记录"右子树是否已访问"，用额外的栈或标记位，代码更繁。

## 相关题目

- 94. 二叉树的中序遍历
- 144. 二叉树的前序遍历
- 102. 二叉树的层序遍历
