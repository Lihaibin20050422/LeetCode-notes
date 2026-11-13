#include <iostream>
#include <string>
using namespace std;

int strStr(string haystack, string needle) {
    int n = haystack.size();
    int m = needle.size();
    int i = 0;
    int j = 0;
    while (i < n && j < m) {
        if (haystack[i] == needle[j]) {
            i++;
            j++;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == m) {
        return i - j;
    }
    return -1;
}

static void Check(string haystack, string needle, int expect, const char *desc) {
    int got = strStr(haystack, needle);
    cout << desc << "  haystack=\"" << haystack << "\" needle=\"" << needle
         << "\"  expect=" << expect << "  got=" << got
         << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check("sadbutsad", "sad", 0, "样例1");
    Check("leetcode", "leeto", -1, "样例2");
    Check("abcabcx", "abcxz", -1, "部分匹配后失配（真不存在）");
    Check("abcabcx", "abcx", 3, "存在但靠后（我一开始把期望写错了）");
    Check("abcabcx", "abc", 0, "开头匹配");
    Check("hello", "ll", 2, "中间匹配");
    Check("a", "a", 0, "单字符匹配");
    Check("a", "b", -1, "单字符不匹配");
    Check("aaa", "aaaa", -1, "needle 比 haystack 长");
    Check("mississippi", "issip", 4, "经典样例");
    Check("abc", "", 0, "空 needle");
    Check("", "", 0, "两个都空");
    Check("aabaaabaaac", "aabaaac", 4, "需要完整回溯");
    return 0;
}
