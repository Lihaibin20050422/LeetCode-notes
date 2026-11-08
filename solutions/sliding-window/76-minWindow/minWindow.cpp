#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

string minWindow(string s, string t) {
    vector<int> need(128);
    vector<int> window(128);
    for(char c : t){
        need[c]++;
    }
    int countType = 0;
    for(int i = 0; i < 128; i++){
        if(need[i] > 0){
            countType++;
        }
    }
    int left = 0;
    int right = 0;
    int valid = 0;
    int start = 0;
    int minLen = INT_MAX;
    while(right < s.size()){
        char c = s[right];
        right++;
        if(need[c] > 0){
            window[c]++;
            if(window[c] == need[c]){
                valid++;
            }
        }
        while(valid == countType){
            if(right - left < minLen){
                minLen = right - left;
                start = left;
            }
            char d = s[left];
            left++;
            if(need[d] > 0){
                if(window[d] == need[d]){
                    valid--;
                }
                window[d]--;
            }
        }
    }
    return minLen == INT_MAX ? "" : s.substr(start, minLen);
}

static void Check(string s, string t, string expect, const char *desc) {
    string got = minWindow(s, t);
    cout << desc << "  s=\"" << s << "\" t=\"" << t << "\"  expect=\"" << expect
         << "\"  got=\"" << got << "\"  " << (got == expect ? "PASS" : "FAIL") << endl;
}

int main() {
    Check("ADOBECODEBANC", "ABC", "BANC", "样例1");
    Check("a", "a", "a", "单字符");
    Check("a", "aa", "", "t 数量不够");
    Check("aa", "aa", "aa", "全都要");
    Check("ab", "b", "b", "只要一个字符");
    Check("a", "b", "", "字符不存在");
    Check("abc", "cba", "abc", "整串才够");
    Check("cabwefgewcwaefgcf", "cae", "cwae", "样例2");
    Check("abcabc", "abc", "abc", "多个同长度窗口");
    Check("ab", "a", "a", "取最短");
    Check("bba", "ab", "ba", "窗口在中间");
    return 0;
}
