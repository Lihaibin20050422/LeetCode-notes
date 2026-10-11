# 144.preorderTraversal(二叉树的前序遍历)

## 题目
给你二叉树的根节点 root，返回它节点值的 **前序** 遍历。

示例 1:
输入: root = [1,null,2,3]
输出: [1,2,3]

示例 2:
输入: root = []
输出: []

示例 3:
输入: root = [1]
输出: [1]

## 思路

**递归 + 辅助函数传引用**（和 94 完全同一套）：

前序遍历的顺序是 **根 → 左 → 右**。

用辅助函数 `dfs(root, res)`，把结果 vector 以**引用**传入，所有递归层共用同一个 vector，
边遍历边 `push_back`。

1. 空结点 → 返回
2. **先把当前结点值加入 res**（根）
3. 递归左子树
4. 递归右子树

## 代码
```cpp
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        dfs(root, res);
        return res;
    }

    void dfs(TreeNode* root, vector<int>& res){
        if(root == nullptr) return;
        res.push_back(root->val);   // 根
        dfs(root->left, res);       // 左
        dfs(root->right, res);      // 右
    }
};
```

## 复杂度

- 时间：$O(n)$
- 空间：$O(h)$

## 要点

### 1. 三种遍历，只差 `push_back` 那一行的位置

```cpp
// 前序(144)       // 中序(94)        // 后序(145)
push_back(val);    dfs(left);         dfs(left);
dfs(left);         push_back(val);    dfs(right);
dfs(right);        dfs(right);        push_back(val);
```

**同一套骨架，`push_back` 换个位置，就是三种遍历。**

**——所以 94 做完之后，144、145 就是"各挪一行"。**

### 2. 迭代版（本题的 follow-up）

**前序的迭代版用一个栈，有个小技巧：**

```cpp
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> res;
    if(root == nullptr) return res;
    stack<TreeNode*> st;
    st.push(root);
    while(!st.empty()){
        TreeNode* p = st.top(); st.pop();
        res.push_back(p->val);
        if(p->right) st.push(p->right);   // 先压右
        if(p->left)  st.push(p->left);    // 后压左
    }
    return res;
}
```

> **为什么要"先压右、后压左"？**
> 因为栈是**后进先出**——左孩子后入栈，就会**先出栈**，
> 于是访问顺序是"左、右"，正好符合前序。

**（这个"反着压栈"的写法，和 94 的中序非递归（一路向左入栈）不同，前序的更简单。）**

### 3. 为什么中序不能用"同款"方法

前序能做到"压右、压左"，是因为**根先被处理**，处理完就可以自由压两个子结点。

**中序不行**——它必须"先把整个左子树走完"才能访问根，所以要用"一路向左入栈"那套（见 94）。

## 相关题目

- 94. 二叉树的中序遍历
- 145. 二叉树的后序遍历
- 102. 二叉树的层序遍历
