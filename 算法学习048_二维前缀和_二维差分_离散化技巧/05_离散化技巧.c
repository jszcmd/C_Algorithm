/*
 * ======================================================================================
 * 题目：力场 / 祝福最强处 (LeetCode LCP 74 / 类似变种)
 * #### 测试链接: https://leetcode.cn/problems/xepqZ5/description/
 * 核心算法：坐标离散化 + 二维差分 + 二维前缀和
 * * 【修正点说明】
 * 1. 引入 <string.h> 以使用 memset.
 * 2. 修复 cmp_long 函数,防止 long 相减导致的 int 溢出.
 * 3. 增加 MAX 大小至 205,防止下标越界.
 * 4. 每次计算前清空全局 diff 数组.
 * ======================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // 【必须引入】用于 memset 清空数组

// 【配置项】
// 题目中 n 最大为 100,意味着最多有 200 个横坐标和 200 个纵坐标
// MAX 设为 205 是为了预留 buffer,防止差分操作时的 +1 越界
#define MAX 205

// 【全局差分数组】
// 存放在全局区,防止栈溢出.注意:每次使用前必须清零！
int diff[MAX][MAX];

// 【辅助函数 1】Long 类型比较函数
// 作用:用于 qsort 排序
// 注意:必须使用 > < 判断,不能直接相减,防止 long 类型溢出导致 int 截断错误
int cmp_long(const void *e1, const void *e2)
{
    long v1 = *(long *)e1;
    long v2 = *(long *)e2;
    if (v1 > v2)
        return 1;
    if (v1 < v2)
        return -1;
    return 0;
}

// 【辅助函数 2】排序并去重 (离散化核心 1)
// 作用:对坐标数组进行排序,并移除重复元素
// 返回值:去重后的有效长度 size
int sort(long nums[], int len)
{
    // 1. 快速排序
    qsort(nums, len, sizeof(nums[0]), cmp_long);

    // 2. 双指针去重
    int size = 1;
    for (int i = 1; i < len; i++)
    {
        // 如果当前数和前一个有效数不同,则收录
        if (nums[i] != nums[size - 1])
        {
            nums[size++] = nums[i];
        }
    }
    return size;
}

// 【辅助函数 3】二分查找排名 (离散化核心 2)
// 作用:查找数值 v 在有序数组 nums 中的排名（下标+1）
// 算法:二分查找 (Binary Search),时间复杂度 O(log N)
int rank(long nums[], long v, int size)
{
    int l = 0;
    int r = size - 1;
    int m = 0;
    int ans = 0;

    // 查找 >= v 的第一个位置（其实题目场景下一定能找到等于 v 的）
    while (l <= r)
    {
        m = (l + r) / 2;
        if (nums[m] >= v)
        {
            ans = m;
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }
    // 返回 1-based 下标,方便差分数组使用(避免 0 下标减法越界)
    return ans + 1;
}

// 【核心算法 1】二维差分更新
// 作用:在 O(1) 时间内,给矩阵区域 [(a,b), (c,d)] 的所有元素 +1
// a: 左边界下标, b: 下边界下标, c: 右边界下标, d: 上边界下标
void add(int diff[MAX][MAX], int a, int b, int c, int d)
{
    diff[a][b] += 1;         // 左下角：开始增加
    diff[c + 1][b] -= 1;     // 右下角右侧：消除 X 轴影响
    diff[a][d + 1] -= 1;     // 左上角上方：消除 Y 轴影响
    diff[c + 1][d + 1] += 1; // 右上角右上方：补回重复减去的部分
}

// 【主函数】获取最大覆盖层数
int fieldOfGreatestBlessing(int **forceField, int forceFieldSize, int *forceFieldColSize)
{
    // 1. 【初始化】非常重要！
    // OJ 可能会复用进程，不清空会导致上个用例的数据残留
    memset(diff, 0, sizeof(diff));

    int n = forceFieldSize; // 力场个数

    // 2. 【收集坐标】
    // 物理坐标可能很大 (e.g., 10^9) 或者是小数 (x-0.5)
    // 技巧：使用 (coord << 1) 即乘以 2,将 .5 的小数问题转化为整数处理
    long xs[n * 2];
    long ys[n * 2];

    for (int i = 0, k = 0, p = 0; i < n; i++)
    {
        long x = forceField[i][0];
        long y = forceField[i][1];
        long r = forceField[i][2];

        // 计算物理边界：2*x - r 和 2*x + r
        xs[k++] = (x << 1) - r; // 收集 X 左边界
        xs[k++] = (x << 1) + r; // 收集 X 右边界
        ys[p++] = (y << 1) - r; // 收集 Y 下边界
        ys[p++] = (y << 1) + r; // 收集 Y 上边界
    }

    // 3. 【离散化】排序并去重
    // 将稀疏的巨大坐标映射为紧凑的数组下标 1, 2, 3...
    int sizex = sort(xs, n * 2);
    int sizey = sort(ys, n * 2);

    // 4. 【执行差分】
    // 遍历每个力场,将其物理坐标转化为离散下标,并在 diff 数组上打标记
    for (int i = 0, a, b, c, d; i < n; i++)
    {
        long x = forceField[i][0];
        long y = forceField[i][1];
        long r = forceField[i][2];

        // 核心映射:物理值 -> rank -> 矩阵下标
        a = rank(xs, (x << 1) - r, sizex); // 左边界下标
        b = rank(ys, (y << 1) - r, sizey); // 下边界下标
        c = rank(xs, (x << 1) + r, sizex); // 右边界下标
        d = rank(ys, (y << 1) + r, sizey); // 上边界下标

        // 在离散化后的网格上进行覆盖
        add(diff, a, b, c, d);
    }

    // 5. 【二维前缀和】还原真实数值
    int ans = 0;
    // 遍历所有有效的离散点
    // 注意：i, j 从 1 开始，循环到 size+1 是为了处理差分边界 c+1/d+1 的情况
    for (int i = 1; i < sizex + 2; i++)
    {
        for (int j = 1; j < sizey + 2; j++)
        {
            // 二维前缀和公式：当前 = 左 + 上 - 左上 + 差分值
            diff[i][j] += diff[i][j - 1] + diff[i - 1][j] - diff[i - 1][j - 1];

            // 记录最大重叠层数
            ans = (ans > diff[i][j]) ? ans : diff[i][j];
        }
    }

    return ans;
}
