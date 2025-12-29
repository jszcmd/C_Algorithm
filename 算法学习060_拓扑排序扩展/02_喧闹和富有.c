/*
 * 题目:851. 喧闹和富有 (Loud and Rich)
 * 来源:LeetCode
 * #### 测试链接: https://leetcode.cn/problems/loud-and-rich/description/
 *
 * 题目描述:
 * 有一组 n 个人作为实验对象,从 0 到 n - 1 编号,其中每个人都有不同数目的钱,
 * 以及不同程度的安静值 (quietness).
 * * 给你一个数组 richer，其中 richer[i] = [ai, bi] 表示 person ai 比 person bi 更有钱.
 * 另给你一个整数数组 quiet,其中 quiet[i] 是 person i 的安静值.
 * richer 中所给出的数据 逻辑自洽 (也就是说,在 person x 比 person y 更有钱的同时,
 * 不会出现 person y 比 person x 更有钱的情况 ).
 *
 * 现在,返回一个整数数组 answer 作为答案,其中 answer[x] = y 的前提是:
 * 在所有拥有的钱肯定不少于 person x 的人中，person y 是最安静的人(也就是安静值 quiet[y] 最小的人).
 *
 * 示例 1:
 * 输入:richer = [[1,0],[2,1],[3,1],[3,7],[4,3],[5,3],[6,3]], quiet = [3,2,5,4,6,1,7,0]
 * 输出:[5,5,2,5,4,5,6,7]
 *
 * 提示:
 * n == quiet.length
 * 1 <= n <= 500
 * 0 <= quiet[i] < n
 * quiet 的所有值 互不相同
 * 0 <= richer.length <= n * (n - 1) / 2
 */

#include <stdio.h>  // 使用NULL;
#include <stdlib.h> // 使用malloc()函数
#include <string.h> // 使用memeset()函数
#define MAX 501     // 定义最大节点数,实际上我们0位置的也用

// 声明边的结构体:链表中的每一个节点代表一条边
struct EdgeNode
{
    int to;                // 这条边的终点节点编号
    struct EdgeNode *next; // 指向该起点引出的下一条边的指针
};

typedef struct EdgeNode EdgeNode; // 简化类型定义

EdgeNode *adjList[MAX]; // 邻接表全局变量:指针数组,数组的每个下标代表图的一个节点

// 初始化邻接表并释放内存
void build(int n)
{
    for (int i = 0; i <= n; i++) // 遍历每一个节点的边链表,0位置也使用(也要初始化)
    {
        EdgeNode *cur = adjList[i]; // cur 指向当前节点的链表头
        while (cur)                 // 循环直到链表末尾
        {
            EdgeNode *tmp = cur; // 暂存当前节点指针
            cur = cur->next;     // 指针后移到下一个边节点
            free(tmp);           // 释放当前动态申请的结构体内存
        }
        adjList[i] = NULL; // 将该节点的表头指针归零,防止野指针
    }
}

// 向图中添加一条单向边 (u -> v)
void addListEdge(int u, int v)
{
    EdgeNode *newNode = (EdgeNode *)malloc(sizeof(struct EdgeNode)); // 动态分配内存创建一个新的边节点
    newNode->to = v;                                                 // 设置边的终点

    // 采用"头插法",新节点插入到链表的最前端
    newNode->next = adjList[u]; // 新节点的 next 指向原来的表头
    adjList[u] = newNode;       // 更新表头为新加入的节点
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *loudAndRich(int **richer, int richerSize, int *richerColSize, int *quiet, int quietSize, int *returnSize)
{
    // 1.初始化
    int n = quietSize;                     // 安静数组的长度,也是节点的个数
    build(n);                              // 初始化邻接表,必须先清空上一局的全局变量
    int indegree[n];                       // 入度表,C语言局部数组是垃圾值,必须手动清零
    memset(indegree, 0, sizeof(indegree)); // 初始化入读表为0.

    // 建表,添加边
    for (int i = 0, u, v; i < richerSize; i++)
    {
        u = richer[i][0];  // 起点
        v = richer[i][1];  // 终点
        addListEdge(u, v); // 添加边
        indegree[v]++;     // 终点的入度++
    }

    int queue[n];     // 拓扑排序需要队列
    int l = 0, r = 0; // 初始化队列

    // 搜集入度为0的点,收集到队列里面
    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0) // 入度为0
            queue[r++] = i;   // 入队
    }

    int ans[n]; // 临时的局部的答案数组
    for (int i = 0; i < n; i++)
    {
        ans[i] = i; // 初始化:每个人最安静的人默认是自己
    }

    // 2.开始拓扑排序
    while (l < r)
    {
        int cur = queue[l++]; // 弹出入度为0的节点
        // 遍历cur的邻居
        EdgeNode *edge_ptr = adjList[cur];
        while (edge_ptr)
        {
            int nxt = edge_ptr->to;                // nxt 是 cur 的邻居(比cur钱少的人)
            if (quiet[ans[cur]] < quiet[ans[nxt]]) // 如果 [cur知道的最安静的人] 比 [nxt自己目前知道的] 还要安静
            {
                ans[nxt] = ans[cur]; // 那么nxt就更新答案,更新成cur的答案
            }
            if (--indegree[nxt] == 0) // 邻居的入度--
            {
                queue[r++] = nxt; // 邻居的入度为0,那么就入队
            }
            edge_ptr = edge_ptr->next; // 继续找下一个邻居
        }
    }

    // 3. 构造返回结果
    *returnSize = n;
    int *res = (int *)malloc(sizeof(int) * n); // 申请堆内存
    for (int i = 0; i < n; i++)
    {
        res[i] = ans[i]; // 把局部数组的数据拷贝到返回数组里
    }
    return res;
}
