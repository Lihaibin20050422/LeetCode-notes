#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

int evalRPN(vector<string>& tokens) {
    stack<int> st;
    for(int i = 0; i < tokens.size(); i++){
        string s = tokens[i];
        if(s == "+" || s == "-" || s == "*" || s == "/"){
            int a = st.top();
            st.pop();
            int b = st.top();
            st.pop();
            int res;
            if(s == "+"){
                res = b + a;
            }
            else if(s == "-"){
                res = b - a;
            }
            else if(s == "*"){
                res = b * a;
            }
            else{
                res = b / a;
            }
            st.push(res);
        }else{
            st.push(stoi(s));
        }
    }
    return st.top();
}

int main()
{
    vector<string> t1 = {"2","1","+","3","*"};
    cout << "((2+1)*3)   : " << evalRPN(t1) << " (期望 9)" << endl;

    vector<string> t2 = {"4","13","5","/","+"};
    cout << "4+(13/5)    : " << evalRPN(t2) << " (期望 6)" << endl;

    vector<string> t3 = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
    cout << "LC 长样例   : " << evalRPN(t3) << " (期望 22)" << endl;

    vector<string> t4 = {"3"};
    cout << "单个操作数  : " << evalRPN(t4) << " (期望 3)" << endl;

    vector<string> t5 = {"4","-2","/"};
    cout << "4/(-2)      : " << evalRPN(t5) << " (期望 -2，向零截断)" << endl;
    return 0;
}
