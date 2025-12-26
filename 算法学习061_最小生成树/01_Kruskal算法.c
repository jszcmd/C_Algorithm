/*
 * 🌲 题目名称: P3366 【模板】最小生成树
 * 🔗 题目来源: 洛谷 (Luogu)
 * 🚀 算法标签: Kruskal / 并查集 / 图论
 * #### 测试链接: https://www.luogu.com.cn/problem/P3366
 * 📝 题目描述
 * ----------------------------------------------------
 * 如题,给出一个无向图,求出最小生成树.
 * 如果该图不连通,则输出 "orz".
 *
 * 📥 输入格式
 * ----------------------------------------------------
 * 1. 第一行:两个整数 N, M (N 个结点，M 条边)
 * 2. 后续 M 行:每行三个整数 Xi, Yi, Zi
 * (表示有一条长度为 Zi 的无向边连接结点 Xi, Yi)
 *
 * 📤 输出格式
 * ----------------------------------------------------
 * ✅ 若连通:输出一个整数,表示最小生成树的边权之和.
 * ❌ 若不连通:输出 "orz".
 *
 * 🧐 样例数据
 * ----------------------------------------------------
 * Input:                  Output:
 * 4 5                     7
 * 1 2 2
 * 1 3 2
 * 1 4 3
 * 2 3 4
 * 3 4 3
 *
 * 📊 数据范围
 * ----------------------------------------------------
 * 🔹 N <= 5,000
 * 🔹 M <= 200,000
 * 🔹 Zi <= 10,000
 */

#include <stdio.h>   // 使用printf()和scanf()函数
#include <stdlib.h>  // 使用qsort()函数
#include <stdbool.h> // 使用bool数据类型

#define MAXN 5001   // 🔢 最大节点数
#define MAXM 200001 // 🛣️ 最大边数

int father[MAXN];   // 🔗 并查集父节点数组
int edges[MAXM][3]; // 📊 边集 [u, v, w]
int n, m;           // 📏 n:节点, m:边

// 🛠️ 初始化并查集
void build()
{
    for (int i = 1; i <= n; i++)
    {
        father[i] = i; // 🔄 初始时,每个点的父节点是自己
    }
}

// 🔍 查找祖先 (带路径压缩)
int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]); // 🚀 路径压缩:直接指向祖先,加速后续查找
    }
    return father[i];
}

// 🤝 合并集合
bool do_union(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx == fy)
    {
        return false; // ⭕ 祖先相同,说明已连通 (会形成环)
    }
    else
    {
        father[fx] = fy; // 🔗 将 x 的集合挂到 y 下面
        return true;
    }
}

// ⚖️ 排序比较函数 (按权重升序)
int weight_cmp(const void *e1, const void *e2)
{
    int *arr1 = (int *)e1; // 🎯 修正指针转换
    int *arr2 = (int *)e2;
    return arr1[2] - arr2[2]; // 📉 权重小的排前面
}

int main()
{
    if (scanf("%d %d", &n, &m) != 2)
        return 0; // 📥 读取节点数和边数

    build(); // 🏗️ 初始化

    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]); // 📝 读取边信息
    }

    qsort(edges, m, sizeof(edges[0]), weight_cmp); // ⚡ 核心步骤:按权重排序所有边

    int ans = 0;     // 💰 最小生成树总权值
    int edgeCnt = 0; // 1️⃣ 已选边数计数

    // 🔄 贪心遍历:从小到大枚举每一条边 (注意是 m 不是 n)
    for (int i = 0; i < m; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        if (do_union(u, v)) // ❓ 尝试合并,若不在同一集合则合并成功
        {
            edgeCnt++; // ✅ 选边成功
            ans += w;  // ➕ 累加权重
            if (edgeCnt == n - 1)
                break; // 🏁 优化:凑够 n-1 条边即可结束
        }
    }

    // 📤 输出结果
    if (edgeCnt == n - 1)
        printf("%d", ans); // 🎉 成功生成
    else
        printf("orz"); // ❌ 图不连通

    return 0;
}
