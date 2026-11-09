# 125. 验证回文串

## 题目

给定一个字符串，只考虑**字母和数字**，忽略大小写，判断它是否为回文串。

示例：`"A man, a plan, a canal: Panama"` → `true`；`"race a car"` → `false`

## 思路：相向双指针 + 跳过无效字符

两个指针从两端往中间靠：

1. 左指针跳过所有**非字母数字**的字符；
2. 右指针同样跳过；
3. 两边都停在有效字符上时，**统一转小写后比较**；
4. 不相同 → `false`；相同 → 两边各走一步，继续。

## 代码

```cpp
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
```

## 复杂度

- 时间 $O(n)$：每个字符最多被两个指针各访问一次
- 空间 $O(1)$

## 要点

### 1. 内层 `while` 必须带 `left < right`

```cpp
while (left < right && !isAlphaNum(s[left])) { left++; }
```

少了 `left < right`，遇到 `".,"` 这种全标点的串，`left` 会一路滑到 `s.size()`，**越界读**。
`right` 同理。

> **双指针的第一条纪律：任何一步移动，都不能跨过对方。**

### 2. 为什么不用 `isalnum` / `tolower`

`<cctype>` 里确实有现成的，但：
- `isalnum` 传负的 `char`（非 ASCII 字节）是未定义行为，要转 `unsigned char`
- 408 手写题里自己写三行更稳，也不依赖头文件

**手写这两个小函数，是刻意为之，不是重复造轮子。**

### 3. 边界

| 输入 | 结果 | 说明 |
|---|---|---|
| `""` | `true` | 空串按回文处理 |
| `" "` / `".,"` | `true` | 没有有效字符，视为回文 |
| `"a"` | `true` | 单字符 |
| `"0P"` | `false` | 数字和字母不相等 |

### 4. 一个 C++ 的坑

`int right = s.size() - 1;` 中，`s.size()` 是 `size_t`：
空串时 `0 - 1` 会回绕成极大值，再转成 `int` 通常得到 `-1`——此时 `left < right` 为假，循环不进，**碰巧返回正确答案**。

**结果对，但依赖了实现定义的转换。** 更稳的写法：`int right = (int)s.size() - 1;`（本题空串时结果不变，但换成别的题可能出事）。

## 相关题目

- 344. 反转字符串（相向双指针的最基础形态）
- 345. 反转字符串中的元音字母（跳过无效 + 交换）
- 680. 验证回文串 II（允许删一个字符）
- 234. 回文链表（快慢指针找中点 + 反转后半）
- 167. 两数之和 II（相向双指针的另一种触发条件）
