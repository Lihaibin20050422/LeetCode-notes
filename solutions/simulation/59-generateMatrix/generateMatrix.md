# 59. 螺旋矩阵 II

## 题目

给你一个正整数 `n`，生成一个包含 `1` 到 `n²` 所有元素，且元素按**顺时针螺旋顺序**排列的 `n × n` 矩阵。

示例：`n = 3` →
```
[[1,2,3],
 [8,9,4],
 [7,6,5]]
```

## 思路：54 题的同一副骨架，只是"读"换成"写"

```cpp
for (int i = left; i <= right; i++)
    res[top][i] = num++;
```

四个边界 `top / bottom / left / right`，每走完一条边收缩一格——**和 54 完全一致**。

唯一的区别：

| | 54 螺旋矩阵 | **59 螺旋矩阵 II** |
|---|---|---|
| 动作 | `res.push_back(matrix[top][i])` | **`res[top][i] = num++`** |
| 循环变量 | 读 | **写 + 计数器** |

## 代码

```cpp
vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> res(n, vector<int>(n));
    int count = n * n;
    int top = 0, bottom = n - 1, left = 0, right = n - 1;
    int num = 1;
    while (count > 0) {
        for (int i = left; i <= right && count > 0; i++) res[top][i] = num++, count--;
        top++;
        for (int i = top; i <= bottom && count > 0; i++) res[i][right] = num++, count--;
        right--;
        for (int i = right; i >= left && count > 0; i--) res[bottom][i] = num++, count--;
        bottom--;
        for (int i = bottom; i >= top && count > 0; i--) res[i][left] = num++, count--;
        left++;
    }
    return res;
}
```

## 复杂度

- 时间 $O(n^2)$：每个格子填一次
- 空间 $O(1)$ 额外（返回的矩阵本身是 $O(n^2)$）

## 要点

### 1. 一个"差一"隐患：`count >= 0` 要改成 `count > 0`

原来的写法用的是 `count >= 0`：

```cpp
for (int i = left; i <= right && count >= 0; i++)   // 危险
```

**当 `count` 恰好减到 0 时，`count >= 0` 仍然为真**——如果此时循环变量还没碰到边界，就会多写一个数（`num` 会写成 $n^2+1$）。

本题因为"最后一个格子永远是某条边的末端"，**碰巧不会触发**。但这属于**依赖题目形状的巧合**，不是安全写法。

> **正确写法是 `count > 0`**。你在 54 题用的是 `> 0`，这里写成了 `>= 0`——**同一个守卫，两处标准不一。**

### 2. 方阵其实可以不要 `count`

因为 `n × n` 方阵里，"单行/单列"的情况不存在，四个边界收缩后自然全部失效，**不会重复写**。

但保留 `count` 也没坏处——**它是"提前退出"的保险**，尤其改动代码时。

### 3. 中心格怎么被填上的

`n` 为奇数时，最内圈只剩中心一个格子：

- `top == bottom == left == right` 时，第一条边（L→R）就填了它
- 填完后 `top++`，后面三条边全部条件不成立

**所以奇数阶的中心格，是被第一条边"顺手"填掉的，不用特殊处理。**

### 4. 和 54 的对照记忆表

| | 54 | **59** |
|---|---|---|
| 输入 | m×n 矩阵 | **整数 n** |
| 方向 | 同 | 同 |
| 边界收缩 | 同 | 同 |
| 特殊处理 | **需要**（单行单列会重复读） | **不需要**（方阵没有单行） |

## 相关题目

- 54. 螺旋矩阵（读取版）
- 48. 旋转图像（矩阵变换）
- 498. 对角线遍历
- 885. 螺旋矩阵 III
