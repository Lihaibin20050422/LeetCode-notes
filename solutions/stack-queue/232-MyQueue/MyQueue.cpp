#include <iostream>
#include <stack>
using namespace std;
stack<int> s1, s2;

void push(int x) {
    s1.push(x);
}

int pop() {
    while (!s1.empty()) {
        s2.push(s1.top());
        s1.pop();
    }
    int e = s2.top();
    s2.pop();
    while (!s2.empty()) {
        s1.push(s2.top());
        s2.pop();
    }
    return e;
}

int peek() {
    while (!s1.empty()) {
        s2.push(s1.top());
        s1.pop();
    }
    int e = s2.top();
    while (!s2.empty()) {
        s1.push(s2.top());
        s2.pop();
    }
    return e;
}

bool empty() {
    return s1.empty();
}

// 测试示例
int main() {
    push(1);
    push(2);
    cout << peek() << endl;   // 1
    cout << pop() << endl;    // 1
    cout << empty() << endl;  // false
    return 0;
}
