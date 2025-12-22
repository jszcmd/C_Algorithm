/**  ****** 使用邻接表建图_动态内存分配 ******
 * * =========================================================================
 * 🧩 LeetCode 210. 课程表 II (Course Schedule II)
 * #### 测试链接: https://leetcode.cn/problems/course-schedule-ii/description/
 * =========================================================================
 * * 📝 【题目描述】
 * 现在总共有 numCourses 门课程需要选,记为 0 到 numCourses - 1.
 * 给定一个数组 prerequisites,其中 prerequisites[i] = [ai, bi] 表示在选修课程 ai 前，
 * 必须先选修课程 bi (即存在一条由 bi 指向 ai 的有向边).
 * * 🎯 【目标】
 * 返回你为了学完所有课程所安排的学习顺序.
 * 可能有多个正确顺序,只需返回任意一种即可.
 * 若不可能完成所有课程,返回一个空数组.
 * * 💡 【示例解析】
 * - 示例 1: numCourses = 2, prerequisites = [[1, 0]] -> 输出: [0, 1].
 * - 示例 2: numCourses = 4, prerequisites = [[1, 0], [2, 0], [3, 1], [3, 2]]
 * -> 输出: [0, 1, 2, 3] 或 [0, 2, 1, 3].
 * * ⚙️ 【提示与约束】
 * - 1 <= numCourses <= 2000
 * - 0 <= prerequisites.length <= numCourses * (numCourses - 1)
 * - 所有 [ai, bi] 互不相同
 * * =========================================================================
 */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 2001 // 🚀 最大课程数量限制

// ================================================ 🕸️ 邻接表结构定义
struct EdgeNode
{
    int to;                // 🎯 目标课程编号
    struct EdgeNode *next; // ⛓️ 指向下一条边的指针
};

typedef struct EdgeNode EdgeNode;

EdgeNode *adjList[MAX]; // 📍 邻接表头指针数组
int n, m;               // 👥 n: 课程数, m: 依赖关系数

int queue[MAX]; // 🏗️ 仿真队列:用于 BFS
int l, r;       // 👈 队列的头(l)和尾(r)指针

int indegree[MAX]; // 📥 入度表:记录每门课的前置课程数量
int ans[MAX];      // ✅ 结果数组:存储拓扑排序序列

/** 🧹 初始化:清空入度表并释放之前邻接表节点的内存 */
void build()
{
    // 💡 修正:memset 第三个参数应为字节大小 sizeof(indegree)
    memset(indegree, 0, sizeof(indegree));

    for (int i = 0; i < n; i++)
    {
        EdgeNode *cur = adjList[i];
        while (cur)
        {
            EdgeNode *temp = cur;
            cur = cur->next;
            free(temp); // 🗑️ 释放节点内存
        }
        adjList[i] = NULL;
    }
}

/** ➕ 添加边:使用头插法将 v 插入到 u 的邻接链表中 */
void addListEdge(int u, int v)
{
    EdgeNode *newNode = (EdgeNode *)malloc(sizeof(EdgeNode));
    newNode->to = v;
    newNode->next = adjList[u]; // 指向当前头节点
    adjList[u] = newNode;       // 更新头节点为新节点
}

/** 🧩 拓扑排序:使用 Kahn 算法(基于队列)寻找合法的拓扑序列 */
bool TopSort()
{
    l = r = 0;
    // 1️⃣ 将所有入度为 0 的课程(无需前置课)入队
    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            queue[r++] = i;
        }
    }

    int count = 0;
    // 2️⃣ 循环从队列中取出课程并处理
    while (l < r)
    {
        int cur = queue[l++];
        ans[count++] = cur;

        EdgeNode *edge_ptr = adjList[cur];
        // 3️⃣ 遍历当前课程的所有后续课程
        while (edge_ptr)
        {
            int neighbor = edge_ptr->to;
            // 🔓 移除依赖,若后续课程入度减为 0,则入队
            if (--indegree[neighbor] == 0)
            {
                queue[r++] = neighbor;
            }
            edge_ptr = edge_ptr->next;
        }
    }
    // 🏁 若处理的节点数等于总课程数,说明不存在环
    return count == n;
}

/** 🏁 主逻辑封装:适配 LeetCode findOrder 接口 */
int *findOrder(int numCourses, int **prerequisites, int prerequisitesSize, int *prerequisitesColSize, int *returnSize)
{
    n = numCourses;
    m = prerequisitesSize;
    build(); // 执行初始化清空工作

    // 🏗️ 根据输入构建有向图并统计入度
    for (int i = 0; i < m; i++)
    {
        int v = prerequisites[i][0]; // 想要上的课
        int u = prerequisites[i][1]; // 必须先上的课 (u -> v)
        addListEdge(u, v);
        indegree[v]++;
    }

    // ⚡ 执行拓扑排序
    if (!TopSort())
    {
        *returnSize = 0;
        return NULL; // 🚫 存在环,无法完成所有课程
    }
    else
    {
        *returnSize = n;
        int *arr = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = ans[i];
        }
        return arr; // ✅ 返回排序结果
    }
}
