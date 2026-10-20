# 589.preorder(N 叉树的前序遍历)

## 题目
给定一个 N 叉树的根节点 root，返回其节点值的**前序遍历**。
N 叉树在输入中按层序序列化，每个子节点集合用 null 分隔。

示例:
输入: root = [1,null,3,2,4,null,5,6]
输出: [1,3,5,6,2,4]

## 思路

**迭代 + 栈**：和二叉树前序一个思路，只是"两个孩子"变成了"若干个孩子"。

- 根入栈
- 循环：弹栈顶 p → 输出；
  把 p 的孩子**从右往左**压栈
  （这样最左边的孩子最后入栈、最先出栈 → 出栈顺序就是从左到右）

**为什么逆序压**：栈是后进先出。要"先访问左边的孩子"，就得让左边的孩子**最后进去**。

## 代码（迭代）
```cpp
class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> res;
        if(root == nullptr) return res;
        stack<Node*> st;
        st.push(root);
        while(!st.empty()){
            Node* p = st.top(); st.pop();
            res.push_back(p->val);
            for(int i = (int)p->children.size() - 1; i >= 0; --i){
                st.push(p->children[i]);   // 逆序压，保证从左到右出栈
            }
        }
        return res;
    }
};
```

## 代码（递归）
```cpp
void dfs(Node* root, vector<int>& res){
    if(root == nullptr) return;
    res.push_back(root->val);
    for(Node* c : root->children){
        dfs(c, res);
    }
}
// 调用：vector<int> res; dfs(root, res); return res;
```

## 复杂度
- 时间：$O(n)$
- 空间：$O(n)$（栈 / 递归深度）

## 要点

### 1. 逆序压孩子 —— 本题唯一的细节
```cpp
for(int i = p->children.size() - 1; i >= 0; --i)
```
栈是 LIFO，要"先左后右"，就**从右往左压**。

### 2. 一个小陷阱：`size() - 1` 的无符号下溢
`children.size()` 返回无符号 `size_t`。叶子结点 `size()==0` 时，`size()-1` 会变成 `SIZE_MAX`，赋给 `int` 一般是 `-1`（**碰巧**让循环不执行）。

能跑，但**依赖实现**。稳妥写法：
```cpp
for(int i = (int)p->children.size() - 1; i >= 0; --i)
// 或惯用法
for(int i = p->children.size(); i-- > 0; )
```

### 3. 和二叉树的对应
二叉树前序的"先压右、后压左"（144），推广到 N 叉树就是"**从右往左整个压一遍**"。

## 相关题目
- 590. N 叉树的后序遍历
- 144. 二叉树的前序遍历
- 429. N 叉树的层序遍历
