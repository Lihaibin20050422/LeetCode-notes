# 49.groupAnagrams(字母异位词分组)

## 题目
给你一个字符串数组，请你将**字母异位词**组合在一起。可以按**任意顺序**返回结果列表。
字母异位词：由相同字母重新排列形成的字符串。

示例:
输入: strs = ["eat","tea","tan","ate","nat","bat"]
输出: [["bat"],["nat","tan"],["ate","eat","tea"]]（顺序任意）

## 思路：给每个单词算一个"身份证"（归一化）

**核心问题**：怎么把"互为异位词"这个关系，转成"**key 相同**"？

异位词的共同点：**每个字母出现的次数相同**。
所以 key 只要能唯一表达"**字母的多重集合**"，异位词就会算出同一个 key。

### 做法一：排序法（本题写法）
把字符串排序 → 异位词排序后**完全相同**。
- `"eat"` / `"tea"` / `"ate"` → 都变成 `"aet"`
- 用排好序的串当 key，哈希表分组。

### 做法二：计数法（进阶，每个串 O(k)）
用 26 个字母的**计数**编码成字符串当 key，不用排序。

## 代码

**排序法**
```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (auto& s : strs) {
            string key = s;
            sort(key.begin(), key.end());   // 异位词 → 同一个 key
            mp[key].push_back(s);           // operator[] 自动建空组
        }
        vector<vector<string>> res;
        for (auto& item : mp) res.push_back(item.second);
        return res;
    }
};
```

**计数法**
```cpp
string keyOf(const string& s){
    int cnt[26] = {0};
    for (char c : s) cnt[c - 'a']++;
    string key;
    for (int i = 0; i < 26; i++) key += char(cnt[i]);   // 26 字节，无歧义
    return key;
}
// 主函数里把 key = s; sort(...) 换成 key = keyOf(s);
```

## 复杂度

| 做法 | 时间 | 空间 |
|---|---|---|
| 排序 | $O(n \cdot k\log k)$ | $O(nk)$ |
| **计数** | **$O(n \cdot k)$** | $O(nk)$ |

（n 个串，每个长 k）

## 要点

### 1. 归一化 / 规范形式（canonical form）

> **把"等价"编码成"相同"。**

**分组类问题的第一反应，就该是：能不能给每个元素算一个"身份证"？**
- 49 异位词：身份证 = 排序后的串 / 字母计数；
- 同源技术：**并查集**（每个元素找"代表元"）、哈希去重、集合的 hash…

**"判断相等" → "比较 key"**，是哈希类问题最核心的一步。

### 2. 排序法 vs 计数法
- **排序**：代码短、直观，$O(k\log k)$；
- **计数**：$O(k)$，长串更快，但编码不能有歧义（用 26 个定长字节，或加分隔符）。

### 3. `mp[key]` 在这里是"对的用法"

`operator[]` 查不到会**自动插入**一个空的 `vector`。
- 在 **1. Two Sum** 里，这个特性是**坑**（会凭空造键）；
- 在 **49** 里，它**正好是你要的**（自动建组）。

> **同一个特性，看场景用。** 这就是"知道原理"和"背口诀"的区别。

### 4. 结果组的顺序不保证
`unordered_map` 的遍历顺序是**无序**的，所以组的先后是乱的。
**LC 接受任意顺序**，所以不用慌。

## 相关题目
- 242. 有效的字母异位词（只判断两个串）
- 128. 最长连续序列
- 1. 两数之和（`operator[]` 的反面教材）
