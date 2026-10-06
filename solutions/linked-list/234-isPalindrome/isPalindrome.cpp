#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

bool isPalindrome(ListNode* head) {
    if(head == nullptr || head->next == nullptr){
        return true;
    }

    // ① 快慢指针找中点：slow 停在"前半部分的最后一个结点"
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast->next != nullptr && fast->next->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }

    // ② 反转后半部分（三指针法）
    ListNode* pre = nullptr;
    ListNode* cur = slow->next;
    while(cur != nullptr){
        ListNode* nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }

    // ③ 一个从 head 出发、一个从反转后的后半头部出发，逐个比较
    while(pre != nullptr && head != nullptr){
        if(pre->val != head->val){
            return false;
        }
        pre = pre->next;
        head = head->next;
    }
    return true;
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

int main(){
    int a[] = {1,2,2,1};
    int b[] = {1,2};
    int c[] = {1,2,3,2,1};
    int d[] = {1,2,3,2,2};
    int e[] = {1};

    cout << "[1,2,2,1]    : " << isPalindrome(buildList(a,4)) << "  (期望 1)" << endl;
    cout << "[1,2]        : " << isPalindrome(buildList(b,2)) << "  (期望 0)" << endl;
    cout << "[1,2,3,2,1]  : " << isPalindrome(buildList(c,5)) << "  (期望 1)" << endl;
    cout << "[1,2,3,2,2]  : " << isPalindrome(buildList(d,5)) << "  (期望 0)" << endl;
    cout << "[1]          : " << isPalindrome(buildList(e,1)) << "  (期望 1)" << endl;

    return 0;
}
