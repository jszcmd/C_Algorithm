/*
 * ================================================================================
 * 📘 题目: P3367 【模板】并查集
 * 🔗 题目链接: https://www.luogu.com.cn/problem/P3367
 * ================================================================================
 * ⏱️ 时间限制: 2.00s | 💾 内存限制: 512.00MB
 * * 📝 【题目描述】
 * 如题,现在有一个并查集,你需要完成合并和查询操作.
 * * 📥 【输入格式】
 * 第一行包含两个整数 N, M, 表示共有 N 个元素和 M 个操作.
 * 接下来 M 行,每行包含三个整数 Zi, Xi, Yi.
 * • 当 Zi = 1 时,将 Xi 与 Yi 所在的集合合并.
 * • 当 Zi = 2 时,输出 Xi 与 Yi 是否在同一集合内,是的输出 Y ;否则输出 N .
 * * 📤 【输出格式】
 * 对于每一个 Zi = 2 的操作,都有一行输出,每行包含一个大写字母,为 Y 或者 N .
 * * 🌟 【输入输出样例】
 * 输入 #1:            输出 #1:
 * 4 7                N
 * 2 1 2              Y
 * 1 1 2              N
 * 2 1 2              Y
 * 1 3 4
 * 2 1 4
 * 1 2 3
 * 2 1 4
 * * 📏 【说明/提示】
 * • 对于 100% 的数据,1 <= N <= 2 * 10^5, 1 <= M <= 10^6, 1 <= Xi, Yi <= N, Zi ∈ {1, 2}。
 * ================================================================================
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX 200001 // 📐 根据数据范围 N <= 2*10^5 设置最大值

int father[MAX]; // 🌳 存储每个节点的父节点
int n;           // 🔢 节点总数

// 🧹 执行初始化:每个节点初始时的父节点都是自己
void build()
{
    for (int i = 0; i <= n; i++)
    {
        father[i] = i;
    }
}

// 🔍 寻找代表节点(采用递归路径压缩)
int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]); // ⚡ 路径压缩:递归回溯时直接修改父节点指向根节点
    }
    return father[i];
}

// ⚖️ 查询两个点是否属于同一个集合
bool isSameSet(int x, int y)
{
    if (x != y)
    {
        return find(x) == find(y); // 🔍 比较两者的根节点(代表节点)是否一致
    }

    return true; // 🎯 节点相同则必然在同一集合
}

// 🤝 合并操作
void do_union(int x, int y)
{
    father[find(x)] = find(y); // 🔗 将 x 所在集合的根节点指向 y 所在集合的根节点
}

int main()
{
    int num = 0; // 🔢 执行 num 次操作 (M)

    // 📥 输入节点数 n 和操作数 num
    if (scanf("%d %d", &n, &num) != 2)
        return 0;

    build(); // 🏗️ 初始化并查集结构

    for (int i = 0, operation, x, y; i < num; i++)
    {
        // 📥 输入操作类型 (operation) 及其关联的两个节点 (x, y)
        if (scanf("%d %d %d", &operation, &x, &y) != 3)
            break;

        if (operation == 1)
        {
            do_union(x, y); // 🏷️ Zi = 1: 执行合并
        }
        else
        {
            printf(isSameSet(x, y) ? "Y\n" : "N\n"); // 🏷️ Zi = 2: 查询并输出结果 (Y 或 N)
        }
    }
    return 0;
}
