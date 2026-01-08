/*
 * ================================================================================
 * 📘 题目: 并查集标准模板 (Union-Find / Disjoint Set Union)
 * 🔗 题目链接: https://www.luogu.com.cn/problem/P3367 (经典模板)
 * ================================================================================
 * 难度: 入门/提高
 * 标签: 并查集, 路径压缩, 按秩合并
 *
 * 【题目描述】
 * 维护一个并查集,支持以下操作:
 * 1. 查询两个元素是否在同一个集合中.
 * 2. 合并两个集合.
 *
 * --------------------------------------------------------------------------------
 * 🌟 核心优化说明:
 * • 路径压缩 (Path Compression): 在 find 时将沿途所有节点指向代表节点,使树高度变 1.
 * • 小挂大 (Union by Size): 始终将节点数少的集合挂到节点数多的集合下,防止退化为链表.
 * ================================================================================
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX 1000001

int father[MAX]; // 🌳 存储每个节点的父节点
int size[MAX];   // 📊 存储以当前节点为代表节点的集合中的元素个数
int stack[MAX];  // 🛠️ 辅助栈:用于迭代实现路径压缩,防止递归过深导致栈溢出
int n;           // 🔢 节点总数

// 🧹 初始化:每个节点初始时父节点都是自己,集合大小为 1
void build()
{
    for (int i = 0; i <= n; i++)
    {
        father[i] = i;
        size[i] = 1;
    }
}

// 🔍 寻找代表节点(寻找根节点)
// i 号节点往上一直找,找到最终的代表节点返回,并进行扁平化处理(路径压缩)
int find(int i)
{
    int pathSize = 0; // 🚩 沿途收集了几个点
    // 1️⃣ 第一步：向上找根节点
    while (i != father[i])
    {
        stack[pathSize++] = i; // 📥 将沿途经过的节点存入栈中
        i = father[i];         // 🪜 往上跳一级
    } // 此时 i 已经是代表节点(根节点)了

    // 2️⃣ 第二步:扁平化处理(路径压缩)
    // 将栈中收集到的所有节点的父节点直接指向根节点 i
    while (pathSize > 0)
    {
        father[stack[--pathSize]] = i; // ⚡ 缩短未来的查找路径
    }
    return i;
}

// ❓ 查询两个点是否属于同一个集合
bool isSameSet(int x, int y)
{
    if (x == y)                // 题目中可能出现 x==y的情况:
        return true;           // 不用调用find函数,直接返回true
    return find(x) == find(y); // ⚖️ 如果它们的代表节点相同,则在同一集合
}

// 🤝 合并操作
void _union(int x, int y)
{
    int fx = find(x); // 🕵️ 找到 x 的根
    int fy = find(y); // 🕵️ 找到 y 的根
    if (fx == fy)
    {
        return; // 🛑 已经在同一集合,无需合并
    }
    else // (fx != fy)的情况
    {
        // 📏 按秩合并策略:小的集合合并到大的集合里
        if (size[fx] >= size[fy])
        {
            size[fx] += size[fy]; // ➕ 大集合累加小集合的成员数
            father[fy] = fx;      // 🔗 小集合根节点指向大集合根节点
        }
        else
        {
            size[fy] += size[fx]; // ➕ 大集合累加小集合的成员数
            father[fx] = fy;      // 🔗 小集合根节点指向大集合根节点
        }
    }
}

int main()
{
    int num = 0; // 执行num次操作
    // 📥 输入节点数 n 和操作数 num
    if (scanf("%d %d", &n, &num) != 2)
        return 0;

    build(); // 🏗️ 执行初始化操作

    for (int i = 0, operation, x, y; i < num; i++)
    {
        // 📥 输入操作类型及对应的两个节点
        if (scanf("%d %d %d", &operation, &x, &y) != 3)
            break;

        if (operation == 1)
        {
            printf(isSameSet(x, y) ? "Yes\n" : "No\n"); // 🏷️ 操作 1:查询是否为同一集合
        }
        else
        {
            _union(x, y); // 🏷️ 操作 2:执行合并
        }
    }
    return 0;
}
