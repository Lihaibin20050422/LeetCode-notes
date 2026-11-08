# 76. 最小覆盖子串

## 题目

给你两个字符串 `s` 和 `t`。返回 `s` 中涵盖 `t` 所有字符的**最短子串**；不存在则返回 `""`。
`t` 中的重复字符必须在窗口里同样满足数量。

示例：`s = "ADOBECODEBANC", t = "ABC"` → `"BANC"`

## 思路：变长窗口 + 频率表 + "已满足的字符种数"

三个"指针"同时维护：

| 变量 | 含义 |
|---|---|
| `need[c]` | `t` 中字符 `c` 需要几个 |
| `window[c]` | 当前窗口里 `c` 有几个 |
| **`valid`** | **窗口里已经"凑够数量"的字符有几种** |
| `countType` | `t` 里有几种不同的字符 |

流程：

1. **右端扩张**：字符进窗，若 `window[c] == need[c]`，`valid++`；
2. **只要 `valid == countType`**（全部凑齐）：先更新答案，再**左端收缩**；
3. 收缩时，若某个字符的 `window[d] == need[d]`，说明马上要不够了 → `valid--`。

## 代码

```cpp
string minWindow(string s, string t) {
    vector<int> need(128, 0), window(128, 0);
    for (char c : t) need[c]++;

    int countType = 0;
    for (int i = 0; i < 128; i++)
        if (need[i] > 0) countType++;

    int left = 0, valid = 0, start = 0, minLen = INT_MAX;
    int n = (int)s.size();
    for (int right = 0; right < n; right++) {
        char c = s[right];
        if (need[c] > 0) {
            window[c]++;
            if (window[c] == need[c]) valid++;
        }

        while (valid == countType) {          // 全部凑够 → 试着缩
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                start = left;
            }
            char d = s[left];
            if (need[d] > 0) {
                if (window[d] == need[d]) valid--;
                window[d]--;
            }
            left++;
        }
    }
    return minLen == INT_MAX ? "" : s.substr(start, minLen);
}
```

## 复杂度

- 时间 $O(|s| + |t| + 128)$：左右指针各走一遍，每个字符进出窗口各一次
- 空间 $O(128)$

## 要点

### 1. 为什么 `valid` 记"种数"，不记"总字符数"

因为判断"是否覆盖"的本质是**每一种字符都够了**，而不是"总共有多少个"。
记种数，就能用 `valid == countType` 一次判断，不用每次扫 128 个格子。

### 2. `window[c]` 可以超过 `need[c]`，不影响正确性

多出来的字符只是冗余，覆盖依然成立。
等它被缩到 `== need[c]` 时，`valid` 保持不变（它早已算作"满足"）；
只有从 `== need[c]` 再减一个，才会 `valid--`。

> 代码里用 `if (window[d] == need[d]) valid--;` **在减之前判断**，就是为这个。

### 3. 更新答案的时机，决定了这是"最短"还是"最长"

| 题 | 求什么 | 在哪里更新答案 |
|---|---|---|
| 3. 无重复最长子串 | **最长** | **每次扩张后** |
| 76. 最小覆盖子串 | **最短** | **刚满足条件时**，缩之前 |

**要最长 → 尽量撑大；要最短 → 一满足就记，然后马上缩。**

### 4. 这是模板题，可以覆盖一串题

同一副骨架（`need` / `window` / `valid`）能解决：

- 3. 无重复字符的最长子串（`valid` 换成"窗口内无重复"的判断）
- 438. 找到所有字母异位词（**固定窗口**版本）
- 567. 字符串的排列（438 的判定版）
- 76. 最小覆盖子串（本题）

### 5. 边界

| 情况 | 结果 |
|---|---|
| `|s| < |t|` | `""`（自然走完，`minLen` 仍为 `INT_MAX`） |
| 不存在覆盖 | `""` |
| `t` 含重复字符 | 靠 `need[c]` 的数量约束，不用特判 |

> **前提**：本题保证 `t` 非空、只含英文字母。若 `t` 为空，`countType = 0`，收缩循环会失控——这是这个写法唯一需要假设的地方。

## 相关题目

- 438. 找到字符串中所有字母异位词（固定窗口 + 同样的频率表）
- 567. 字符串的排列
- 3. 无重复字符的最长子串
- 209. 长度最小的子数组（求和版的最小窗口）
- 30. 串联所有单词的子串（把"字符"换成"单词"）
