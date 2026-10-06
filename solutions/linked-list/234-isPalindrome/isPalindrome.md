# 234.isPalindrome(回文链表)

## 题目
给你一个单链表的头节点 head，请你判断该链表是否为回文链表。
如果是，返回 true；否则，返回 false。

示例 1:
输入: head = [1,2,2,1]
输出: true

示例 2:
输入: head = [1,2]
输出: false

## 思路

**快慢指针找中点 + 反转后半部分 + 双指针比较**（时间 $O(n)$，空间 $O(1)$）：

1. **找中点**：快指针每次走 2 步、慢指针每次走 1 步；走完后 `slow` 指向"前半部分的最后一个结点"
2. **反转后半部分**：从 `slow->next` 开始，用**三指针法**原地反转
3. **比较**：一个指针从 `head` 出发、一个从反转后的后半头部出发，逐个比较；全相同则是回文
4. （可选）把后半再反转一次，恢复原链表

**为什么是"反转后半"，而不是"反转整条"？**

因为**反转整条链表会破坏原链表**，就没有"另一半"可以拿来比较了。
而"反转后半 + 从头和后半同时走"，两边正好一对一对。

用一个例子理解：`head = [1,2,2,1]`

```
① 找中点：slow 停在 index 1（值为 2 的那个）
② 反转 slow->next 开始的后半：  2 -> 1   变成   1 -> 2
③ 比较：
     head 从 1 出发： 1,  2
     后半 从 1 出发： 1,  2      → 全相同 → true
```

## 代码
```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head == nullptr || head->next == nullptr) return true;

        // ① 快慢指针找中点
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast->next != nullptr && fast->next->next != nullptr){
            slow = slow->next;
            fast = fast->next->next;
        }

        // ② 反转后半部分
        ListNode* pre = nullptr;
        ListNode* cur = slow->next;
        while(cur != nullptr){
            ListNode* nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }

        // ③ 从头和后半同时走，逐个比较
        while(pre != nullptr && head != nullptr){
            if(pre->val != head->val) return false;
            pre = pre->next;
            head = head->next;
        }
        return true;
    }
};
```

## 复杂度

- 时间：$O(n)$
- 空间：$O(1)$ ← **满足题目的进阶要求**

## 要点

### 1. 这条优化路，是一步步逼出来的

```
暴力：每轮找第 i 个和第 n-i 个        → O(n²)
用数组存下来再比                     → O(n) 时间，但 O(n) 空间
【反转后半部分】                     → O(n) 时间 + O(1) 空间  ✅
```

**"链表不能随机访问 + 指针不能倒退"——这两个限制，正是逼出"反转"这个办法的原因。**

### 2. 为什么反转"后半"而不是"整条"

**反转整条 = 破坏原链表** → 就没有另一半可以比了。

**必须先找中点，再反转后半**：这样前半还在、后半被倒过来了，两边正好对称。

（这正是"链表只能单向走"带来的一个典型的绕路思路。）

### 3. 中点找法：`fast->next && fast->next->next`

```cpp
while(fast->next != nullptr && fast->next->next != nullptr)
```

这个写法让 `slow` 停在"**前半部分的最后一个结点**"：

| 长度 | slow 停在哪 |
|---|---|
| 奇数（2k+1）| 正中间（下标 k）|
| 偶数（2k）| 前半的最后一个（下标 k-1）|

**两种情况都保证"后半的长度 ≤ 前半"**，所以第③步只要用 `pre != nullptr` 当条件就够了（后半走完即停）。

### 4. （可选）恢复链表

比较完之后，把后半再反转一次就能还原：

```cpp
ListNode* cur2 = pre;
ListNode* pre2 = nullptr;
while(cur2 != nullptr){
    ListNode* nxt = cur2->next;
    cur2->next = pre2;
    pre2 = cur2;
    cur2 = nxt;
}
slow->next = pre2;      // 接回前半
```

**LeetCode 不检查这个，但面试常追问"能否保持链表原样"。**

## 相关题目

- 9. 回文数
- 125. 验证回文串
- 206. 反转链表（本题直接复用了它的技术）
