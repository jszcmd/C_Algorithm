/**
 * @brief 🚀 算法练习:基于邻接表的带权图表示法
 * -------------------------------------------------------------------------
 * 📝 【题目描述】
 * -------------------------------------------------------------------------
 * 在图论中,邻接表(Adjacency List)是表示图的一种高效方式,尤其适用于稀疏图.
 * 请按照以下要求完成代码练习:
 * * 1. 📍 节点规范:假设图最多有 10 个节点,编号从 1 开始(如:节点1, 节点2...).
 * 2. 📊 数据结构:使用结构体指针数组 `adjList` 表示图,每个元素指向一个单链表.
 * 3. ⚙️ 功能实现:
 * - 初始化:清空邻接表,并释放之前申请的所有动态内存.
 * - 有向图构建:传入边集 `[[起点, 终点, 权重], ...]`,使用头插法建立单链表.
 * - 无向图构建:同上,但每条边需双向插入节点.
 * - 遍历打印:输出每个节点及其邻居节点和边权信息.
 * * 4. 🧮 存储原理:
 * 对于每个顶点 i,邻接表存储了一个包含所有从顶点 i 出发的边的列表.
 * -------------------------------------------------------------------------
 * 🧪 【测试用例与预期结果】
 * -------------------------------------------------------------------------
 * Case 1: 有向带权图 (n=4)
 * 输入边集: {{1,3,6}, {4,3,4}, {2,4,2}, {1,2,7}, {2,3,5}, {3,1,1}}
 * 预期遍历输出 (顺序可能因头插法而异):
 * Node 1 (Neighbor, Weight): (2,7) (3,6)
 * Node 2 (Neighbor, Weight): (3,5) (4,2)
 * Node 3 (Neighbor, Weight): (1,1)
 * Node 4 (Neighbor, Weight): (3,4)
 * * Case 2: 无向带权图 (n=5)
 * 输入边集: {{3,5,4}, {4,1,1}, {3,4,2}, {5,2,4}, {2,3,7}, {1,5,5}, {4,2,6}}
 * 预期遍历输出:
 * Node 1 (Neighbor, Weight): (5,5) (4,1)
 * Node 2 (Neighbor, Weight): (4,6) (3,7) (5,4)
 * Node 3 (Neighbor, Weight): (2,7) (4,2) (5,4)
 * Node 4 (Neighbor, Weight): (2,6) (3,2) (1,1)
 * Node 5 (Neighbor, Weight): (1,5) (2,4) (3,4)
 * -------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h> // 使用malloc函数

#define MAX 11 // 📌 定义最大节点数,包含索引 0-10,我们只使用[1,10]

// 🧱 声明边的结构体:链表中的每一个节点代表一条边
struct EdgeNode
{
    int to;                // 🎯 这条边的终点节点编号
    int weight;            // ⚖️ 这条边的权重值
    struct EdgeNode *next; // 🔗 指向该起点引出的下一条边的指针
};

typedef struct EdgeNode EdgeNode; // 🏷️ 简化类型定义

// 📊 邻接表全局变量:指针数组,数组的每个下标代表图的一个节点
EdgeNode *adjList[MAX];

/**
 * 🧹 函数:build
 * 目的:初始化邻接表并释放内存,防止多次建图时发生内存泄漏
 * @param n 当前图中使用的最大节点编号
 */
void build(int n)
{
    // 遍历每一个节点的边链表
    for (int i = 0; i <= n; i++)
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

/**
 * 🔗 函数:addListEdge
 * 目的:向图中添加一条单向边 (u -> v, 权重 w)
 */
void addListEdge(int u, int v, int w)
{
    // 动态分配内存创建一个新的边节点
    EdgeNode *newNode = (EdgeNode *)malloc(sizeof(struct EdgeNode));
    newNode->to = v;     // 设置边的终点
    newNode->weight = w; // 设置边的权重

    // 采用"头插法",新节点插入到链表的最前端
    newNode->next = adjList[u]; // 新节点的 next 指向原来的表头
    adjList[u] = newNode;       // 更新表头为新加入的节点
}

/**
 * ➡️ 函数：directGraph
 * 目的:建立有向带权图
 * @param edges 边数据数组 [[起点, 终点, 权重], ...]
 * @param edgeSize 边的总数量
 */
void directGraph(int edges[][3], int edgeSize)
{
    for (int i = 0; i < edgeSize; i++) // 遍历输入的每一条边
    {
        int u = edges[i][0]; // 获取起点
        int v = edges[i][1]; // 获取终点
        int w = edges[i][2]; // 获取权重

        addListEdge(u, v, w); // 调用加边函数建立单向连接
    }
}

/**
 * ↔️ 函数：undirectGraph
 * 目的：建立无向带权图
 */
void undirectGraph(int edges[][3], int edgeSize)
{
    for (int i = 0; i < edgeSize; i++) // 遍历输入的每一条边
    {
        int u = edges[i][0]; // 节点 A
        int v = edges[i][1]; // 节点 B
        int w = edges[i][2]; // 权重

        // 无向图的一条边等价于两条有向边
        addListEdge(u, v, w); // 记录 u 到 v 的连接
        addListEdge(v, u, w); // 记录 v 到 u 的连接
    }
}

/**
 * 🔍 函数:traversal
 * 目的:遍历邻接表并打印输出
 * @param n 需要打印的节点总数
 */
void traversal(int n)
{
    printf("Adjacency List Traversal:\n");

    for (int i = 1; i <= n; i++) // 遍历编号为 1 到 n 的每一个节点
    {
        printf("Node %d (Neighbor, Weight): ", i); // 打印当前起点编号
        EdgeNode *cur = adjList[i];                // 指向该起点的边链表头
        while (cur)                                // 遍历该链表上的所有邻居
        {
            printf("(%d,%d) ", cur->to, cur->weight); // 打印 (终点, 权重) 对
            cur = cur->next;                          // 移动到下一条边
        }
        printf("\n"); // 换行,开始处理下一个节点
    }
}

/**
 * 🚀 主函数:程序执行入口
 */
int main()
{
    // 💡 例子 1:有向带权图测试
    int n1 = 4; // 使用节点 1, 2, 3, 4
    int edges1[][3] = {{1, 3, 6}, {4, 3, 4}, {2, 4, 2}, {1, 2, 7}, {2, 3, 5}, {3, 1, 1}};
    int size1 = sizeof(edges1) / sizeof(edges1[0]); // 计算边数

    build(n1);                  // 清空并初始化
    directGraph(edges1, size1); // 构建有向图
    traversal(n1);              // 打印结果

    printf("==============================\n");

    // 💡 例子 2:无向带权图测试
    int n2 = 5; // 使用节点 1, 2, 3, 4, 5
    int edges2[][3] = {{3, 5, 4}, {4, 1, 1}, {3, 4, 2}, {5, 2, 4}, {2, 3, 7}, {1, 5, 5}, {4, 2, 6}};
    int size2 = sizeof(edges2) / sizeof(edges2[0]); // 计算边数

    build(n2);                    // 再次初始化
    undirectGraph(edges2, size2); // 构建无向图
    traversal(n2);                // 打印结果

    return 0; // 程序正常结束
}
