#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode* dummy = new ListNode();     // 虚拟头结点：复用"带头结点"的头插法
    ListNode* cur = head;
    while (cur != nullptr) {
        ListNode* s = cur->next;          // 暂存后继
        cur->next = dummy->next;          // 头插到 dummy 后面
        dummy->next = cur;
        cur = s;
    }
    ListNode* ans = dummy->next;
    delete dummy;
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
    int a[] = {1,2,3,4,5};
    ListNode* L1 = buildList(a,5);
    cout << "逆置前  : "; printList(L1);
    cout << "逆置后  : "; printList(reverseList(L1));            // 期望 5 4 3 2 1

    cout << "单结点  : "; printList(reverseList(buildList(a,1))); // 期望 1
    cout << "空表    : "; printList(reverseList(nullptr));        // 期望 空

    return 0;
}
