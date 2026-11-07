#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> findAnagrams(string s, string p) {
    vector<int> res;
    int n = (int)s.size();
    int m = (int)p.size();
    if (m > n) return res;

    vector<int> cnt_p(26, 0), cur(26, 0);   // 只处理小写字母
    for (int i = 0; i < m; i++) cnt_p[p[i] - 'a']++;
    for (int i = 0; i < m; i++) cur[s[i] - 'a']++;

    if (cnt_p == cur) res.push_back(0);

    for (int left = 1; left <= n - m; left++) {
        cur[s[left - 1] - 'a']--;          // 左端滑出
        cur[s[left + m - 1] - 'a']++;      // 右端滑入
        if (cnt_p == cur) res.push_back(left);
    }
    return res;
}

static void Print(const vector<int> &v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << (i + 1 < v.size() ? "," : "");
    cout << "]";
}

static void Check(const string &s, const string &p, const vector<int> &expect, const char *desc) {
    vector<int> got = findAnagrams(s, p);
    cout << desc << "  s=\"" << s << "\" p=\"" << p << "\"  expect=";
    Print(expect);
    cout << "  got=";
    Print(got);
    cout << (got == expect ? "  PASS" : "  FAIL") << endl;
}

int main() {
    Check("cbaebabacd", "abc", {0, 6}, "样例1");
    Check("abab", "ab", {0, 1, 2}, "样例2");
    Check("a", "a", {0}, "长度相等且匹配");
    Check("a", "ab", {}, "p 比 s 长");
    Check("aa", "a", {0, 1}, "单字符多次出现");
    Check("abc", "cba", {0}, "只有一个窗口");
    Check("baa", "aa", {1}, "窗口在中间");
    Check("aabb", "ab", {1}, "只有中间是异位词");
    Check("abcdefg", "abc", {0}, "只在开头");
    Check("aaa", "aa", {0, 1}, "全同字符");
    Check("ababab", "abab", {0, 1, 2}, "长窗口滑动(全命中)");
    Check("ababac", "abab", {0, 1}, "长窗口滑动(末尾不是)");
    return 0;
}
