#include <iostream>
#include <stack>
using namespace std;
stack<int> s1, s2;   // s1: 入栈（输入缓冲区）；s2: 出栈（输出缓冲区）

void push(int x) {
    s1.push(x);
}

/*---------------------- 懒汉法（最优，均摊 O(1)）----------------------*/
int pop() {
    // 只在 s2 空了时，才把 s1 全倒一次
    if (s2.empty()) {
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
    }
    // 取完【不倒回去】——s2 常驻当输出缓冲区
    int e = s2.top();
    s2.pop();
    return e;
}

int peek() {
    if (s2.empty()) {
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
    }
    return s2.top();
}

bool empty() {
    return s1.empty() && s2.empty();     // s1、s2 都空，队列才空
}

/*-------------- 对照：最初的写法（每次来回倒，O(n)/次）--------------
int pop() {
    while (!s1.empty()) { s2.push(s1.top()); s1.pop(); }
    int e = s2.top();
    s2.pop();
    while (!s2.empty()) { s1.push(s2.top()); s2.pop(); }   // ← 多倒回去这一趟
    return e;
}

int peek() {
    while (!s1.empty()) { s2.push(s1.top()); s1.pop(); }
    int e = s2.top();
    while (!s2.empty()) { s1.push(s2.top()); s2.pop(); }
    return e;
}
-----------------------------------------------------------------------*/

// 测试示例
int main() {
    // 示例
    push(1);
    push(2);
    cout << peek() << endl;   // 1
    cout << pop() << endl;    // 1
    cout << empty() << endl;  // false(0)

    // 交错操作：验证「s2 非空时继续 push」的情况（懒汉法最容易错的地方）
    push(3);
    cout << pop() << endl;    // 2  ← 2 还在 s2 里，队头仍是 2
    cout << pop() << endl;    // 3
    cout << empty() << endl;  // true(1)
    return 0;
}
