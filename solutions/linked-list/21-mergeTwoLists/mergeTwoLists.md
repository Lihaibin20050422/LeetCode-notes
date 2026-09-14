# 21.mergeTwoLists(合并两个有序链表)

## 题目
将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

示例 1:
输入: list1 = [1,2,4], list2 = [1,3,4]
输出: [1,1,2,3,4,4]

示例 2:
输入: list1 = [], list2 = []
输出: []

示例 3:
输入: list1 = [], list2 = [0]
输出: [0]

## 思路

**虚拟头结点 + 双指针 + 复用节点**：同时遍历两个链表，每次把值较小的节点接到新链表末尾，直到其中一个链表空，再把另一个剩余部分直接接上。

1. 建一个虚拟头结点 `dummy`，`tail` 永远指向新链表的末尾
2. `list1`、`list2` 双指针同时遍历，比较 `val`，小的那个**直接接到** `tail->next`（复用原节点，不新建）
3. 对应指针后移，`tail` 后移
4. 某个链表空了，把另一个剩余部分**整体接上**
5. 返回 `dummy->next`（虚拟头的下一个，才是真正的链表头）

用一个例子理解：`list1 = [1,2,4]`, `list2 = [1,3,4]`

```
dummy -> (空)
比较 1 vs 1：list2 的 1 更小（else 分支）→ 接 list2[1]
比较 1 vs 3：list1 的 1 更小 → 接 list1[1]
比较 2 vs 3：list1 的 2 更小 → 接 list1[2]
比较 4 vs 3：list2 的 3 更小 → 接 list2[3]
比较 4 vs 4：list2 的 4（else 分支）→ 接 list2[4]
list2 空 → 剩余 list1[4] 直接接上
结果: [1,1,2,3,4,4]
```

## 代码
```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode(0);  // 虚拟头结点
        ListNode* tail = dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                tail->next = list1;         // 复用原节点
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        tail->next = (list1 != nullptr) ? list1 : list2;  // 剩余直接接上
        return dummy->next;
    }
};
```

## 复杂度

- 时间：$O(m+n)$，两个链表各遍历一次
- 空间：$O(1)$，只用了几个指针变量（复用原节点，不开新空间）

## 要点

### 1. 虚拟头结点（dummy node）——链表题最重要的技巧

**问题**：如果没有虚拟头结点，第一个节点需要"特殊处理"——因为一开始 `tail` 是空的，`tail->next` 无法赋值。

**解法**：先 `new` 一个无关紧要的 `dummy` 节点当头，`tail` 从它开始。这样所有节点（包括第一个）都能用统一的 `tail->next = ...` 处理，最后返回 `dummy->next` 丢掉这个虚拟头。

**本质**：虚拟头结点把"空链表"和"非空链表"统一成了同一种情况，消灭了边界特判。后面 203、206、19、24 等链表题几乎全用这个技巧。

### 2. 复用节点 vs 新建节点——链表题的空间关键

题目说"新链表是通过**拼接**给定的所有节点组成的"，所以要**复用原节点**：

```cpp
tail->next = list1;   // ✅ 复用：只改指针，空间 O(1)
tail->next = new ListNode(list1->val);  // ❌ 新建：复制值，空间 O(m+n)
```

- 复用的是"把原节点从旧链表里摘下来、接到新链表上"，不额外分配内存
- 新建的是"复制一个值相同的新节点"，功能也对但浪费空间

**链表题的精髓就是"只动指针、不开新空间"**，能复用就复用。

### 3. C++ 构造函数（本地测试需要自己定义 ListNode）

LeetCode 平台自动给了 `ListNode` 定义，但本地跑要自己写：

```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}          // new ListNode() 时调用
    ListNode(int x) : val(x), next(nullptr) {}     // new ListNode(5) 时调用
};
```

- `: val(0), next(nullptr)` 是**初始化列表**，创建对象时直接给成员变量赋值
- `ListNode()` 是默认构造，`ListNode(int x)` 是带参构造，两者靠参数个数区分
- 对比 C 的写法：C++ 构造函数就是把 `malloc + 手动赋值` 打包进了一个语法，本质一样

## 相关题目

- 88. 合并两个有序数组（同思路，数组版，但数组要从后往前填）
- 23. 合并 K 个升序链表（本题进阶，用优先队列或分治）
- 203. 移除链表元素（虚拟头结点的另一个经典应用）
