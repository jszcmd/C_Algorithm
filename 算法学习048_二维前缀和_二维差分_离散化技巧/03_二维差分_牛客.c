/*
 * ======================================================================================
 * 题目: 矩阵子区域更新 (二维差分模板题)
 * #### 测试链接: https://www.nowcoder.com/practice/50e1a93989df42efb0b1dec386fb4ccc
 * * 【题目描述】
 * 给定一个 n * m 的整数矩阵 origin,下标从 1 开始。
 * 需要执行 q 次操作.
 * 每次操作给定 5 个整数 x1, y1, x2, y2, k.
 * 表示将以 (x1, y1) 为左上角、(x2, y2) 为右下角的子矩阵内所有元素增加 k.
 * (k 可以是负数,表示减少)
 * 请输出所有操作执行完毕后的最终矩阵.
 * * 【数据范围】
 * 1 <= n, m <= 1000
 * 1 <= q <= 100000
 * -10^9 <= 初始数值, k <= 10^9  (意味着结果可能超过 int 范围,需用 long long)
 * ======================================================================================
 */

#include <stdio.h>
#include <string.h>

#define MAX 1002 // 最大尺寸,预留边界防止越界

int origin[MAX][MAX]; // 原始矩阵
long diff[MAX][MAX];  // 差分数组 (long 防止累加溢出)

int n, m, q; // n行, m列, q次操作

// 二维差分更新:O(1) 时间标记子矩阵增减
void add(int a, int b, int c, int d, int v)
{
    diff[a][b] += v;
    diff[c + 1][b] -= v;
    diff[a][d + 1] -= v;
    diff[c + 1][d + 1] += v;
}

// 二维前缀和:O(nm) 将差分标记还原为实际变化量
void build()
{
    int i = 0;
    int j = 0;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            // 递推公式:当前 = 左 + 上 - 左上 + 差分值
            diff[i][j] += diff[i][j - 1] + diff[i - 1][j] - diff[i - 1][j - 1];
        }
    }
}

// 清空数组 (可选)
void clear()
{
    memset(diff, 0, sizeof(diff));
}

int main()
{
    // 1. 读取矩阵大小和操作次数
    if (scanf("%d %d %d", &n, &m, &q) != 3)
        return 0;

    int i = 0;
    int j = 0;

    // 2. 读取原始矩阵数据
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            scanf("%d", &origin[i][j]);
        }
    }

    // 3. 处理 q 次差分操作
    for (i = 0; i < q; i++)
    {
        int a, b, c, d, v;
        scanf("%d %d %d %d %d", &a, &b, &c, &d, &v);
        add(a, b, c, d, v);
    }

    // 4. 计算前缀和，还原每个位置的变化量
    build();

    // 5. 输出结果：最终值 = 原始值 + 变化量
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            printf("%ld ", origin[i][j] + diff[i][j]); // 注意空格分隔
        }
        printf("\n"); // 每行结束后换行
    }

    clear();

    return 0;
}
