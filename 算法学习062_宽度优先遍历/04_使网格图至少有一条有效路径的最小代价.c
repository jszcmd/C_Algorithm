/** 0-1 BFS (双端队列广度优先搜索) ::: LeetCode 1368
 * =========================================================================
 * 🚀 【算法模板练习】使网格图至少有一条有效路径的最小代价
 * #### 测试链接: https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/description/
 * -------------------------------------------------------------------------
 * 【描述】
 * 给你一个 m x n 的网格图 grid . grid 中每个格子都有一个数字,对应着从该格子出发下一步走的方向.
 * grid[i][j] 中的数字可能为以下几种情况:
 * - 1 :下一步往右走，也就是你会从 grid[i][j] 走到 grid[i][j + 1]
 * - 2 :下一步往左走，也就是你会从 grid[i][j] 走到 grid[i][j - 1]
 * - 3 :下一步往下走，也就是你会从 grid[i][j] 走到 grid[i + 1][j]
 * - 4 :下一步往上走，也就是你会从 grid[i][j] 走到 grid[i - 1][j]
 *
 * 注意网格图中可能会有 无效数字 ,因为它们可能指向 grid 以外的区域.
 *
 * 一开始,你会从最左上角的格子 (0,0) 出发.
 * 我们定义一条 有效路径 为从格子 (0,0) 出发，每一步都顺着数字对应方向走，最终在最右下角的格子 (m - 1, n - 1) 结束的路径.
 * 有效路径 不需要是最短路径 .
 *
 * 你可以花费 cost = 1 的代价修改一个格子中的数字,但每个格子中的数字 只能修改一次 .
 *
 * 请你返回让网格图至少有一条有效路径的最小代价.
 *
 * 【输入描述】
 * grid: 二维整数数组,表示网格图,其中 grid[i][j] 代表该格子的方向.
 * gridSize: 整数，表示行数 m.
 * gridColSize: 整数数组，表示每一行的列数.
 *
 * 【输出描述】
 * int: 返回让网格图至少有一条有效路径的最小代价.
 *
 * 【示例 1】
 * 输入: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
 * 输出: 3
 * 解释: 你将从点 (0, 0) 出发.
 * 到达 (3, 3) 的路径为:
 * (0, 0) --> (0, 1) --> (0, 2) --> (0, 3) 花费代价 cost = 1 使方向向下 -->
 * (1, 3) --> (1, 2) --> (1, 1) --> (1, 0) 花费代价 cost = 1 使方向向下 -->
 * (2, 0) --> (2, 1) --> (2, 2) --> (2, 3) 花费代价 cost = 1 使方向向下 -->
 * (3, 3)
 * 总花费为 cost = 3.
 * =========================================================================
 */

// =====================================================================================================
// 双端队列的实现
// =====================================================================================================
// 节点类型:arrNode  双端队列类型:Deque

// (1): 初始化一个新双端队列:
//     初始化包含一个虚拟头节点(Dummy Head)的队列
//     Deque* InitDeque();
//     返回值: 初始化的队列的地址(指针)

// (2): 判断队列是否为空:
//     参数: Deque* 类型的指针;
//     返回值: true (为空), false (不为空)
//     bool IsEmpty(Deque *obj);

// (3): 向队列的头部(左端)加入一个元素:
//     参数1: Deque* 队列的指针; 参数2: int x; 参数3: int y;
//     返回值: 无 (void)
//     void appendleft(Deque *obj, int x, int y);

// (4): 向队列的尾部(右端)加入一个元素:
//     参数1: Deque* 队列的指针; 参数2: int x; 参数3: int y;
//     返回值: 无 (void)
//     void append(Deque *obj, int x, int y);

// (5): 弹出队列头部(左端)的元素:
//     参数: Deque* 队列的指针;
//     返回值: 成功返回弹出的节点指针(arrNode*); 失败(队列为空)返回 NULL;
//     注意: 调用者负责 free 返回的节点指针
//     arrNode* popleft(Deque *obj);

// (6): 销毁队列:
//     释放队列中所有节点(包括虚拟头节点)以及队列结构体本身的内存
//     参数: Deque* 队列的指针;
//     void free_deque(Deque *obj);

#include <stdbool.h> // 使用bool数据类型
#include <stdlib.h>  // 使用malloc()|free()
#include <limits.h>  // 使用整数最大值

// 定义单链表链表结构体类型
struct arrNode
{
    int arr[2];           // 每一个元素
    struct arrNode *pre;  // 前驱
    struct arrNode *next; // 后继
};
typedef struct arrNode arrNode;

// 声明和定义Deque,链表实现的双端队列
struct Deque
{
    int size;      // size表示队列的长度;
    arrNode *head; // head代表头指针
    arrNode *tail; // tail指向队列的队尾的指针
};

typedef struct Deque Deque;

// 初始化双端队列
Deque *InitDeque()
{
    Deque *obj = (Deque *)malloc(sizeof(Deque));      // 申请Deque双端队列
    if (obj == NULL)                                  // 申请失败
        return NULL;                                  // 返回空指针
    arrNode *h1 = (arrNode *)malloc(sizeof(arrNode)); // 申请头节点
    if (h1 == NULL)                                   // 申请失败
    {
        free(obj);   // 释放刚刚申请的Deque双端队列
        return NULL; // 返回空指针
    }
    obj->head = obj->tail = h1;
    obj->head->next = NULL;
    obj->size = 0; // 队列初始化为0
    return obj;
}

bool IsEmpty(Deque *obj) // 判断队列是否为空
{
    return obj->size == 0;
}

// 向队列的左边加入一个元素
void appendleft(Deque *obj, int x, int y)
{
    // 先创建一个新的节点
    arrNode *newNode = (arrNode *)malloc(sizeof(arrNode));
    newNode->next = NULL;
    newNode->arr[0] = x;
    newNode->arr[1] = y;

    if (IsEmpty(obj)) // 如果队列为空,添加一个元素
    {
        obj->head->next = newNode; // 先处理后继 head --(next)--> newNode
        obj->tail = newNode;       // 更新tail指入的节点
        newNode->pre = obj->head;  // 先处理前驱
    }
    else // 队列里面的元素不为空
    {
        arrNode *p = obj->head->next; // 记录第一个有效节点
        // 处理后继关系:head --(next)--> arrNode(value) --(next)--> p
        obj->head->next = newNode;
        newNode->next = p;
        // 处理前驱关系:p(原本的队头) --(pre)--> arrNode(value) --(pre)--> head
        p->pre = newNode;
        newNode->pre = obj->head;
    }
    obj->size += 1;
}

// 向队列的尾部添加一个元素
void append(Deque *obj, int x, int y)
{
    arrNode *newNode = (arrNode *)malloc(sizeof(arrNode));
    newNode->next = NULL;
    newNode->arr[0] = x;
    newNode->arr[1] = y;
    if (IsEmpty(obj)) // (1):处理队列为空的情况
    {
        // 队列为空,加入一个元素后的队列: head(头节点)  ---  tail(也是new_node)
        obj->head->next = newNode; // 处理后继: head --(next)--> new_node
        obj->tail = newNode;       // tail指向新加入的节点
        newNode->pre = obj->head;  // 处理前驱: tail(也是new_node) --(pre)--> head(头节点)
    }
    else // (2):队列里面的元素不为空
    {
        obj->tail->next = newNode; // 处理后继: tail --(next)--> new_node
        newNode->pre = obj->tail;  // 处理前驱: new_node --(pre)--> tail
        obj->tail = newNode;       // 更新队尾tail
    }
    obj->size += 1;
}

// 弹出队列头部的元素
arrNode *popleft(Deque *obj)
{
    if (IsEmpty(obj)) // 队列为空
    {
        return NULL;
    }
    else // 队列不为空
    {
        arrNode *res = obj->head->next; // 第一个元素,要删除的节点
        if (obj->size == 1)             // (1):队列只有一个元素,删除后变为空队列
        {
            obj->head->next = NULL; // head的后继指向None
            obj->tail = obj->head;  // tail指向head
        }
        else // (2):队列中的元素不止一个
        {
            obj->head->next = res->next; // head指向新的头节点
            res->next->pre = obj->head;  // 新的头节点指向head;(res->next)就变成了第一个有效的节点
        }
        obj->size -= 1;
        return res;
    }
}

// 消除|释放队列
void free_deque(Deque *obj)
{
    arrNode *cur = obj->head;
    while (cur)
    {
        arrNode *temp = cur;
        cur = cur->next;
        free(temp); // 释放申请的结点
    }
    free(obj); // 释放Deque
    obj = NULL;
}

// =====================================================================================================
// 主函数 minCost()逻辑
// =====================================================================================================

int minCost(int **grid, int gridSize, int *gridColSize)
{
    // 方向数组: 对应题目定义的 1:右, 2:左, 3:下, 4:上
    // 技巧: 数组大小设为 5，让索引 1~4 直接对应题目中的方向值,0 索引留空不用
    int move[5][2] = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int m = gridSize;       // 行数
    int n = gridColSize[0]; // 列数
    int distance[m][n];     // 定义距离表: distance[i][j] 表示从起点到 (i,j) 的最小修改次数

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            distance[i][j] = INT_MAX; // 初始化距离表为无穷大
        }
    }

    Deque *deque = InitDeque(); // 初始化双端队列

    appendleft(deque, 0, 0); // 加入起点
    distance[0][0] = 0;      // 起点本身的代价是 0

    // 开始 0-1 BFS 循环
    while (!IsEmpty(deque))
    {
        // 1. 取出队头元素 (当前处理的节点)
        arrNode *record = popleft(deque);
        int x = record->arr[0];
        int y = record->arr[1];

        free(record);  // 数据取出后, 需要释放节点内存, 防止内存泄漏
        record = NULL; // 避免野指针

        // 2. 判断是否到达终点 (右下角)
        if (x == m - 1 && y == n - 1)
        {
            free_deque(deque);     // 返回前必须销毁队列
            return distance[x][y]; // 返回到右下角的最小代价
        }

        // 3. 遍历四个方向 (i 从 1 到 4,对应题目 grid 中的方向值)
        for (int i = 1; i <= 4; i++)
        {
            int nx = x + move[i][0]; // 下一步的 x
            int ny = y + move[i][1]; // 下一步的 y

            // 计算移动代价:
            // 如果 grid[x][y] 里的箭头方向 == 我们尝试走的方向 i,则不需要修改,代价为 0
            // 否则,我们需要消耗 1 次修改次数来改变箭头方向,代价为 1
            int weight = (grid[x][y] == i) ? 0 : 1;

            // 边界检查 && 发现更短路径则更新
            if ((0 <= nx && nx < m) && (0 <= ny && ny < n) && (distance[x][y] + weight < distance[nx][ny]))
            {
                distance[nx][ny] = distance[x][y] + weight; // 更新到达的最短距离
                // 0-1 BFS 核心逻辑:
                if (weight == 0) // 如果代价是 0 (顺着箭头走): 插队到【队头】,保证优先处理
                    appendleft(deque, nx, ny);
                else // 如果代价是 1 (改箭头方向): 排队到【队尾】,正常处理
                    append(deque, nx, ny);
            }
        }
    }

    free_deque(deque); // 释放队列
    return -1;
}
