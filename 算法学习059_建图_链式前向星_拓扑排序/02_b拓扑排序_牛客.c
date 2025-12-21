/**  拓扑排序 (邻接表建图) ::: 牛客这个使用动态内存分配也是可以通过的...
 * =========================================================================
 * 🚀 【算法模板练习】拓扑排序 (Topological Sort)
 * #### 测试链接: https://www.nowcoder.com/practice/88f7e156ca7d43a1a535f619cd3f495c
 * -------------------------------------------------------------------------
 * 【描述】
 * 给定一个包含 n 个点 m 条边的有向无环图,求出该图的拓扑序.
 * 若图的拓扑序不唯一,输出任意合法拓扑序即可.
 * 若该图不能进行拓扑排序(即图中存在环),输出 -1.
 * * 【输入描述】
 * 第一行输入两个整数 n, m (1 <= n, m <= 200,000),表示点数和边数.
 * 接下来 m 行,每行输入两个整数 u, v (1 <= u, v <= n),表示从 u 到 v 有一条有向边.
 * * 【输出描述】
 * 若存在拓扑序,输出一行 n 个整数,用空格隔开.否则输出 -1.
 * 注意:输出的最后一个数后面不要带空格.
 * * 【示例 1】
 * 输入:
 * 5 4
 * 1 2
 * 2 3
 * 3 4
 * 4 5
 * 输出:
 * 1 2 3 4 5
 * =========================================================================
 */

#include <stdio.h>   // 使用sancf()和printf()
#include <stdlib.h>  // 使用malloc()和free()
#include <stdbool.h> // 使用bool数据类型
#include <string.h>  // 使用memset()

#define MAX 200001 // 📌 定义最大范围 (点数与边数)

struct EdgeNode
{                          // 🧱 声明边节点结构体
    int to;                // 🎯 边的终点
    struct EdgeNode *next; // 🔗 指向下一个邻居的指针
};
typedef struct EdgeNode EdgeNode; // 🏷️ 简化类型名

EdgeNode *adjList[MAX]; // 📊 邻接表头指针数组 (每个元素是一个链表头)
int n, m;               // 📍 全局变量:点数 n,边数 m
int queue[MAX];         // 🏃 模拟队列:存储入度为 0 的节点
int l, r;               // ↔️ 队头队尾指针
int indegree[MAX];      // 📥 入度表:记录每个节点的当前入度
int ans[MAX];           // 📝 结果集:存储最终生成的拓扑序列

/**
 * 🧹 函数：build
 * 目的:初始化入度表并释放之前分配的所有动态内存
 */
void build()
{
    memset(indegree, 0, sizeof(indegree)); // 🧼 入度表清零
    for (int i = 1; i <= n; i++)
    {                               // ⚠️ 遍历所有节点 (1 到 n)
        EdgeNode *cur = adjList[i]; // 🔍 获取当前点的链表头
        while (cur)
        {                         // 🌀 循环释放链表节点
            EdgeNode *temp = cur; // 📋 暂存当前指针
            cur = cur->next;      // ⏩ 移动到下一个节点
            free(temp);           // ✅ 释放已处理节点的内存
        }
        adjList[i] = NULL; // 🧼 指针重置为空
    }
}

/**
 * 🛰️ 函数：addListEdge
 * 目的:通过"头插法"向邻接表中添加一条有向边 (u -> v)
 */
void addListEdge(int u, int v)
{
    EdgeNode *newNode = (EdgeNode *)malloc(sizeof(struct EdgeNode)); // 🏗️ 申请新节点内存
    newNode->to = v;                                                 // 🎯 设置终点
    newNode->next = adjList[u];                                      // ✅ 新节点指向原表头 (头插逻辑)
    adjList[u] = newNode;                                            // 🏁 更新表头为新节点
}

/**
 * 🌀 函数：topoSort
 * 目的：执行 Kahn 算法进行拓扑排序
 * @return 是否成功完成排序 (无环)
 */
bool topoSort()
{
    l = r = 0; // ↔️ 初始化队列指针
    for (int i = 1; i <= n; i++)
    { // 1️⃣ 步骤:寻找初始入度为 0 的点
        if (indegree[i] == 0)
        {
            queue[r++] = i; // 📥 入度为 0 则入队
        }
    }
    int count = 0; // 🔢 记录排好序的节点数
    while (l < r)
    {                                      // 2️⃣ 步骤：队列不为空时处理
        int cur = queue[l++];              // 📤 出队一个点
        ans[count++] = cur;                // ✍️ 存入结果集
        EdgeNode *edge_ptr = adjList[cur]; // 🔍 获取该点的邻居链表
        while (edge_ptr)                   // 遍历所有邻居,把它们的入度都减1
        {
            int neighbor = edge_ptr->to;   // 🎯 获取邻居编号
            if (--indegree[neighbor] == 0) // ✂️ 削减入度,若归零则入队
            {
                queue[r++] = neighbor; // 🔄 加入待处理队列
            }
            edge_ptr = edge_ptr->next; // ⏩ 移动到下一条边
        }
    }
    return count == n; // 💡 判断结果数是否等于总点数
}

/**
 * 🚀 主函数:程序入口
 */
int main()
{
    if (scanf("%d %d", &n, &m) != 2)
    {
        return 0;
    } // 📥 读取点数和边数
    build(); // 🛠️ 初始化/重置环境
    for (int i = 0; i < m; i++)
    { // 🔄 循环读入 m 条边
        int u, v;
        scanf("%d %d", &u, &v); // 📥 读取边 u -> v
        addListEdge(u, v);      // 🛰️ 添加到邻接表
        indegree[v]++;          // 📈 终点入度累加
    }

    if (!topoSort())
    {                     // 🌀 执行排序并判定
        printf("%d", -1); // ❌ 存在环则输出 -1
    }
    else // ✅ 排序成功按格式输出
    {
        for (int i = 0; i < n - 1; i++)
        {
            printf("%d ", ans[i]); // ✍️ 打印前 n-1 个数加空格
        }
        printf("%d", ans[n - 1]); // 🎯 最后一个数后无空格
    }
    return 0; // 🏁 结束
}
