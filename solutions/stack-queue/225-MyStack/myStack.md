# 225.MyStack(用队列实现栈)

## 题目
请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作：
- `void push(int x)` 将元素 x 压入栈顶
- `int pop()` 移除并返回栈顶元素
- `int top()` 返回栈顶元素
- `boolean empty()` 如果栈是空的返回 true，否则返回 false

示例:
输入: ["MyStack","push","push","top","pop","empty"] [[],[1],[2],[],[],[]]
输出: [null,null,null,2,2,false]

## 思路

**两个队列：q1 存数据，q2 当搬运工。**

- `push(x)`：直接 `q1.push(x)`
- `pop() / top()`：栈顶 = **最后入队**的元素。但队列只能从**队头**出，所以要先把栈顶"露出来"：
  1. 把 q1 前面 **n-1 个**元素依次搬到 q2
  2. q1 剩下的唯一元素就是栈顶，取走它（`top` 则取出后再放回）
  3. `swap(q1, q2)`，把数据交还给 q1

## 代码
```cpp
class MyStack {
    queue<int> q1, q2;
public:
    void push(int x) { q1.push(x); }

    int pop() {
        while(q1.size() > 1){          // 前 n-1 个搬到 q2
            q2.push(q1.front());
            q1.pop();
        }
        int res = q1.front();          // 剩下的就是栈顶
        q1.pop();
        swap(q1, q2);                  // 数据交还 q1
        return res;
    }

    int top() {
        while(q1.size() > 1){
            q2.push(q1.front());
            q1.pop();
        }
        int res = q1.front();
        q2.push(res);                  // top 不删除，放回 q2
        q1.pop();
        swap(q1, q2);
        return res;
    }

    bool empty() { return q1.empty(); }
};
```

## 复杂度
- `push`：O(1)
- `pop` / `top`：O(n)（每次要搬 n-1 个）
- 空间：O(n)

## 要点

### 1. 为什么"搬 n-1 个"
栈是 **LIFO**、队列是 **FIFO**。要让最后进来的元素先出，**只能把挡在它前面的 n-1 个先挪走**。

### 2. 另一种写法：单队列旋转
只用一个队列：push 之后，把**新元素前面所有元素**依次出队再入队（转一圈），新元素就跑到队头了。
→ `push` O(n)、`pop` O(1)，正好和上面的取舍反过来。**两种都行，看你想优化哪一边。**

### 3. 和 232 是一对
225 是"队列 → 栈"，232 是"栈 → 队列"。**两题对照看，能把两种结构的差异钉死。**

## 相关题目
- 232. 用栈实现队列（反过来）
- 155. 最小栈
