# 54. 螺旋矩阵

## 题目

给定一个 `m × n` 的矩阵，按**顺时针螺旋顺序**返回其中所有元素。

示例：`[[1,2,3],[4,5,6],[7,8,9]]` → `[1,2,3,6,9,8,7,4,5]`

## 思路：四个边界，走一圈收缩一次

维护四个边界：

```
top    上边界（未走的行）
bottom 下边界
left   左边界
right  右边界
```

每一圈按四个方向走：

1. **左 → 右**：沿 `top` 行，从 `left` 到 `right`；然后 `top++`
2. **上 → 下**：沿 `right` 列，从 `top` 到 `bottom`；然后 `right--`
3. **右 → 左**：沿 `bottom` 行，从 `right` 到 `left`；然后 `bottom--`
4. **下 → 上**：沿 `left` 列，从 `bottom` 到 `top`；然后 `left++`

**每走完一条边，对应的边界就收缩一格。**

### 单行 / 单列：这是唯一的坑

```
只有一行：[1,2,3]
  L→R 走完 → top++ → 后面三条边都"没东西可走"
```

如果四条边无条件执行，**"右→左"会把同一行再走一遍**，结果重复。

**两种解决办法：**

| 写法 | 做法 |
|---|---|
| **A（你的写法）** | 用剩余数量 `count`，每条边里加 `&& count > 0` |
| B | 每条边之间判 `if (top > bottom) break;` |

**两种都对。A 更直观：数够了就停。**

## 代码

```cpp
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> res;
    if(matrix.empty()){
        return res;
    }
    int m = matrix.size();
    int n = matrix[0].size();
    int count = m * n;
    int top = 0;
    int bottom = m - 1;
    int left = 0;
    int right = n - 1;
    while(count > 0){
        for(int i = left; i <= right && count > 0; i++){
            res.push_back(matrix[top][i]);
            count--;
        }
        top++;
        for(int i = top; i <= bottom && count > 0; i++){
            res.push_back(matrix[i][right]);
            count--;
        }
        right--;
        for(int i = right; i >= left && count > 0; i--){
            res.push_back(matrix[bottom][i]);
            count--;
        }
        bottom--;
        for(int i = bottom; i >= top && count > 0; i--){
            res.push_back(matrix[i][left]);
            count--;
        }
        left++;
    }
    return res;
}
```

## 复杂度

- 时间 $O(m \times n)$：每个元素访问一次
- 空间 $O(1)$ 额外（返回数组不算）

## 要点

### 1. 边界的含义要固定

> **`top` = 还没走过的第一行，`bottom` = 还没走过的最后一行。**

一旦定义清楚，"走完一条边就收缩一格"就是自然的事。

**千万别混成"已经走过的最后一行"**——那样 `top++` 还是 `top--` 就会搞反。

### 2. 四个循环的边界写法不同

| 方向 | 循环变量 | 结束条件 |
|---|---|---|
| 左→右 | `i` 在行上 | `i <= right` |
| 上→下 | `i` 在列上 | `i <= bottom` |
| 右→左 | `i` 递减 | `i >= left` |
| 下→上 | `i` 递减 | `i >= top` |

**注意第 2、4 个用的是 `top`/`bottom` 的当前值（已经 +1 或 -1 过）**，这正是"不重复走角"的原因。

### 3. 和 59（螺旋矩阵 II）的关系

**同一个骨架**，只是把"读出来"换成"写进去"（填 `1..n²`）。

> **54 会写，59 就是 10 分钟的事。**

### 4. 边界

| 输入 | 输出 |
|---|---|
| 空矩阵 | `[]` |
| `1 × n` | 顺序输出 |
| `m × 1` | 顺序输出 |
| `1 × 1` | 单个元素 |

## 相关题目

- 59. 螺旋矩阵 II（填充版，同一骨架）
- 48. 旋转图像（矩阵变换，另一类）
- 498. 对角线遍历（换一种走法）
- 885. 螺旋矩阵 III（从中间往外）
