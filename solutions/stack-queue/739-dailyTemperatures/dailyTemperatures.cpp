#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> res(n, 0);
    stack<int> st;
    for(int i = 0; i < temperatures.size(); i++){
        while(!st.empty() && temperatures[i] > temperatures[st.top()]){
            int idx = st.top();
            st.pop();
            res[idx] = i - idx;
        }
        st.push(i);
    }
    return res;
}

void printVec(const vector<int>& v)
{
    for(int x : v) cout << x << " ";
    cout << endl;
}

int main()
{
    vector<int> t1 = {73,74,75,71,69,72,76,73};
    cout << "示例    : "; printVec(dailyTemperatures(t1));   // 期望 1 1 4 2 1 1 0 0

    vector<int> t2 = {30,40,50,60};
    cout << "递增    : "; printVec(dailyTemperatures(t2));   // 期望 1 1 1 0

    vector<int> t3 = {90,80,70,60};
    cout << "递减    : "; printVec(dailyTemperatures(t3));   // 期望 0 0 0 0

    vector<int> t4 = {50,50,50};
    cout << "全相等  : "; printVec(dailyTemperatures(t4));   // 期望 0 0 0

    vector<int> t5;
    cout << "空数组  : "; printVec(dailyTemperatures(t5));   // 期望 空

    return 0;
}
