/*
编写一个函数来查找字符串数组中的最长公共前缀。
如果不存在公共前缀，返回空字符串 ""。
示例 1：
输入：strs = ["flower","flow","flight"]
输出："fl"
示例 2：
输入：strs = ["dog","racecar","car"]
输出：""
解释：输入不存在公共前缀。
*/
#include <iostream>
#include <vector>
using namespace std;
string longestCommonPrefix(vector<string>& strs) {
    if(strs.empty()){
            return "";
    }
    string prefix = strs[0];
    for(int i=1;i<strs.size();++i){
        while(strs[i].find(prefix)!=0){
            prefix.pop_back();
            if(prefix.empty()){
                return "";
            }
        }
    }
    return prefix;
}

int main(){
    int n;
    cin >> n;
    vector<string> strs(n);
    for(int i=0;i<n;i++){
        cin >> strs[i];
    }
    cout << longestCommonPrefix(strs) << endl;
    return 0;
}