#include <iostream>
#include <string>
using namespace std;

//判断是否是字母和数字
bool isAlphaNum(char c) {
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

//字母大写转小写
char toLowerAscii(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

bool isPalindrome(string s) {
    int left = 0;
    int right = s.size() - 1;
    while (left < right) {
        while (left < right && !isAlphaNum(s[left])) {
            left++;
        }
        while (left < right && !isAlphaNum(s[right])) {
            right--;
        }
        char lc = toLowerAscii(s[left]);
        char rc = toLowerAscii(s[right]);
        if (lc != rc) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

static void Check(string s, bool expect, const char *desc) {
    bool got = isPalindrome(s);
    cout << desc << "  s=\"" << s << "\"  expect=" << boolalpha << expect
         << "  got=" << got << "  " << (got == expect ? "PASS" : "FAIL") << endl;
}

int main() {
    Check("A man, a plan, a canal: Panama", true,  "样例1");
    Check("race a car",                   false, "样例2");
    Check(" ",                            true,  "样例3(全符号)");
    Check("",                             true,  "空串");
    Check("a",                            true,  "单字符");
    Check("aba",                          true,  "奇数长度回文");
    Check("abba",                         true,  "偶数长度回文");
    Check("abca",                         false, "不是回文");
    Check("Aa",                           true,  "大小写不敏感");
    Check("0P",                           false, "数字和字母不等");
    Check(".,",                           true,  "全是标点");
    Check("12321",                        true,  "纯数字回文");
    Check("ab_a",                         true,  "下划线被跳过");
    Check("a  b",                         false, "空格跳过但字母不同");
    return 0;
}
