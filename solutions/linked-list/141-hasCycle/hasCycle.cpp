#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

bool hasCycle(ListNode *head) {
    ListNode* fast = head;   // 快指针：一次走两个结点
    ListNode* slow = head;   // 慢指针：一次走一个结点
    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow){    // 两者相遇 → 有环
            return true;
        }
    }
    return false;            // fast 走到终点 → 无环
}

// 构造无环链表：1 -> 2 -> 3 -> NULL
ListNode* buildNoCycle(){
    ListNode* n1 = new ListNode(1);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(3);
    n1->next = n2;  n2->next = n3;  n3->next = NULL;
    return n1;
}

// 构造带环链表：1 -> 2 -> 3 -> 2（3 的 next 指回 2）
ListNode* buildCycle(){
    ListNode* n1 = new ListNode(1);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(3);
    n1->next = n2;  n2->next = n3;  n3->next = n2;
    return n1;
}

int main(){
    cout << "空链表        : " << hasCycle(NULL)            << "  (期望 0)" << endl;
    cout << "单个结点      : " << hasCycle(new ListNode(1)) << "  (期望 0)" << endl;
    cout << "无环 1->2->3  : " << hasCycle(buildNoCycle())  << "  (期望 0)" << endl;
    cout << "有环 1->2->3->2: " << hasCycle(buildCycle())    << "  (期望 1)" << endl;
    return 0;
}
