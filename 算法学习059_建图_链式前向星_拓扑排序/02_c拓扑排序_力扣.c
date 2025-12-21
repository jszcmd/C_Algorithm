/**
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

#include <string.h>  // 使用memset函数
#include <stdbool.h> // 使用bool数据类型
#include <stdlib.h>  // 使用malloc函数

#define MAX_N 2005 // 🏗️ 最大节点数 (课程数 0 ~ 1999)
#define MAX_M 5005 // 🛣️ 最大边数 (先修关系数),实际上力扣的测试数据没有那么大

// 📊 链式前向星核心数组
int head[MAX_N]; // 🏁 head[i]: 存储节点 i 的第一条(最新)出边的编号
int nxt[MAX_M];  // 🔗 nxt[i]: 存储第 i 条边的“下一条”出边编号
int to[MAX_M];   // 🎯 to[i]: 存储第 i 条边的终点节点
int cnt;         // 🔢 边计数器

// ⚡ 拓扑排序辅助结构
int queue[MAX_N]; // 🏃 模拟队列,用于存放当前入度为 0 的点
int l, r;         // ↔️ 队头(l)和队尾(r)指针

int indegree[MAX_N]; // 📥 入度表:记录每个节点当前的入度数量
int ans[MAX_N];      // 📝 结果集:存储最终生成的拓扑序列
int n, m;            // 📍 全局变量:节点数 n 和边数 m

/**
 * 🧹 函数:build
 * 目的:初始化/清空全局数据,为构建新图做准备
 */
void build()
{
    cnt = 1;                               // 🔢 边编号从 1 开始
    memset(head, 0, sizeof(head));         // 🧼 将所有头节点索引重置为 0
    memset(indegree, 0, sizeof(indegree)); // 🧼 清空入度统计
}

/**
 * 🛰️ 函数:addChainEdge
 * 目的:在链式前向星中添加一条有向边 (u -> v)
 */
void addChainEdge(int u, int v)
{
    nxt[cnt] = head[u]; // 🔗 将新边的 next 指向该起点原本的“头”
    to[cnt] = v;        // 🎯 记录该边的终点
    head[u] = cnt++;    // 🏁 更新表头并递增边计数器
}

/**
 * 🌀 函数：topoSort
 * 目的：执行 Kahn 算法进行拓扑排序
 * @return 是否能够完成所有课程 (无环返回 true)
 */
bool topoSort()
{
    l = r = 0; // ↔️ 初始化队列指针

    // 1️⃣ 第一步:扫描所有节点,将初始入度为 0 的课程入队
    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            queue[r++] = i;
        }
    }

    int count = 0; // 🔢 统计出队(已排序)的节点数

    // 2️⃣ 第二步:只要队列不为空,不断提取节点并"删除"其发出的边
    while (l < r)
    {
        int cur = queue[l++]; // 📤 出队一个入度为 0 的节点
        ans[count++] = cur;   // ✍️ 存入结果集

        for (int ei = head[cur]; ei != 0; ei = nxt[ei]) // 🔍 遍历当前节点 cur 指向的所有邻居
        {
            if (--indegree[to[ei]] == 0) // ✂️ 将邻居的入度减 1 (相当于删除 cur -> to[ei] 这条边)
            {
                queue[r++] = to[ei]; // 🔄 如果邻居的入度归零,则可以入队
            }
        }
    }

    // 💡 判断结果:如果排好序的节点数等于总节点数 n,则排序成功
    return count == n;
}

/**
 * 🚀 LeetCode 入口函数:findOrder
 * -------------------------------------------------------------------------
 * @param numCourses 课程总数
 * @param prerequisites 先修关系数组 [终点, 起点]
 * @param returnSize 返回数组的长度指针
 * -------------------------------------------------------------------------
 */
int *findOrder(int numCourses, int **prerequisites, int prerequisitesSize, int *prerequisitesColSize, int *returnSize)
{
    n = numCourses;        // 赋值点数
    m = prerequisitesSize; // 赋值边数

    build(); // 🛠️ 初始化存储空间

    // 🏗️ 建立有向图:[v, u] 意味着必须先修 u 再修 v (即 u -> v)
    for (int i = 0; i < m; i++)
    {
        int v = prerequisites[i][0]; // 🎯 终点 (被指向者)
        int u = prerequisites[i][1]; // 🏁 起点 (先修课)
        addChainEdge(u, v);          // 🛰️ 建立由 u 指向 v 的边
        indegree[v]++;               // 📈 统计入度
    }

    // 执行拓扑排序并判定结果
    if (!topoSort())
    {
        *returnSize = 0; // ❌ 排序失败(图中存在环路),返回大小为 0
        return NULL;     // 返回空指针
    }
    else
    {
        *returnSize = n;                           // ✅ 排序成功,设置返回长度为 n
        int *arr = (int *)malloc(sizeof(int) * n); // 动态申请结果内存
        for (int i = 0; i < n; i++)
        {
            arr[i] = ans[i]; // 📋 拷贝拓扑序列到结果数组
        }
        return arr; // 🏁 返回结果 (调用者负责 free)
    }
}
