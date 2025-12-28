/** 0-1 BFS (双端队列广度优先搜索) ::: LeetCode 2290
 * =========================================================================
 * 🚀 【算法模板练习】到达角落需要移除障碍物的最小数目
 * #### 测试链接: https://leetcode.cn/problems/minimum-obstacle-removal-to-reach-corner/
 * -------------------------------------------------------------------------
 * 【描述】
 * 给你一个下标从 0 开始的二维整数数组 grid ，数组大小为 m x n 。
 * 每个单元格都是两个值之一：
 * - 0 表示一个 空 单元格，
 * - 1 表示一个可以移除的 障碍物 。
 * * 你可以向上、下、左、右移动，从一个空单元格移动到另一个空单元格。
 * 现在你需要从左上角 (0, 0) 移动到右下角 (m - 1, n - 1) ，
 * 返回需要移除的障碍物的 最小 数目.
 *
 * 【输入描述】
 * grid: 二维整数数组，大小为 m x n.
 * gridSize: 整数，表示行数 m.
 * gridColSize: 整数数组，表示每一行的列数 (通常 gridColSize[0] 即为 n).
 *
 * 【输出描述】
 * int: 返回一个整数，表示从左上角到右下角需要移除障碍物的最小数量.
 *
 * 【示例 1】
 * 输入: grid = [[0,1,1],[1,1,0],[1,1,0]]
 * 输出: 2
 * 解释:
 * 可以移除位于 (0, 1) 和 (0, 2) 的障碍物来创建从 (0, 0) 到 (2, 2) 的路径。
 * 路径为 (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2)。
 * * 【示例 2】
 * 输入: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]]
 * 输出: 0
 * 解释: 不移除任何障碍物就能从 (0, 0) 到 (2, 4)。
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
// 主函数minimumObstacles()逻辑
// =====================================================================================================

int minimumObstacles(int **grid, int gridSize, int *gridColSize)
{
    int move[] = {-1, 0, 1, 0, -1}; // 方向数组技巧: 配合循环使用 (-1,0)上, (0,1)右, (1,0)下, (0,-1)左
    int m = gridSize;               // m行
    int n = gridColSize[0];         // n列
    int distance[m][n];             // 定义距离表: distance[i][j] 表示从起点到 (i,j) 需要移除的最少障碍物数量

    // 初始化距离表
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            distance[i][j] = INT_MAX; // 初始化为无穷大, 表示尚未到达
        }
    }

    Deque *deque = InitDeque(); // 初始化双端队列

    appendleft(deque, 0, 0); // 加入第一个元素 (起点)
    distance[0][0] = 0;  // 起点本身的代价是0

    // 开始 BFS 循环
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
            return distance[x][y]; // 返回到右下角的代价
        }

        // 3. 遍历四个方向 (上、右、下、左)
        for (int i = 0; i < 4; i++)
        {
            int nx = x + move[i], ny = y + move[i + 1];
            // 边界判断 (不越界) && 只有发现更短的路径才更新
            // distance[x][y] + grid[nx][ny] 是指: 到达当前点代价 + 到达下一点的开销(0或1)
            if ((0 <= nx && nx < m) && (0 <= ny && ny < n) && (distance[x][y] + grid[nx][ny] < distance[nx][ny]))
            {
                distance[nx][ny] = distance[x][y] + grid[nx][ny]; // 更新到达邻居的最短距离
                // 0-1 BFS 核心逻辑:
                if (grid[nx][ny] == 0)
                    appendleft(deque, nx, ny); // 权值为0 (空地): 放到队头, 优先处理
                else
                    append(deque, nx, ny); // 权值为1 (障碍): 放到队尾, 正常排队
            }
        }
    }

    free_deque(deque); // 释放队列
    return -1;
}
