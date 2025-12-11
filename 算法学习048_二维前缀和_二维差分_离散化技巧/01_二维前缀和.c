/*
=================================================================================
304. 二维区域和检索 - 矩阵不可变 (Range Sum Query 2D - Immutable)
### 测试链接: https://leetcode.cn/problems/range-sum-query-2d-immutable/description/

* 通俗题目描述:
给你一个由数字组成的二维矩阵 matrix。
你需要实现一个功能,能够快速计算出矩阵中任意一个"子矩形"范围内所有数字的总和.

* 输入告诉我们：
1. 这是一个"不可变"的矩阵(初始化后,里面的数字不会变).
2. 会有多次查询请求(sumRegion),所以每次都暴力遍历去加会超时,必须预处理.

* 查询参数:
给定左上角 (row1, col1) 和 右下角 (row2, col2),返回这块区域的和.

* 示例:
输入矩阵:
[
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

查询 sumRegion(2, 1, 4, 3) -> 返回红色矩形框的和 -> 8
查询 sumRegion(1, 1, 2, 2) -> 返回绿色矩形框的和 -> 11
查询 sumRegion(1, 2, 2, 4) -> 返回蓝色矩形框的和 -> 12
=================================================================================
*/

#include <stdlib.h>

typedef struct
{
    int **sum; // 核心仓库:存储二维前缀和 (比原矩阵大一圈)
    int row;   // 辅助信息:记录行数 (m+1),释放内存时遍历用
    int col;   // 辅助信息:记录列数
} NumMatrix;

NumMatrix *numMatrixCreate(int **matrix, int matrixSize, int *matrixColSize)
{
    // 1. 获取矩阵尺寸
    int m = matrixSize;
    int n = matrixColSize[0];

    // 2. 初始化结构体
    NumMatrix *obj = (NumMatrix *)malloc(sizeof(NumMatrix));
    obj->row = m + 1; // 记录 m+1 行,因为我们会有哨兵行
    obj->col = n + 1;

    // 3. 申请二维数组骨架 (m+1 行)
    obj->sum = (int **)malloc(sizeof(int *) * (m + 1));

    // 4. 申请每一行 (n+1 列) 并清零
    int i = 0;
    for (i = 0; i < m + 1; i++)
    {
        // 使用 calloc 自动初始化为 0,确保第 0 行/列是 0 (哨兵)
        obj->sum[i] = (int *)calloc(n + 1, sizeof(int));
    }

    int j = 0;
    // 5. 填值:将 matrix 搬运到 sum,整体向右下偏移 1 位
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            obj->sum[i + 1][j + 1] = matrix[i][j];
        }
    }

    // 6. 核心逻辑:原地计算二维前缀和
    // 公式:当前 = 上 + 左 - 左上 + 本身(已填入)
    for (i = 1; i < m + 1; i++)
    {
        for (j = 1; j < n + 1; j++)
        {
            obj->sum[i][j] += obj->sum[i - 1][j] + obj->sum[i][j - 1] - obj->sum[i - 1][j - 1];
        }
    }

    return obj; // 必须返回创建的对象指针
}

int numMatrixSumRegion(NumMatrix *obj, int a, int b, int c, int d)
{
    // 1. 坐标映射:输入 0-based -> 数组 1-based
    a++;
    b++;
    c++;
    d++;

    // 2. 容斥原理:大矩形 - 上半部 - 左半部 + 重叠部分
    // (a,b)是左上角，(c,d)是右下角
    return obj->sum[c][d] - obj->sum[c][b - 1] - obj->sum[a - 1][d] + obj->sum[a - 1][b - 1];
}

void numMatrixFree(NumMatrix *obj)
{
    if (obj == NULL)
        return;

    int i = 0;
    // 1. 由内而外释放:先释放每一行
    for (i = 0; i < obj->row; i++)
    {
        free(obj->sum[i]);
        obj->sum[i] = NULL; // 置空防止悬空指针
    }
    // 2. 释放指针数组
    free(obj->sum);
    obj->sum = NULL;

    // 3. 释放结构体本身
    free(obj);
    obj = NULL;
}
