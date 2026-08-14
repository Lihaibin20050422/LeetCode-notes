# 14.longestCommonPrefix(最长公共前缀)

## 题目
编写一个函数来查找字符串数组中的最长公共前缀。
如果不存在公共前缀，返回空字符串 ""。
示例 1：
输入：strs = ["flower","flow","flight"]
输出："fl"

示例 2：
输入：strs = ["dog","racecar","car"]
输出：""
解释：输入不存在公共前缀。

## 思路

**水平扫描法**：拿第一个字符串当作"候选前缀"，然后逐个和后面的字符串比较。

1. 如果候选前缀是当前字符串的开头（`find(prefix) == 0`），说明它俩前面对得上，继续比下一个字符串；
2. 如果不是开头，就把候选前缀的**最后一个字符去掉**（`pop_back`），再比一次；
3. 反复缩短，直到候选前缀变成当前字符串的前缀，或者缩短成空串（说明没有公共前缀，直接返回 `""`）。

用一个例子理解：

```
prefix = "flower"
和 "flow" 比：不是前缀 → "flowe" → "flow" ✓（成了 "flow" 的前缀）
和 "flight" 比：不是前缀 → "flo" → "fl" ✓（成了 "flight" 的前缀）
最终返回 "fl"
```

## 代码
```cpp
class Solution {
public:
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
};
```

## 复杂度

- 时间：$O(S)$，其中 $S$ 是所有字符串的字符总数。最坏情况是每个字符串都相同，需要把每个字符都比较一遍。
- 空间：$O(1)$，只用了 `prefix` 一个额外字符串（它最长为第一个字符串的长度，不算额外随输入增长）。

## 要点

- `find(prefix) != 0` 是判断"不是前缀"的关键：`find` 返回子串首次出现的位置，返回 `0` 说明从开头就匹配上了，即 prefix 是它的前缀。
- 每次只去掉一个字符（`pop_back`），保证不跳过任何可能的公共前缀长度。
- 空数组直接返回 `""`，`prefix` 被缩短到空也要提前返回，这两个边界都要守住。