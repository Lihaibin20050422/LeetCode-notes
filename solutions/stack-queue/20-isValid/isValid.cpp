#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isValid(string s) {
    stack<char> S;
    int i = 0;
    while (i < s.size()) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            S.push(s[i]);
        } else if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
            if (S.empty()) {
                return false;
            }
            char top = S.top();
            S.pop();
            if (!((top == '(' && s[i] == ')') || 
                  (top == '[' && s[i] == ']') || 
                  (top == '{' && s[i] == '}'))) {
                return false;
            }
        }
        i++;
    }
    return S.empty();
}

int main() {
    cout << boolalpha;
    cout << "\"\"       : " << isValid("") << endl;        // 期望 true（空串有效）
    cout << "\"()\"     : " << isValid("()") << endl;      // 期望 true
    cout << "\"(]\"     : " << isValid("(]") << endl;      // 期望 false
    cout << "\"()[]{}\" : " << isValid("()[]{}") << endl;  // 期望 true
    cout << "\"([)]\"   : " << isValid("([)]") << endl;    // 期望 false（交叉不合法）
    cout << "\"{[]}\"   : " << isValid("{[]}") << endl;    // 期望 true（嵌套）
    cout << "\"(\"      : " << isValid("(") << endl;       // 期望 false（左括号多余）
    cout << "\")\"      : " << isValid(")") << endl;       // 期望 false（右括号多余）
    return 0;
}