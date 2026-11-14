# 15. 三数之和

## 题目

给你一个整数数组 `nums`，找出所有**和为 0** 且**不重复**的三元组 `[a,b,c]`。

示例：`[-1,0,1,2,-1,-4]` → `[[-1,-1,2], [-1,0,1]]`

## 思路：排序 + 固定一个数 + 两数之和

```
排序
for i in 0..n-3:            ← 固定第一个数
    用双指针在 i+1..n-1 里找两数，使 nums[left] + nums[right] == -nums[i]
```

**这题就是 167 套了一层循环。** 167 找"两数之和"，这题先固定一个数，剩下的就是"两数之和 = −nums[i]"。

### 排序带来两个好处

1. **双指针才能用**（和的大小有单调性）
2. **去重变简单**——相同的数排在一起，跳过邻居就行

## 三处去重（漏一处就重复）

| 位置 | 写法 | 为什么 |
|---|---|---|
| **① 固定的 `i`** | `if (i > 0 && nums[i] == nums[i-1]) continue;` | 同一个值当过"第一个数"，再当一次只会得到同一批答案 |
| **② `left`** | 找到答案后 `while (left < right && nums[left] == nums[left+1]) left++;` | 跳过后面相同的值，避免同一组答案再出现 |
| **③ `right`** | 同理，`nums[right] == nums[right-1]` 时 `right--` | 同上 |

**去重的本质：同一个位置上，相同的值只处理一次。**

## 代码

```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> res;
    if (n < 3) {
        return res;
    }

    sort(nums.begin(), nums.end());

    for (int i = 0; i < n - 2; i++) {
        if (nums[i] > 0) {
            break;                      // 最小的都 > 0，后面不可能凑出 0
        }
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;                   // ① 固定的数去重
        }

        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum == 0) {
                res.push_back({nums[i], nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1]) {
                    left++;             // ② 左指针去重
                }
                while (left < right && nums[right] == nums[right - 1]) {
                    right--;            // ③ 右指针去重
                }
                left++;
                right--;
            }
            else if (sum < 0) {
                left++;
            }
            else {
                right--;
            }
        }
    }
    return res;
}
```

## 复杂度

- 时间 **$O(n^2)$**：外层 n 次，内层双指针 O(n)
- 空间 $O(1)$ 额外（排序用 $O(\log n)$ 栈）

## 要点

### 1. 排序后 `nums[i] > 0` 可以提前 `break`

数组升序，`nums[i]` 是三元组里最小的那个。**它都大于 0 了，三个正数相加不可能是 0。** 后面都不用看了。

### 2. 去重时的 `left < right` 不能省

```cpp
while (left < right && nums[left] == nums[left + 1]) left++;
```

如果只剩两个相同的元素，没有 `left < right` 会一直加到 `left + 1` 越界。

### 3. 换个角度看：这是"两数之和"的推广

| 题 | 结构 |
|---|---|
| 1. 两数之和 | 枚举 1 个数？不——**用哈希** |
| 167. 两数之和 II | 排序后**双指针** |
| **15. 三数之和** | **固定 1 个 + 两数之和** |
| 18. 四数之和 | **固定 2 个 + 两数之和** |

**规律：多一层"固定"，就多一层循环，复杂度多一个 n。**

### 4. `int sum` 的溢出

本题约束 $|nums[i]| \le 10^5$，三数之和最大 $3\times10^5$，`int` 安全。
若数据范围更大，`sum` 要用 `long long`。

## 相关题目

- 167. 两数之和 II（本题的内层）
- 18. 四数之和（多固定一个数）
- 16. 最接近的三数之和（不求等于，求最接近）
- 259. 较小的三数之和
- 11. 盛最多水的容器（相向双指针的另一种）
