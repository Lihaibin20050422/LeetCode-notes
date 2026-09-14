/*
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
示例 1:
输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
示例 2：
输入：l1 = [], l2 = []
输出：[]
示例 3：
输入：l1 = [], l2 = [0]
输出：[0]
*/

#include <iostream>
using namespace std;

// 链表节点定义（LeetCode 平台自带，本地要自己写）
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}          // 默认构造：new ListNode()
    ListNode(int x) : val(x), next(nullptr) {}     // 带值构造：new ListNode(5)
};

// 辅助：根据数组构建链表
ListNode* buildList(int arr[], int n) {
    ListNode* dummy = new ListNode(0);
    ListNode* tail = dummy;
    for (int i = 0; i < n; i++) {
        tail->next = new ListNode(arr[i]);
        tail = tail->next;
    }
    return dummy->next;
}

// 辅助：打印链表
void printList(ListNode* head) {
    for (ListNode* p = head; p != nullptr; p = p->next) {
        cout << p->val << " ";
    }
    cout << endl;
}

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* dummy = new ListNode(0);  // 虚拟头结点，避免头结点特殊处理
    ListNode* tail = dummy;             // tail 永远指向新链表末尾

    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val < list2->val) {
            tail->next = list1;         // 复用原节点，不是 new 复制
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    // 剩余链表直接接上（复用原节点）
    tail->next = (list1 != nullptr) ? list1 : list2;
    return dummy->next;                 // 返回虚拟头的下一个，即真正链表头
}

int main() {
    int a[] = {1, 2, 4};
    int b[] = {1, 3, 4};
    ListNode* l1 = buildList(a, 3);
    ListNode* l2 = buildList(b, 3);
    ListNode* res = mergeTwoLists(l1, l2);
    printList(res);   // 期望输出 1 1 2 3 4 4
    return 0;
}
