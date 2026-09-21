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

ListNode* deleteDuplicates(ListNode* head) {
    if(head==nullptr){
        return head;
    }
    ListNode* slow = head;
    ListNode* quick = head;
    while(quick!=nullptr&&quick->next!=nullptr){
        if(quick->val!=quick->next->val){
            slow->next = quick->next;
            slow = slow->next;
        }
        quick = quick->next;
    }
    slow->next = nullptr;
    return head;
}

int main(){
    int a[] = {1,1,2,2,3};
    ListNode* L = buildList(a,5);
    deleteDuplicates(L);
    printList(L);
}
