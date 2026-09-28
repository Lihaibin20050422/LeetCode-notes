# 160.getIntersectionNode(相交链表)

## 题目
给你两个单链表的头节点 headA 和 headB，请找出并返回两个单链表相交的起始节点。
如果两个链表不存在相交节点，返回 null。

```
A:        a1 → a2 ↘
                   c1 → c2 → c3
B: b1 → b2 → b3 ↗
```

题目数据保证整个链式结构中不存在环。
注意，函数返回结果后，链表必须保持其原始结构。

示例 1:
输入: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5]
输出: Intersected at '8'

示例 2:
输入: intersectVal = 0, listA = [2,6,4], listB = [1,5]
输出: No intersection

## 思路

**长度对齐法**：

1. 分别遍历两个链表，求出长度 lenA、lenB
2. 让**较长链表的指针先走 |lenA − lenB| 步**
3. 之后两指针同步前进，**第一个地址相同的结点就是相交起始结点**
4. 若两指针都走到 NULL 还没相遇，说明不相交，返回 NULL

**为什么对齐长度之后就能找到？**

两条链表相交后会共用同一段尾部。对齐之后，两指针距离交点**同样远**，
所以会**同时**走到交点。若不对齐，两者步调不一致，就会在交点处错开。

用一个例子理解：`A = [4,1,8,4,5]`, `B = [5,6,1,8,4,5]`

```
lenA = 5, lenB = 6 → B 长，s 先走 1 步

p = 4(A)   s = 6(B)   不等 → 各走一步
p = 1(A)   s = 1(B)   不等（不同结点，只是值相同）→ 各走一步
p = 8(A)   s = 8(B)   相等（同一结点）→ 返回 ✓
```

## 代码
```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* p = headA;
        ListNode* s = headB;
        int lenA = 0, lenB = 0;

        while(p != NULL){ p = p->next; lenA++; }   // ① 求 A 的长度
        while(s != NULL){ s = s->next; lenB++; }   // ② 求 B 的长度

        p = headA;
        s = headB;
        int i = 0;
        if(lenA > lenB){                            // ③ 长的先走差值步
            while(i < lenA - lenB){ p = p->next; i++; }
        }else{
            while(i < lenB - lenA){ s = s->next; i++; }
        }

        while(p != NULL && s != NULL){              // ④ 同步前进找交点
            if(p == s) return p;
            p = p->next;
            s = s->next;
        }
        return NULL;
    }
};
```

## 复杂度

- 时间：$O(m+n)$，每个链表各遍历两次（求长度一次、同步前进一次）
- 空间：$O(1)$

## 要点

### 1. 比较的是"结点地址"，不是"结点的值"

```cpp
if(p == s) return p;      // ✅ 比地址
if(p->val == s->val)      // ❌ 错！值相同不代表是同一个结点
```

**"相交"的定义是"同一个结点"，不是"值相等"。**

上面的 trace 里，`p=1(A)` 和 `s=1(B)` 就是**值相同但地址不同**的情况——
如果用值来比，这里就会误判成交点。

### 2. 为什么"长度对齐"一定对

设 A 独有段长 `a`、B 独有段长 `b`、公共段长 `c`。
对齐后，两指针分别从各自链表的"第 `a`（或 `b`）个位置"往后走，
**距离交点的剩余长度相同**，所以必定同时抵达。

### 3. 不相交时不会死循环

两指针会**同时**走到 NULL，`while(p != NULL && s != NULL)` 退出，返回 NULL。

### 4. 另一种解法：双指针走两遍（知道即可）

```cpp
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode *p = headA, *q = headB;
    while(p != q){
        p = (p == NULL) ? headB : p->next;   // A 走完接着走 B
        q = (q == NULL) ? headA : q->next;   // B 走完接着走 A
    }
    return p;                                // 有交点则相遇，无交点则同为 NULL
}
```

**原理**：两指针都走 `m+n` 步、总路程相同，所以有交点必同时到达，无交点则同时变 NULL。

**更短，但"为什么对"要想一下。408 答卷建议用"长度对齐法"——更直观、更好解释。**

## 相关题目

- 141. 环形链表（判环）
- 142. 环形链表 II（找环的入口）
- 面试题 02.07. 链表相交（同一道题）
