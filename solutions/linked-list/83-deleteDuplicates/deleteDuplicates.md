# 83.deleteDuplicates(删除排序链表中的重复元素)

## 题目
给定一个已排序的链表的头 head，删除所有重复的元素，使每个元素只出现一次。返回已排序的链表。

示例 1:
输入: head = [1,1,2]
输出: [1,2]

示例 2:
输入: head = [1,1,2,3,3]
输出: [1,2,3]

## 思路

**快慢指针（保留法）**：因为链表已排序，重复元素一定相邻。`slow` 指向已保留部分的最后一个结点，`quick` 从前向后扫描；当 `quick` 与 `quick->next` 的值不同时，说明 `quick` 是当前值组的最后一个，于是把下一组的头结点接到 `slow` 后面。

1. `slow = quick = head`
2. `quick` 扫描：若 `quick->val != quick->next->val`，则 `slow->next = quick->next`，`slow` 后移
3. `quick` 后移
4. 循环结束（quick 到末尾）后，`slow->next = nullptr` 截断尾部残留的重复结点

用一个例子理解：`head = [1,1,2,2,3]`

```
slow=1(node1), quick=1(node1)
quick(1) vs next(1) 相同 → 跳过，quick 移到 node2
quick(1) vs next(2) 不同 → slow->next = node3(2), slow 移到 node3
quick 移到 node3(2)
quick(2) vs next(2) 相同 → 跳过，quick 移到 node4
quick(2) vs next(3) 不同 → slow->next = node5(3), slow 移到 node5
quick 移到 node5(3)，next 为空 → 退出
slow->next = nullptr
结果: 1 -> 2 -> 3
```

## 代码
```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == nullptr) return head;
        ListNode* slow = head;
        ListNode* quick = head;
        while(quick != nullptr && quick->next != nullptr){
            if(quick->val != quick->next->val){   // quick 是当前值组的最后一个
                slow->next = quick->next;         // 下一组的首结点接到 slow 后
                slow = slow->next;
            }
            quick = quick->next;
        }
        slow->next = nullptr;   // 截断尾部残留的重复结点
        return head;
    }
};
```

## 复杂度

- 时间：$O(n)$，一趟扫描
- 空间：$O(1)$，只用了两个指针

## 要点

### 1. 更简洁的写法：单指针"跳过法"

链表上更自然的写法是"遇到重复就直接跳过"，一个指针就够：

```cpp
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* cur = head;
    while(cur != nullptr && cur->next != nullptr){
        if(cur->val == cur->next->val){
            cur->next = cur->next->next;   // 跳过重复结点
        }else{
            cur = cur->next;
        }
    }
    return head;
}
```

两种写法都对，但**链表上"跳过法"比"保留法"更自然**——因为链表改指针比搬元素方便。

### 2. 顺序表用"保留法"，链表用"跳过法"

这个对比很有意思：

| | 删除重复的写法 | 原因 |
|---|---|---|
| 顺序表（408 综合题 05） | 快慢指针 + 覆盖写（保留法） | 要搬移元素，只能"重写" |
| 链表（本题） | 直接改指针跳过（跳过法） | 改指针比搬元素省事 |

**数据结构决定算法写法**——这是 408 反复考的思维。

### 3. "已排序"是前提

题目说"已排序"，所以重复元素一定相邻，才能一趟扫描解决。如果无序，就得先排序（$O(n\log n)$）或用哈希表（$O(n)$ 空间）。

### 4. 边界处理

- `head == nullptr`：空链表直接返回
- `slow->next = nullptr`：防止最后一个值组有重复时，尾部残留多余结点

## 相关题目

- 82. 删除排序链表中的重复元素 II（重复的**全部删掉**，一个不留）
- 26. 删除有序数组中的重复项（顺序表版，保留法）
- 27. 移除元素（顺序表，保留法）
