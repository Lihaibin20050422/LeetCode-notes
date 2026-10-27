#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> mp;
    for(auto& s : strs){
        string key = s;
        sort(key.begin(), key.end());
        mp[key].push_back(s);
    }
    vector<vector<string>> res;
    for(auto& item : mp){
        res.push_back(item.second);
    }
    return res;
}

int main()
{
    // 测试样例
    vector<string> strs = {"eat","tea","tan","ate","nat","bat"};
    vector<vector<string>> ans = groupAnagrams(strs);

    // 输出结果查看
    for(auto& group : ans)
    {
        for(auto& word : group)
        {
            cout << word << " ";
        }
        cout << endl;
    }
    return 0;
}
