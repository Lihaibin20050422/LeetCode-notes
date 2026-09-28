#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL){}
};

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode* p = headA;
    ListNode* s = headB;
    int lenA = 0;
    int lenB = 0;

    while(p!=NULL){        // ① 求 A 的长度
        p = p->next;
        lenA++;
    }
    while(s!=NULL){        // ② 求 B 的长度
        s = s->next;
        lenB++;
    }

    p = headA;
    s = headB;
    int i = 0;
    if(lenA>lenB){         // ③ 较长的链表先走 |lenA-lenB| 步
        while(i<lenA-lenB){
            p = p->next;
            i++;
        }
    }else{
        while(i<lenB-lenA){
            s = s->next;
            i++;
        }
    }

    while(p!=NULL&&s!=NULL){  // ④ 同步前进，第一个地址相同的就是交点
        if(p==s){             // 注意：比的是结点地址，不是结点的值
            return p;
        }
        p = p->next;
        s = s->next;
    }
    return NULL;              // 都走到 NULL 说明不相交
}

/*----------------------------------------------------------------
测试：构造两条共享尾部的链表
   A: 4 -> 1 -> ┐
                ├─> 8 -> 4 -> 5   （在结点 8 处相交）
   B: 5 -> 6 -> 1 -> ┘
----------------------------------------------------------------*/
int main(){
    // 先建公共段：8 -> 4 -> 5
    ListNode* common = new ListNode(8);
    common->next = new ListNode(4);
    common->next->next = new ListNode(5);

    // A 的独有段：4 -> 1，末尾接上公共段
    ListNode* headA = new ListNode(4);
    headA->next = new ListNode(1);
    headA->next->next = common;

    // B 的独有段：5 -> 6 -> 1，末尾接上公共段
    ListNode* headB = new ListNode(5);
    headB->next = new ListNode(6);
    headB->next->next = new ListNode(1);
    headB->next->next->next = common;

    ListNode* res = getIntersectionNode(headA, headB);
    cout << "有交点时      : " << (res ? res->val : -1) << "   (期望 8)" << endl;

    // 测试不相交
    ListNode* x = new ListNode(1);
    x->next = new ListNode(2);
    ListNode* y = new ListNode(3);
    y->next = new ListNode(4);
    cout << "不相交时      : " << (getIntersectionNode(x, y) ? "非空" : "空") << "   (期望 空)" << endl;

    // 测试完全重合（同一个头）
    cout << "完全重合时    : " << (getIntersectionNode(x, x) ? "非空" : "空") << "   (期望 非空)" << endl;

    return 0;
}
