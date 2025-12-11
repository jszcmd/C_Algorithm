/*
 * =================================================================================
 * 1139. 最大的以 1 为边界的正方形
 * ### 测试链接:https://leetcode.cn/problems/largest-1-bordered-square/description/
 * * 给你一个由若干 0 和 1 组成的二维网格 grid，请你找出边界全部由 1 组成的最大 正方形
 * 子网格，并返回该子网格中的元素数量。如果不存在，则返回 0。
 * * 示例 1：
 * 输入：grid = [[1,1,1],[1,0,1],[1,1,1]]
 * 输出：9
 * * 示例 2：
 * 输入：grid = [[1,1,0,0]]
 * 输出：1
 * * 提示：
 * 1 <= grid.length <= 100
 * 1 <= grid[0].length <= 100
 * grid[i][j] 为 0 或 1
 * =================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 辅助函数:安全获取数组元素,处理边界越界
int get(int **arr, int i, int j)
{
    if (i < 0 || j < 0)
        return 0;
    else
        return arr[i][j];
}

// 辅助函数:计算子矩形面积 (容斥原理)
int get_sum(int **arr, int a, int b, int c, int d)
{
    // 如果左上角坐标 > 右下角坐标 (用于处理 k=1 时的内部小矩形情况),返回 0
    if (a > c)
        return 0;
    return get(arr, c, d) - get(arr, c, b - 1) - get(arr, a - 1, d) + get(arr, a - 1, b - 1);
}

// 构造前缀和：grid[i][j] = 上 + 左 - 左上 + 原值
void build(int **arr, int m, int n)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            // 注意：这里是原地修改,arr[i][j] 初始值就是 arr[i][j]
            arr[i][j] += get(arr, i, j - 1) + get(arr, i - 1, j) - get(arr, i - 1, j - 1);
        }
    }
}

int largest1BorderedSquare(int **grid, int gridSize, int *gridColSize)
{
    int m = gridSize;
    int n = gridColSize[0];

    // 1. 原地构建二维前缀和
    build(grid, m, n);

    // 2. 特判:如果全为0,直接返回0
    if (get_sum(grid, 0, 0, m - 1, n - 1) == 0)
        return 0;

    int ans = 1; // 至少有一个 1,所以最小是 1

    // 3. 遍历每一个点做左上角 (a,b)
    for (int a = 0; a < m; a++)
    {
        for (int b = 0; b < n; b++)
        {
            // 4. 剪枝优化：直接从比当前最大边长 ans 大 1 的尺寸开始找
            // c, d 是右下角坐标; k 是当前尝试的边长
            for (int c = a + ans, d = b + ans, k = ans + 1; c < m && d < n; c++, d++, k++)
            {
                // 5. 核心判断: 大矩形面积 - 内部小矩形面积 == 边框理论面积 ((k-1)*4)
                // 大矩形面积: get_sum(grid, a, b, c, d)
                // 小矩形面积: get_sum(grid, a + 1, b + 1, c - 1, d - 1)
                if ((get_sum(grid, a, b, c, d) - get_sum(grid, a + 1, b + 1, c - 1, d - 1)) == (k - 1) << 2)
                    ans = k;
            }
        }
    }
    return ans * ans;
}
