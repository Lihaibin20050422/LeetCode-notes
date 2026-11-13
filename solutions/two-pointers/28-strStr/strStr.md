# 28. 找出字符串中第一个匹配项的下标

## 题目

给定两个字符串 `haystack` 和 `needle`，在 `haystack` 中找到 `needle` 第一次出现的下标；不存在返回 `-1`。
`needle` 为空时返回 `0`。

示例：`haystack = "sadbutsad", needle = "sad"` → `0`

## 思路：朴素匹配（BF 算法）

用两个指针：`i` 扫主串，`j` 扫模式串。

- 字符相同 → 两个都前进；
- 字符不同 → **主串指针退回本次匹配起点的下一位**，模式串归零：

```cpp
i = i - j + 1;   // i 已经走了 j 步，减回去再 +1
j = 0;
```

匹配成功的判据是 **`j` 走完了模式串**（`j == m`），此时起点是 `i - j`。

## 代码

```cpp
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
```

## 复杂度

- 时间 **$O(n \times m)$**（最坏情况，如 `haystack = "aaaaa"`, `needle = "aaab"`）
- 空间 $O(1)$

## 要点

### 1. 这就是 408 串章节的“简单匹配算法”

王道书里的朴素模式匹配就是这个。**考试让你写“串的模式匹配”，朴素算法是完全合格的答案。**

KMP 的作用，就是把失配时的这两行优化掉：

| | 朴素匹配 | KMP |
|---|---|---|
| 失配时主串指针 | **回退到起点下一位** | **不回退** |
| 失配时模式串指针 | 归零 | 退到 `next[j]` |
| 复杂度 | $O(nm)$ | $O(n+m)$ |

### 2. 回溯公式别写错

`i = i - j + 1`，意思是：本次匹配从 `i - j` 开始，失败了就从 `i - j + 1` 重新试。

写成 `i = i + 1` 会漏掉重叠的匹配（比如 `"aabaaabaaac"` 找 `"aabaaac"`）。

### 3. 边界

| 情况 | 结果 |
|---|---|
| `needle` 为空 | `0`（`j == m == 0`，直接返回 `i - j = 0`）|
| `needle` 比 `haystack` 长 | `-1` |
| 完全不匹配 | `-1` |

## 相关题目

- 459. 重复的子字符串（KMP 的 next 数组应用）
- 214. 最短回文串（KMP 变形）
- 686. 重复叠加字符串匹配
