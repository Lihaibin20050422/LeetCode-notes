#include <iostream>
#include <queue>
using namespace std;

queue<int> q1, q2;

void push(int x) {
    q1.push(x);
}

int pop() {
    while(q1.size() > 1){
        q2.push(q1.front());
        q1.pop();
    }
    int res = q1.front();
    q1.pop();
    swap(q1, q2);
    return res;
}

int top() {
    while(q1.size() > 1){
        q2.push(q1.front());
        q1.pop();
    }
    int res = q1.front();
    q2.push(res);
    q1.pop();
    swap(q1, q2);
    return res;
}

bool empty() {
    return q1.empty();
}

// main函数测试
int main()
{
    push(1);
    push(2);
    cout << top() << endl;    // 输出2
    cout << pop() << endl;    // 输出2
    cout << empty() << endl;  // 输出0(false)
    return 0;
}