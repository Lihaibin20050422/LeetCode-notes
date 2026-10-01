#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* removeElements(ListNode* head, int val) {
    ListNode* dummy = new ListNode(0);   // 虚拟头结点：把"不带头"临时改造成"带头"
    dummy->next = head;
    ListNode* p = dummy;                 // p 始终指向"待检查结点的前驱"
    while(p->next != nullptr){
        if(p->next->val == val){
            ListNode* s = p->next;
            p->next = p->next->next;     // 前驱跳过它
            delete(s);
            // 注意：p 不后移，继续检查新的 p->next
        }else{
            p = p->next;
        }
    }
    ListNode* ans = dummy->next;         // 真正的新头结点
    delete(dummy);                       // 释放虚拟头
    return ans;
}

/*---------------------------- 测试辅助 ----------------------------*/
ListNode* buildList(int arr[], int n){
    ListNode* dummy = new ListNode(0);
    ListNode* tail = dummy;
    for(int i = 0; i < n; i++){
        tail->next = new ListNode(arr[i]);
        tail = tail->next;
    }
    ListNode* head = dummy->next;
    delete dummy;
    return head;
}

void printList(ListNode* head){
    for(ListNode* p = head; p != nullptr; p = p->next){
        cout << p->val << " ";
    }
    cout << endl;
}

int main(){
    int a[] = {1,2,6,3,4,5,6};
    ListNode* L1 = buildList(a,7);
    cout << "删除前    : "; printList(L1);
    cout << "删除6后   : "; printList(removeElements(L1,6));   // 期望 1 2 3 4 5

    int b[] = {7,7,7,7};
    ListNode* L2 = buildList(b,4);
    cout << "全删后    : "; printList(removeElements(L2,7));   // 期望 空

    cout << "空表      : "; printList(removeElements(nullptr,1)); // 期望 空

    // 删首元结点 —— 验证虚拟头结点的作用
    int c[] = {6,1,2};
    ListNode* L3 = buildList(c,3);
    cout << "删首元后  : "; printList(removeElements(L3,6));   // 期望 1 2

    return 0;
}
