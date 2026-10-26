#include <iostream>
#include <string>

using namespace std;

bool isAnagram(string s, string t) {
    if (s.length() != t.length()) {
        return false;
    }
    int cnt[26] = {0};
    for (size_t i = 0; i < s.length(); i++) {
        cnt[s[i] - 'a']++;
        cnt[t[i] - 'a']--;
    }
    for (int i = 0; i < 26; i++) {
        if (cnt[i] != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    cout << boolalpha;
    cout << "anagram / nagaram : " << isAnagram("anagram","nagaram") << "  (期望 true)"  << endl;
    cout << "rat / car         : " << isAnagram("rat","car")         << "  (期望 false)" << endl;
    cout << "a / a             : " << isAnagram("a","a")             << "  (期望 true)"  << endl;
    cout << "ab / a            : " << isAnagram("ab","a")            << "  (期望 false，长度不同)" << endl;
    cout << "\"\" / \"\"           : " << isAnagram("","")            << "  (期望 true，都为空)" << endl;
    cout << "abc / cba         : " << isAnagram("abc","cba")         << "  (期望 true)"  << endl;
    cout << "aacc / ccac       : " << isAnagram("aacc","ccac")       << "  (期望 false)" << endl;
    return 0;
}