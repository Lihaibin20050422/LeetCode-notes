# 94.inorderTraversal(二叉树的中序遍历)

## 题目
给你二叉树的根节点 root，返回它节点值的 **中序** 遍历。

示例 1:
输入: root = [1,null,2,3]
输出: [1,3,2]

示例 2:
输入: root = []
输出: []

示例 3:
输入: root = [1]
输出: [1]

## 思路

**递归 + 辅助函数传引用**：

中序遍历的顺序是 **左 → 根 → 右**。

但题目要求**返回一个 vector**，而不是打印——所以真正的关键在"**结果存在哪里**"。

做法：写一个辅助函数 `dfs(node, res)`，把结果 vector 以**引用**的方式传进去；
所有递归层共用同一个 vector，边遍历边 `push_back`。

1. 主函数建一个空的 `res`，调用 `dfs(root, res)`，返回 `res`
2. `dfs` 中：递归左子树 → 把当前结点的值加入 `res` → 递归右子树

用一个例子理解：

```
        1
       / \
      2   3
     / \
    4   5

中序: 4 2 5 1 3
```

## 代码
```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        dfs(root, res);
        return res;
    }

    void dfs(TreeNode* node, vector<int>& res){
        if(node == nullptr) return;
        dfs(node->left, res);
        res.push_back(node->val);
        dfs(node->right, res);
    }
};
```

## 复杂度

- 时间：$O(n)$，每个结点访问一次
- 空间：$O(h)$（$h$ 为树高，即递归栈深度），最坏情况（单支树）为 $O(n)$

## 要点

### 1. 那个 `&` 不能省（本题唯一真正的难点）

```cpp
void dfs(TreeNode* node, vector<int> res)    // ❌ 如果传【值】
```

**传值的话**：每层递归都会拿到一个**独立的 vector 副本**，`push_back` 加在副本上，
函数一返回、副本就销毁——**结果全部丢失**。

**所以必须传引用 `vector<int>&`**，让所有递归层共享同一个 vector。

**——而这已经是同一类问题的第三次出现：**

| 场景 | 共享并修改的东西 | 怎么传 |
|---|---|---|
| 用先序序列建二叉树 | 数组下标 `idx` | `int* idx` |
| 线索二叉树线索化 | 前驱指针 `pre` | `ThreadNode** pre` |
| **中序遍历收集结果** | **结果数组 `res`** | **`vector<int>&`** |

> **规律：递归中需要"共享并修改"的东西，必须传指针 / 引用。**
> 传值的话，改的是副本，出了这一层就没了。

### 2. 从"打印"到"返回"——LC 题和 DS 代码的接口差别

这是写 LC 题时最常见的转变：

| | DS 里的写法 | LC 94 |
|---|---|---|
| 输出 | `printf("%d", node->val)` | `res.push_back(node->val)` |
| 接口 | `void InOrder(BiTree T)` | `vector<int> inorderTraversal(root)` |

**算法完全一样，但"结果存在哪里"这个问题，是 DS 代码里没有的。**

### 3. 另一种写法（不如上一种）

```cpp
vector<int> inorderTraversal(TreeNode* root) {
    if(root == nullptr) return {};
    vector<int> res = inorderTraversal(root->left);    // 递归返回左子树的
    res.push_back(root->val);
    vector<int> right = inorderTraversal(root->right);
    res.insert(res.end(), right.begin(), right.end()); // 拼接
    return res;
}
```

看起来不用辅助函数更"自然"，但**每层都在拷贝和拼接 vector，效率差**。

### 4. 迭代版 = DS 里的"中序非递归"

用栈模拟：一路向左入栈 → 出栈访问 → 转右。

把 DS 代码里的 `printf` 换成 `res.push_back` 即可，思路完全一样。

## 相关题目

- 144. 二叉树的前序遍历
- 145. 二叉树的后序遍历
- 102. 二叉树的层序遍历
- 98. 验证二叉搜索树（中序遍历的直接应用）
