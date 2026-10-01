# 203.removeElements(移除链表元素)

## 题目
给你一个链表的头节点 head 和一个整数 val，请你删除链表中所有满足 Node.val == val 的节点，
并返回新的头节点。

示例 1:
输入: head = [1,2,6,3,4,5,6], val = 6
输出: [1,2,3,4,5]

示例 2:
输入: head = [], val = 1
输出: []

示例 3:
输入: head = [7,7,7,7], val = 7
输出: []

## 思路

**虚拟头结点 + 前驱指针**：

1. 新建虚拟头结点 `dummy`，令 `dummy->next = head`
2. 用指针 `p` 从 `dummy` 开始遍历（`p` 始终指向**待检查结点的前驱**）
3. 若 `p->next->val == val`，则删除 `p->next`（前驱跳过它），**`p` 不后移**
4. 否则 `p` 后移一位
5. 返回 `dummy->next`，并释放 `dummy`

用一个例子理解：`head = [1,2,6,3,4,5,6]`, `val = 6`

```
dummy -> 1 -> 2 -> 6 -> 3 -> 4 -> 5 -> 6

p=1: p->next=2  ≠6 → p 移到 2
p=2: p->next=6  =6 → 删掉 6，2->3，p 不动
p=2: p->next=3  ≠6 → p 移到 3
p=3: p->next=4  ≠6 → p 移到 4
p=4: p->next=5  ≠6 → p 移到 5
p=5: p->next=6  =6 → 删掉 6，5->NULL，p 不动
p=5: p->next=NULL → 结束

返回 dummy->next = 1
结果: 1 -> 2 -> 3 -> 4 -> 5
```

## 代码
```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* p = dummy;
        while(p->next != nullptr){
            if(p->next->val == val){
                ListNode* s = p->next;
                p->next = p->next->next;
                delete(s);
                // p 不后移
            }else{
                p = p->next;
            }
        }
        ListNode* ans = dummy->next;
        delete(dummy);
        return ans;
    }
};
```

## 复杂度

- 时间：$O(n)$
- 空间：$O(1)$

## 要点

### 1. 虚拟头结点的本质：手动补一个"头结点"（本题最该讲清的一点）

**不带头结点的链表，删第一个结点时要改 head 指针本身**，所以只能单独处理"删头"，代码分裂成两段：

```cpp
while(head != nullptr && head->val == val){
    head = head->next;      // 只能靠改 head 来"删头"
}
// 之后才能处理中间的结点
```

**而加上 `dummy` 之后**，第一个数据结点变成了 `dummy->next`——
**它和中间结点一样"有个前驱"**，于是全程只需要一套逻辑。

> **虚拟头结点 = 手动补上那个题目没给你的头结点 = 把"不带头结点"临时改造成"带头结点"。**

**这和 408 里"带头结点让操作统一、省掉边界特判"是同一个原理。**

对照数据结构综合题（带头结点，题目直接给了头结点）：

| | 408 综合题 | LeetCode 203 |
|---|---|---|
| 头结点从哪来 | **题目给** | **自己 new** |
| 循环变量 | `p = L` | `p = dummy` |
| 删除逻辑 | 删 `p->next` | **删 `p->next`（一模一样）** |

### 2. 删除时 p 不能后移

```cpp
if(p->next->val == val){
    ...
    // p 不后移，继续检查新的 p->next
}
```

如果删完就 `p = p->next`，遇到**连续多个 val** 会漏删。

### 3. 返回 dummy->next，不是 head

删掉首元结点后，原来的 `head` 会**悬空**（指向已释放的结点）。
所以必须返回 `dummy->next`——它才是真正的新头结点。

### 4. 结尾要释放 dummy

`delete dummy` 是应该做的（虽然 LeetCode 不检查内存）。
但注意**不能顺手把整条链表也 delete 掉**——题目要求保持原结构。

## 相关题目

- 83. 删除排序链表中的重复元素（虚拟头 + 快慢指针）
- 82. 删除排序链表中的重复元素 II（重复的全删）
- 19. 删除链表的倒数第 N 个结点（虚拟头的经典应用）
- 21. 合并两个有序链表（虚拟头 + 尾指针）
- 24. 两两交换链表中的结点（虚拟头）
