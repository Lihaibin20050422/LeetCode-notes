# 590.postorder(N 叉树的后序遍历)

## 题目
给定一个 N 叉树的根节点 root，返回其节点值的**后序遍历**（先所有孩子从左到右，最后根）。

示例:
输入: root = [1,null,3,2,4,null,5,6]
输出: [5,6,3,2,4,1]

## 思路

**迭代 + "逆序法"**：

后序是"孩子（从左到右）→ 根"。直接迭代不好写——因为**根要等所有孩子访问完才能输出**，而栈天生是"先处理根"。

所以反过来做：
1. 按 **"根 → 孩子（从右到左）"** 的顺序遍历（孩子的进栈顺序**正着**放）；
2. 把得到的序列**整体反转** → 正好是"孩子（从左到右）→ 根" = 后序。

## 代码（迭代 + 反转）
```cpp
class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> res;
        if(root == nullptr) return res;
        stack<Node*> st;
        st.push(root);
        while(!st.empty()){
            Node* p = st.top(); st.pop();
            res.push_back(p->val);
            for(int i = 0; i < (int)p->children.size(); i++){
                st.push(p->children[i]);   // 正着压 → 出栈是"从右到左"
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
```

## 代码（递归，最直观）
```cpp
void dfs(Node* root, vector<int>& res){
    if(root == nullptr) return;
    for(Node* c : root->children) dfs(c, res);   // 先所有孩子
    res.push_back(root->val);                    // 最后自己
}
```

## 复杂度
- 时间：$O(n)$
- 空间：$O(n)$（栈 / 递归深度）

## 要点

### 1. 和 589（前序）正好相反

| | 压孩子顺序 | 最后要 reverse 吗 |
|---|---|---|
| **589 前序** | **逆序**压（右→左）| 不用 |
| **590 后序** | **正序**压（左→右）| **要** |

> **口诀：前序反着压，后序压了再反。**

### 2. 为什么后序要绕这一圈
后序的根在**最后**输出，而栈/迭代天生"先处理根"。**先按"根优先"遍历出来，再整体倒过来**，根自然跑到最后。

### 3. `size()` 的符号警告
`int i < children.size()` 会有 `sign-compare` 警告。写 `(int)children.size()`，或用范围 for：`for(Node* c : root->children)`。

## 相关题目
- 589. N 叉树的前序遍历（正好配对）
- 145. 二叉树的后序遍历（同款"根右左 + reverse"）
- 429. N 叉树的层序遍历
