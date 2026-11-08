#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

string minWindow(string s, string t) {
    vector<int> need(128, 0), window(128, 0);
    for (char c : t) need[c]++;

    int countType = 0;                       // t 中有多少种字符
    for (int i = 0; i < 128; i++) {
        if (need[i] > 0) countType++;
    }

    int left = 0, valid = 0, start = 0, minLen = INT_MAX;
    int n = (int)s.size();
    for (int right = 0; right < n; right++) {
        char c = s[right];                   // 右端扩张
        if (need[c] > 0) {
            window[c]++;
            if (window[c] == need[c]) valid++;   // 这种字符刚刚凑够
        }

        while (valid == countType) {         // 全部凑够 → 试着缩
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                start = left;
            }
            char d = s[left];                // 左端收缩
            if (need[d] > 0) {
                if (window[d] == need[d]) valid--;   // 这种字符马上不够了
                window[d]--;
            }
            left++;
        }
    }
    return minLen == INT_MAX ? "" : s.substr(start, minLen);
}

static void Check(const string &s, const string &t, const string &expect, const char *desc) {
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
