/*
 * ======================================================================================
 * 题目:2050. 并行课程 III (Parallel Courses III)
 * 难度:困难 (Hard)
 * 来源:LeetCode
 * #### 测试链接: https://leetcode.cn/problems/parallel-courses-iii/
 *
 * 描述:
 * 给你一个整数 n ,表示有 n 节课,课程编号从 1 到 n .
 * 同时给你一个二维整数数组 relations ,其中 relations[j] = [prevCourse_j, nextCourse_j] ,
 * 表示课程 prevCourse_j 必须在课程 nextCourse_j 之前 完成(先修课的关系).
 * 同时给你一个下标从 0 开始的整数数组 time ,其中 time[i] 表示完成第 (i+1) 门课程需要花费的 月份 数.
 *
 * 请你根据以下规则算出完成所有课程所需要的 最少 月份数:
 * 1. 如果一门课的所有先修课都已经完成,你可以在 任意 时间开始这门课程.
 * 2. 你可以 同时 上 任意门课程 .
 *
 * 请你返回完成所有课程所需要的 最少 月份数.
 *
 * 注意:测试数据保证一定可以完成所有课程(也就是先修课的关系构成一个有向无环图).
 * ======================================================================================
 */

#include <string.h> // 使用memset()

#define MAXN 50001 // 最大节点数 N
#define MAXM 50001 // 最大边数 M

// 链式前向星建图变量
int head[MAXN]; // head[u] 存储节点 u 的第一条边的编号
int next[MAXM]; // next[e] 存储编号为 e 的边的"下一条"边编号
int to[MAXM];   // to[e] 存储编号为 e 的边的终点
int cnt;        // 边的计数器(给每条边分配唯一ID)

// 拓扑排序需要的队列
int queue[MAXN]; // 手写队列
int l, r;        // l: 队头指针, r: 队尾指针

// 入度表
int indegree[MAXN]; // 只使用下标 1到n ;0下标弃而不用

// cost[i]: 完成第i件事情,已经它之前的事情所用的时间.
int cost[MAXN]; // 完成工作耗用的时间;0下标弃而不用

void build()
{
    l = r = 0;                             // 队列初始化为0
    cnt = 1;                               // 边编号从1开始,这样0就可以表示"没有边"
    memset(head, 0, sizeof(head));         // 初始化头指针数组
    memset(indegree, 0, sizeof(indegree)); // 清空入度表
    memset(cost, 0, sizeof(cost));         // 清空花费表
}

void addChainEdge(int u, int v)
{
    next[cnt] = head[u]; // 新边的 next 指向旧的 head (头插法)
    to[cnt] = v;         // 记录这条边的终点是 v
    head[u] = cnt;       // 更新 u 的 head 为当前新边
    cnt++;               // 编号自增,为下一条边做准备
}

int minimumTime(int n, int **relations, int relationsSize, int *relationsColSize, int *time, int timeSize)
{
    // 节点的关系: [1,2,3,...,n] 节点是从1开始的 ; 一共有1...n这么多个节点
    // 时间time:  0下标: time[0] 代表1这件事完成的时间 依次类推
    // 也就是说 i号点的单点的时间花费要去 time[i-1]位置拿

    build(); // 初始化
    // 建图,添加边
    for (int i = 0, u, v; i < relationsSize; i++)
    {
        u = relations[i][0];
        v = relations[i][1];
        addChainEdge(u, v);
        indegree[v]++;
    }
    // 先遍历一遍,把入度为0的节点先加入到队列里面
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            queue[r++] = i;
        }
    }
    // 开始拓扑排序主要逻辑
    while (l < r)
    {
        int cur = queue[l++]; // 弹出入度为0的节点,cur是节点编号
        // 在没有加之前是自己前面的事完成所需要的时间,加完之后就是自己这件事连同前面的事完成所需要的时间
        cost[cur] += time[cur - 1]; // 每一个点完成的时间先加自己的单点
        // 遍历邻居,给邻居推时间
        for (int ei = head[cur]; ei > 0; ei = next[ei])
        {
            int v = to[ei]; // v是cur节点的邻居的编号
            // 邻居之间有一个完成前面的事所需要的时间,更现在的这件事完成所需要的时间比,谁更大就维持谁
            cost[v] = (cost[v] > cost[cur]) ? cost[v] : cost[cur];
            if (--indegree[v] == 0) // 邻居的入度--
            {
                queue[r++] = v; // 如果v节点的入度变成0,进入队列.
            }
        }
    }
    // 遍历找所花费的最大时间
    int ans = 0;
    for (int i = 1; i <= n; i++) // 现在,cost[i]表示完成节点i以及i之前的事所需要的时间
    {
        ans = (ans > cost[i]) ? ans : cost[i];
    }
    return ans;
}
