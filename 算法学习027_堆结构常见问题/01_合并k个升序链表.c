#include <stdio.h> // 导入头文件,使用NULL;

// 定义链表节点结构体
struct ListNode
{
    int val;               // 节点存储的整数值
    struct ListNode *next; // 指向下一个节点的指针
};

// 由于C语言没有现成的优先级队列,小根堆等数据结构;我们就用自己自己实现的小根堆;
// 力扣测试链接:https://leetcode.cn/problems/merge-k-sorted-lists/
// 牛客测试链接:https://www.nowcoder.com/practice/65cfde9e5b9b4cf2b6bafa5f3ef33fa6
// 力扣测试的数据量为10000
// 牛客测试的数据量为5000  ---> 可以自行调整,下面的就用10001
// 注意:力扣和牛客的测试链接都是填函数风格的,
// 函数名不要改变,下面的函数声明定义的顺序不能变; **** 提交的时候一定不要提交struct ListNode结构体

#define MAX 10001 // 定义堆的最大容量,根据题目数据范围设定

struct ListNode *min_heap[MAX]; // 最小堆数组,存储链表节点的指针
int size_heap = 0;              // 堆的当前大小,记录堆中元素个数

// 交换堆中两个位置的元素
// a: 第一个元素的索引位置
// b: 第二个元素的索引位置
void swap(int a, int b)
{
    struct ListNode *temp = min_heap[a]; // 临时保存a位置的指针
    min_heap[a] = min_heap[b];           // 将b位置的指针赋值给a位置
    min_heap[b] = temp;                  // 将临时保存的a位置指针赋值给b位置
}

// 向最小堆中添加一个新的链表节点
// x: 要添加的链表节点指针
void add(struct ListNode *x)
{
    min_heap[size_heap] = x; // 将新节点指针放入堆的末尾位置
    int i = size_heap++;     // 记录新节点的索引位置,同时堆大小加1
    // 向上调整堆，维持最小堆性质（父节点值小于等于子节点值）
    while (i > 0 && min_heap[i]->val < min_heap[(i - 1) / 2]->val)
    {
        swap(i, (i - 1) / 2); // 如果当前节点值小于父节点值,交换它们的位置
        i = (i - 1) / 2;      // 更新当前节点的位置为父节点位置,继续向上比较
    }
}

// 从最小堆中弹出值最小的元素(堆顶元素)
// 返回值: 堆顶元素的指针,即当前所有链表头节点中值最小的节点
struct ListNode *pop()
{
    struct ListNode *min = min_heap[0]; // 保存堆顶元素（最小元素）的指针
    swap(0, --size_heap);               // 将堆顶元素与最后一个元素交换，同时堆大小减1
    int i = 0;                          // 从堆顶开始向下调整
    int l = 2 * i + 1;                  // 计算左子节点的索引位置
    // 向下调整堆，维持最小堆性质
    while (l < size_heap)
    {
        // 找出左右子节点中值较小的那个
        int best = ((l + 1 < size_heap) && (min_heap[l + 1]->val < min_heap[l]->val)) ? l + 1 : l;
        // 比较当前节点与较小子节点的值，确定是否需要交换
        best = (min_heap[best]->val < min_heap[i]->val) ? best : i;
        if (best == i)
            break;     // 如果当前节点已经是最小的，堆性质满足，退出循环
        swap(best, i); // 交换当前节点与较小子节点的位置
        i = best;      // 更新当前节点的位置
        l = 2 * i + 1; // 重新计算左子节点位置，继续向下比较
    }
    return min; // 返回之前保存的最小元素指针
}

// 合并K个升序链表的主函数
// lists: 链表指针数组，每个元素指向一个升序链表的头节点
// listsSize: 链表数组的大小，即要合并的链表数量
// 返回值: 合并后的新链表的头节点指针
struct ListNode *mergeKLists(struct ListNode **lists, int listsSize)
{
    if (listsSize == 0)
        return NULL; // 如果链表数组为空，直接返回NULL
    size_heap = 0;   // 重置堆大小为0，清空堆

    // 遍历所有链表，将每个非空链表的头节点加入最小堆
    for (int i = 0; i < listsSize; i++)
    {
        if (lists[i] != NULL)
        {                  // 只处理非空链表
            add(lists[i]); // 将链表头节点加入最小堆
        }
    }
    if (size_heap == 0)
        return NULL; // 如果堆为空（所有链表都为空），返回NULL

    // 创建哑节点（dummy node），简化链表操作
    struct ListNode dummy = {-1, NULL}; // 哑节点的值设为-1，next指针初始为NULL
    struct ListNode *cur = &dummy;      // 当前指针指向哑节点，用于构建新链表

    // 循环直到堆为空（所有链表的所有节点都处理完毕）
    while (size_heap > 0)
    {
        struct ListNode *min_node = pop(); // 从堆中弹出当前最小节点
        cur->next = min_node;              // 将最小节点连接到新链表中
        cur = cur->next;                   // 移动当前指针到新连接的节点
        // 如果弹出的节点还有后续节点，将后续节点加入堆中继续比较
        if (min_node->next != NULL)
        {
            add(min_node->next); // 将下一个节点加入最小堆
        }
    }
    return dummy.next; // 返回哑节点的下一个节点，即合并后链表的真正头节点
}
