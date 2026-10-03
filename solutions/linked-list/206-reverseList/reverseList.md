# 206.reverseList(反转链表)

## 题目
给你单链表的头节点 head，请你反转链表，并返回反转后的链表。

示例 1:
输入: head = [1,2,3,4,5]
输出: [5,4,3,2,1]

示例 2:
输入: head = [1,2]
输出: [2,1]

示例 3:
输入: head = []
输出: []

## 思路

**头插法（虚拟头结点）**：新建一个虚拟头结点 `dummy`，逐个摘下原链表的结点，
用**头插法**插到 `dummy` 后面。

因为每次插入都插在"最前面"，插入顺序与原顺序相反——所以全部插完之后，链表自然就逆置了。

1. 新建 `dummy`，`cur = head`
2. 循环：暂存 `cur->next` → 把 `cur` 头插到 `dummy` 后面 → `cur` 后移
3. 返回 `dummy->next`

用一个例子理解：`head = [1,2,3]`

```
初始 : dummy -> NULL , cur = 1

第1轮: 暂存后继=2 ; 1->next = dummy->next = NULL ; dummy->next = 1 ; cur = 2
       → dummy -> 1 -> NULL

第2轮: 暂存后继=3 ; 2->next = 1                  ; dummy->next = 2 ; cur = 3
       → dummy -> 2 -> 1 -> NULL

第3轮: 暂存后继=NULL ; 3->next = 2               ; dummy->next = 3 ; cur = NULL
       → dummy -> 3 -> 2 -> 1 -> NULL

返回 dummy->next = 3
```

## 代码
```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* dummy = new ListNode();
        ListNode* cur = head;
        while(cur != nullptr){
            ListNode* s = cur->next;      // 暂存后继
            cur->next = dummy->next;      // 头插到 dummy 后面
            dummy->next = cur;
            cur = s;
        }
        ListNode* ans = dummy->next;
        delete dummy;
        return ans;
    }
};
```

## 复杂度

- 时间：$O(n)$
- 空间：$O(1)$

## 要点

### 1. 这道题 = 数据结构综合题 03（就地逆置）· 头插法

**这本质上就是"带头结点的单链表就地逆置"**，只是题目**不给头结点**，所以要自己造一个：

| | DS 综合题 03 · 解法二 | LC 206 |
|---|---|---|
| 头结点从哪来 | **题目给的 L** | **自己 new 的 dummy** |
| 暂存后继 | `s = p->next` | `s = cur->next` |
| 头插 | `p->next = L->next; L->next = p;` | `cur->next = dummy->next; dummy->next = cur;` |
| 后移 | `p = s` | `cur = s` |

**除了头结点的来源，逐行对应。**

### 2. 虚拟头结点的第二次使用

这是虚拟头结点的两个典型应用：

| 题目 | 不给头结点 → 自己造 → 复用什么 |
|---|---|
| **LC 203** 移除元素 | 复用"带头结点"的**删除**逻辑 |
| **LC 206** 反转链表 | 复用"带头结点"的**头插法** |

> **虚拟头结点 = 手动补上题目没给你的头结点。**

### 3. 另外两种解法

**① 三指针法**（DS 综合题 03 · 解法一）：

```cpp
ListNode* pre = NULL, *cur = head;
while(cur){
    ListNode* next = cur->next;
    cur->next = pre;
    pre = cur;
    cur = next;
}
return pre;
```

**② 递归法**（经典，面试常问）：

```cpp
ListNode* reverseList(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* newHead = reverseList(head->next);   // 先假设"后面的已经逆置好了"
    head->next->next = head;                       // 让后继指回自己
    head->next = nullptr;                          // 自己变成尾结点
    return newHead;
}
```

**递归法的思维**：**假设"子问题已解决"**——先逆置后面的，然后只需要处理"我"和"我的后继"这一对。

**这个思维在树、动态规划里会反复出现。**

## 相关题目

- 92. 反转链表 II（反转指定区间，本题的进阶）
- 25. K 个一组翻转链表（困难）
- 234. 回文链表（用反转辅助判断）
- 剑指 Offer 24. 反转链表（同一道题）
