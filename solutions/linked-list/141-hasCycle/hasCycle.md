# 141.hasCycle(环形链表)

## 题目
给你一个链表的头节点 head，判断链表中是否有环。
如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
如果链表中存在环，则返回 true；否则返回 false。

示例 1:
输入: head = [3,2,0,-4], pos = 1（尾结点连接到下标 1 的结点）
输出: true

示例 2:
输入: head = [1,2], pos = 0
输出: true

示例 3:
输入: head = [1], pos = -1
输出: false

## 思路

**快慢指针（Floyd 判圈算法 / 龟兔赛跑）**：设 fast 一次走 2 个结点、slow 一次走 1 个结点，同时从 head 出发。

- **若无环**：fast 会先到达终点（NULL），循环结束，返回 false
- **若有环**：两者都会进入环。进入环之后，fast 每轮比 slow 多走 1 步，所以两者的距离**每轮减 1**；距离是有限的非负整数，**必然减到 0** —— 即相遇，返回 true

**注意措辞**：不是"可能会相遇"，是"必然相遇"。因为相对速度为 1、距离是整数、每轮必减 1，没有"错过"的可能。

用一个例子理解：`head = 3 → 2 → 0 → -4 →（指回 2）`

```
初始 : fast = 3,   slow = 3
第1轮: fast = 0,   slow = 2    不等
第2轮: fast = 2,   slow = 0    不等
第3轮: fast = -4,  slow = -4   相遇 → true
```

## 代码
```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast != NULL && fast->next != NULL){
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow) return true;
        }
        return false;
    }
};
```

## 复杂度

- 时间：$O(n)$，slow 最多走完一圈，fast 最多走两圈
- 空间：$O(1)$，只用了两个指针

## 要点

### 1. 为什么 fast 走 2 步、slow 走 1 步？（本题最该讲清的一点）

因为要保证"**相对速度 = 1**"：

| fast 每轮走 | 相对速度 | 结果 |
|---|---|---|
| **2 步** | 1 | 距离每轮 **-1**，必然减到 0 → **必然相遇** ✅ |
| 3 步 | 2 | 距离每轮 **-2**，若初始距离是奇数，会从 1 跳到 -1（绕过去）→ **可能永远遇不上** ❌ |

**所以"走 2 步"不是随便选的，它是保证"相对速度为 1"的最小选择。**

### 2. 循环条件两个都不能少

```cpp
while(fast != NULL && fast->next != NULL)
```

因为循环体里要访问 `fast->next->next`，若 `fast` 或 `fast->next` 为空就会崩。
- `fast != NULL`：保证 `fast->next` 可访问
- `fast->next != NULL`：保证 `fast->next->next` 可访问

### 3. 比较的时机必须在移动之后

如果一开始就比较（两者都在 head），会立刻"相等"，造成**假阳性**。
必须在两个指针都移动之后再比。

## 相关题目

- 142. 环形链表 II（**找环的入口**，本题的进阶）
  → 相遇后，让一个指针回到 head，两指针同速前进，再次相遇处即为环的入口
- 202. 快乐数（本质也是判环）
- 287. 寻找重复数（可用同样思路）
