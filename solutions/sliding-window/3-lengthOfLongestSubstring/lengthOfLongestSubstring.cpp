#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> idx;      // 字符 -> 最近一次出现的下标
    int maxLen = 0;
    int left = 0;
    int n = (int)s.size();
    for (int right = 0; right < n; right++) {
        char c = s[right];
        // 只有当"上一次出现"确实还在当前窗口内，才需要跳
        if (idx.find(c) != idx.end() && idx[c] >= left) {
            left = idx[c] + 1;
        }
        idx[c] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

static void Check(const string &s, int expect, const char *desc) {
    int got = lengthOfLongestSubstring(s);
    cout << desc << "  s=\"" << s << "\"  expect=" << expect
         << "  got=" << got << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check("abcabcbb", 3, "样例1");
    Check("bbbbb", 1, "样例2");
    Check("pwwkew", 3, "样例3");
    Check("", 0, "空串");
    Check("abba", 2, "关键：左指针不能回头");
    Check("tmmzuxt", 5, "关键：重复字符早已滑出窗口");
    Check("dvdf", 3, "重复后窗口重建");
    Check(" ", 1, "空格字符");
    Check("au", 2, "两个不同字符");
    Check("aab", 2, "开头重复");
    Check("abcdefghijklmnopqrstuvwxyz", 26, "26 个不重复");
    return 0;
}
