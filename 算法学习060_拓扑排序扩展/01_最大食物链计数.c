/*
 * 题目:P4017 最大食物链计数
 * 来源:洛谷 (Luogu)
 * #### 测试连接: https://www.luogu.com.cn/problem/P4017
 *
 * 题目描述:
 * 给你一个食物网，你要求出这个食物网中最大食物链的数量。
 * (这里的"最大食物链",指的是生物学意义上的食物链,即最左端是不会捕食其他生物的生产者,
 * 最右端是不会被其他生物捕食的消费者.)
 *
 * 由于这个结果可能过大,你只需要输出总数模上 80112002 的结果.
 *
 * 输入格式:
 * 第一行,两个正整数 n、m,表示生物种类 n 和吃与被吃的关系数 m.
 * 接下来 m 行，每行两个正整数 A B,表示被吃的生物 A 和吃 A 的生物 B (即存在边 A -> B)。
 *
 * 输出格式:
 * 一行一个整数,为最大食物链数量模上 80112002 的结果.
 *
 * 数据范围:
 * 1 <= n <= 5000
 * 1 <= m <= 500000
 * 保证图中不会出现环(DAG).
 */

#include <stdio.h>  // 使用scanf()|printf()
#include <string.h> // 使用memset()

#define MAXN 5001    // 最大节点数 N
#define MAXM 500001  // 最大边数 M
#define MOD 80112002 // 结果取模,防止整数溢出,同时题目也要求取模

// 链式前向星建图变量
int head[MAXN]; // head[u] 存储节点 u 的第一条边的编号
int next[MAXM]; // next[e] 存储编号为 e 的边的"下一条"边编号
int to[MAXM];   // to[e] 存储编号为 e 的边的终点
int cnt;        // 边的计数器(给每条边分配唯一ID)
int n, m;       // n个节点, m条边

// 拓扑排序需要的队列
int queue[MAXN]; // 手写队列,比系统队列更快
int l, r;        // l: 队头指针, r: 队尾指针

// 入度表
int indegree[MAXN]; // 记录每个节点有多少条入边

// 向上推送的信息 (DP数组)
int lines[MAXN]; // lines[i] 表示从起点到节点 i 有多少条不同的路径

void build()
{
    cnt = 1;                               // 边编号从1开始,这样0就可以表示"没有边"
    memset(head, 0, sizeof(head));         // 初始化头指针数组
    memset(indegree, 0, sizeof(indegree)); // 清空入度表
    memset(lines, 0, sizeof(lines));       // 清空路径计数数组
}

void addChainEdge(int u, int v)
{
    next[cnt] = head[u]; // 新边的 next 指向旧的 head (头插法)
    to[cnt] = v;         // 记录这条边的终点是 v
    head[u] = cnt;       // 更新 u 的 head 为当前新边
    cnt++;               // 编号自增，为下一条边做准备
}

int ways()
{
    l = r = 0; // 初始化队列指针

    // 1. 初始化:找到所有入度为0的点(生产者)
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            queue[r++] = i; // 入度为0,加入拓扑排序队列
            lines[i] = 1;   // 作为起点,自身算作 1 条路径
        }
    }

    int ans = 0; // 记录最终的总路径数

    // 2. 开始拓扑排序
    while (l < r)
    {
        int u = queue[l++]; // 弹出当前处理的节点 u
        if (head[u] == 0)   // 当前的u节点不再有后续邻居了
        {
            ans = (ans + lines[u]) % MOD; // 如果是终点,累加它的路径数到答案
        }
        else
        {
            for (int ei = head[u], v; ei > 0; ei = next[ei]) // 遍历 u 的所有邻居 v
            {
                v = to[ei];                             // 获取当前边的终点 v
                lines[v] = (lines[u] + lines[v]) % MOD; // 核心 DP 转移:把 u 的路径数加到 v 身上
                if (--indegree[v] == 0)                 // 拓扑排序逻辑:删掉 u->v 这条边 (v的入度减1)
                {
                    queue[r++] = v; // 如果 v 的所有前置节点都处理完了，入队
                }
            }
        }
    }
    return ans; // 返回统计好的路径总数
}

int main()
{
    scanf("%d %d", &n, &m); // 读取点数和边数
    build();                // 初始化建图环境
    for (int i = 0, u, v; i < m; i++)
    {
        scanf("%d %d", &u, &v); // 读取一条边 u -> v
        addChainEdge(u, v);     // 存入链式前向星
        indegree[v]++;          // 统计终点 v 的入度，用于拓扑排序
    }
    printf("%d", ways()); // 执行算法并输出结果
    return 0;
}
