/*
 * 🧩 字典序最小的拓扑排序模板
 * #### 测试链接: https://www.luogu.com.cn/problem/U107394
 * 📝 题目描述:
 * 给定一个有向无环图(DAG),包含 n 个点和 m 条边.
 * 要求输出该图字典序最小的拓扑排序结果.
 * 字典序最小指:在满足排序前提下,让越靠前的数字尽可能小。
 * 📥 输入格式:
 * 第一行包含整数 n 和 m.接下来 m 行每行 u v,表示有向边 u -> v.
 * 📤 输出格式:
 * 一行由空格隔开的拓扑排序序列.
 * 🔢 数据范围:
 * 1 <= n, m <= 10^5,图中可能存在重边.
 */

#include <stdio.h>   // 使用printf()和scanf()
#include <string.h>  // 使用memset()函数
#include <stdbool.h> // 使用bool数据类型

#define MAX 100001 // 🚀 算法处理的最大数据规模

// ================================================ 🕸️ 链式前向星 (图存储)
int head[MAX]; // 📍 存点:head[u] 指向点 u 的第一条边
int next[MAX]; // ⛓️ 连边:指向同一始点的下一条边
int to[MAX];   // 🎯 终点:当前边的目标节点
int cnt;       // 🔢 计数:边的唯一编号标识

// ================================================ 🌲 优先队列 (小根堆)
int heap[MAX]; // 🏗️ 堆体:存储当前所有入度为 0 的节点编号
int heapSize;  // 📏 堆大小:记录堆中当前的元素数量

// ================================================ 📊 拓扑排序核心变量
int indegree[MAX]; // 📥 入度：记录每个节点被指向的次数
int ans[MAX];      // ✅ 结果：存储字典序最小的拓扑序列

int n, m; // 👥 统计:n 个点,m 条边

// ================================================ 🕸️ 链式前向星主要函数 (建立图)

/** 🧹 初始化:清空全局数组并重置边计数与堆计数 */
void build()
{
    cnt = 1;
    heapSize = 0;
    memset(head, 0, sizeof(head));
    memset(indegree, 0, sizeof(indegree));
}

/** 🔗 加边:在链式前向星中添加 u -> v 的有向边 */
void addChainEdge(int u, int v)
{
    next[cnt] = head[u]; // 将新边挂载到当前链表头
    to[cnt] = v;         // 记录终点信息
    head[u] = cnt;       // 更新头节点索引
    cnt++;
}

// ================================================ 🏆 小根堆维护逻辑

/** 🔄 交换:交换堆数组中两个索引位置的节点编号 */
void swap(int a, int b)
{
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

/** 🔼 插入:新节点入堆并向上浮动,维持小根堆性质 (字典序核心) */
void add(int num)
{
    int i = heapSize++;
    heap[i] = num;
    while (i > 0 && heap[i] < heap[(i - 1) / 2]) // 💡 若子节点编号更小则上浮
    {
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

/** 🔽 弹出:移出堆顶最小编号节点并执行向下调整 (Heapify) */
int pop()
{
    int res = heap[0];          // 提取堆顶(当前最小编号)
    heap[0] = heap[--heapSize]; // 将末尾节点移至堆顶重新平衡
    int i = 0;
    int l = 2 * i + 1;
    while (l < heapSize) // 🔍 递归检查子节点
    {
        int best = l + 1 < heapSize && heap[l + 1] < heap[l] ? l + 1 : l;
        best = heap[best] < heap[i] ? best : i;
        if (best == i)
            break; // 符合性质,停止沉降

        swap(best, i);
        i = best;
        l = i * 2 + 1;
    }
    return res;
}

/** ❓ 判空:返回当前堆中是否还有待处理的节点 */
bool isEmpty()
{
    return heapSize == 0;
}

// ================================================ 🎓 算法核心流程

/** 🧩 拓扑排序:结合小根堆,计算并存储字典序最小的拓扑序列 */
void topSort()
{
    // 1️⃣ 扫描所有节点:将初始入度为 0 的点送入堆中准备处理
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
            add(i);
    }

    int count = 0;
    // 2️⃣ 循环处理:每次从堆中取出编号最小的任务执行
    while (!isEmpty())
    {
        int cur = pop();    // 弹出当前可执行的最小编号节点
        ans[count++] = cur; // 记录到结果序列

        // 3️⃣ 释放邻居:消除当前节点发出的边,更新邻居入度
        for (int ei = head[cur]; ei != 0; ei = next[ei])
        {
            if (--indegree[to[ei]] == 0) // 🔓 若邻居入度降为 0,则入堆
            {
                add(to[ei]);
            }
        }
    }
}

/** 🏁 程序入口:读取输入数据并驱动整个排序流程 */
int main()
{
    if (scanf("%d %d", &n, &m) != 2)
        return 0;
    build();

    // 🏗️ 读取 m 条边信息并构建有向图
    for (int i = 0, u, v; i < m; i++)
    {
        scanf("%d %d", &u, &v);
        addChainEdge(u, v);
        indegree[v]++; // 终点入度累加
    }

    topSort();

    // 📤 格式化输出排序结果，末尾无空格
    for (int i = 0; i < n - 1; i++)
        printf("%d ", ans[i]);
    printf("%d", ans[n - 1]);

    return 0;
}
