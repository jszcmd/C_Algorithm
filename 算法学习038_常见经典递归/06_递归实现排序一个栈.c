// #########################################################################
// 单链表栈的实现
// #########################################################################

/**
 * 链栈实现说明文档
 *
 * 栈实现方式:
 * - 使用单向链表实现,无头节点设计
 * - 采用头插法:新元素始终插入链表头部,栈顶即为链表头
 * - 时间复杂度:所有基本操作均为 O(1)
 *
 * 栈结构：
 *   LinkStack
 *   ├── size: 栈中元素个数
 *   └── top: 指向栈顶元素的指针
 *        ↓
 *       [栈顶] -> [元素2] -> [元素1] -> ... -> NULL
 *
 * 操作函数列表：
 *
 * 1. 栈的创建与销毁:
 *    - LinkStack* InitStack()
 *        | 创建并初始化一个空栈
 *        | 返回值: 成功返回栈指针,失败返回NULL
 *
 *    - void DestoryStack(LinkStack* obj)
 *        | 完全销毁栈,释放所有内存
 *        | 参数: obj - 栈指针
 *
 *    - void ClearStack(LinkStack* obj)
 *        | 清空栈中所有元素,保留栈结构
 *        | 参数: obj - 栈指针
 *
 * 2. 栈的状态查询：
 *    - bool StackEmpty(LinkStack* obj)
 *        | 判断栈是否为空
 *        | 参数: obj - 栈指针
 *        | 返回值: 空返回true,非空返回false
 *
 *    - int StackLength(LinkStack* obj)
 *        | 获取栈中元素个数
 *        | 参数: obj - 栈指针
 *        | 返回值: 元素个数
 *
 * 3. 栈的基本操作：
 *    - bool Push(LinkStack* obj, int x)
 *        | 元素入栈
 *        | 参数: obj - 栈指针, x - 要入栈的元素值
 *        | 返回值: 成功返回true,失败返回false
 *
 *    - int Pop(LinkStack* obj)
 *        | 元素出栈
 *        | 参数: obj - 栈指针
 *        | 返回值: 成功返回出栈元素值,失败返回INT_MIN
 *
 *    - int GetTop(LinkStack* obj)
 *        | 获取栈顶元素(不弹出)
 *        | 参数: obj - 栈指针
 *        | 返回值: 成功返回栈顶元素值,失败返回INT_MIN
 *
 * 注意事项：
 * - 使用前必须调用InitStack()初始化栈
 * - 使用完毕后必须调用DestoryStack()释放内存
 * - 空栈时Pop()和GetTop()返回INT_MIN
 * - 所有函数都对空指针进行了安全检查
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// 定义链表节点结构
typedef struct ListNode
{
    int val;               // 节点存储的数据值
    struct ListNode *next; // 指向下一个节点的指针
} ListNode;

// 定义链栈结构
typedef struct LinkStack
{
    int size;      // 栈中元素个数
    ListNode *top; // 指向栈顶元素的指针(不使用头节点更加方便)
} LinkStack;

// 初始化一个栈
LinkStack *InitStack()
{
    LinkStack *obj = (LinkStack *)malloc(sizeof(LinkStack)); // 分配栈结构内存
    if (obj == NULL)
        return NULL; // 内存分配失败,返回NULL

    obj->size = 0;   // 初始时栈中元素个数为0
    obj->top = NULL; // 栈为空时top指针为NULL
    return obj;      // 返回创建的栈对象
}

// 清空栈(释放所有数据节点,但保留栈结构)
void ClearStack(LinkStack *obj)
{
    if (obj == NULL)
        return; // 如果栈对象为空,直接返回

    ListNode *cur = obj->top; // 从栈顶开始遍历
    while (cur != NULL)
    {
        ListNode *temp = cur->next; // 保存下一个节点的地址
        free(cur);                  // 释放当前节点内存
        cur = temp;                 // 移动到下一个节点
    }
    obj->top = NULL; // 栈顶指针置为NULL
    obj->size = 0;   // 元素个数重置为0
}

// 销毁栈(释放栈结构和所有数据节点)
void DestoryStack(LinkStack *obj)
{
    if (obj == NULL)
        return;      // 如果栈对象为空,直接返回
    ClearStack(obj); // 先清空所有数据节点
    free(obj);       // 再释放栈结构本身的内存
}

// 判断栈是否为空
bool StackEmpty(LinkStack *obj)
{
    if (obj == NULL)
        return true;       // 栈对象为空则认为栈为空
    return obj->size == 0; // 根据元素个数判断栈是否为空
}

// 获取栈中元素个数
int StackLength(LinkStack *obj)
{
    if (obj == NULL)
        return 0;     // 栈对象为空则返回0
    return obj->size; // 返回栈中元素个数
}

// 获取栈顶元素的值(不弹出)
int GetTop(LinkStack *obj)
{
    if ((obj == NULL) || (StackEmpty(obj)))
        return INT_MIN;   // 栈为空或对象为空返回最小值
    return obj->top->val; // 返回栈顶元素的值
}

// 元素入栈操作
bool Push(LinkStack *obj, int x)
{
    if (obj == NULL)
        return false; // 栈对象为空，操作失败

    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode)); // 创建新节点
    if (new_node == NULL)
        return false; // 内存分配失败,返回false

    new_node->val = x;         // 设置新节点的值
    new_node->next = obj->top; // 新节点指向原栈顶(头插法)
    obj->top = new_node;       // 更新栈顶指针指向新节点
    obj->size++;               // 栈中元素个数加1
    return true;               // 操作成功
}

// 元素出栈操作
int Pop(LinkStack *obj)
{
    if ((obj == NULL) || (StackEmpty(obj)))
        return INT_MIN; // 栈为空或对象为空返回最小值

    ListNode *top_node = obj->top; // 保存栈顶节点的地址
    int res = top_node->val;       // 保存栈顶元素的值
    obj->top = top_node->next;     // 栈顶指针指向下一个节点
    free(top_node);                // 释放原栈顶节点的内存
    obj->size--;                   // 栈中元素个数减1
    return res;                    // 返回出栈的元素值
}

// 打印栈的函数（从栈顶到栈底）
void PrintStack(LinkStack *stack)
{
    if (stack == NULL || StackEmpty(stack))
    {
        printf("栈为空\n");
        return;
    }

    printf("栈内容(栈顶→栈底): ");
    ListNode *current = stack->top;
    while (current != NULL)
    {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

// #########################################################################
// 单链表栈的实现
// #########################################################################

// #########################################################################
// 递归排序一个栈
// #########################################################################

/**
 * 递归计算栈的深度(不改变栈的数据顺序)
 * 通过递归弹出并重新压入的方式计算栈中元素个数
 *
 * @param stack 栈指针
 * @return 栈的深度(元素个数)
 */
int deep(LinkStack *stack)
{
    if (stack->size == 0)
        return 0;                // 基准情况:空栈深度为0
    int num = Pop(stack);        // 弹出栈顶元素
    int depth = deep(stack) + 1; // 递归计算剩余栈的深度并加1
    Push(stack, num);            // 恢复弹出的元素,保持栈原样
    return depth;
}

/**
 * 查找栈中前depth个元素的最大值
 * 递归遍历栈的前depth个元素,找到其中的最大值
 *
 * @param stack 栈指针
 * @param depth 要检查的深度(元素个数)
 * @return 前depth个元素中的最大值
 */
int depth_max(LinkStack *stack, int depth)
{
    if (depth == 0)
        return INT_MIN;                              // 基准情况:深度为0时返回最小值
    int num = Pop(stack);                            // 弹出栈顶元素
    int rest_max = depth_max(stack, depth - 1);      // 递归查找剩余元素的最大值
    int max_num = (num > rest_max) ? num : rest_max; // 比较当前元素与剩余最大值
    Push(stack, num);                                // 恢复弹出的元素
    return max_num;
}

/**
 * 统计栈中前depth个元素中最大值出现的次数
 *
 * @param stack 栈指针
 * @param depth 要检查的深度
 * @param max_num 要统计的目标最大值
 * @return 最大值在前depth个元素中出现的次数
 */
int times(LinkStack *stack, int depth, int max_num)
{
    if (depth == 0)
        return 0;                                                // 基准情况:深度为0时返回0次
    int num = Pop(stack);                                        // 弹出栈顶元素
    int rest_times = times(stack, depth - 1, max_num);           // 递归统计剩余元素
    int current_times = rest_times + ((num == max_num) ? 1 : 0); // 当前元素匹配则计数+1
    Push(stack, num);                                            // 恢复弹出的元素
    return current_times;
}

/**
 * 将栈中前depth个元素中的最大值下沉到指定位置
 * 这是一个关键步骤，用于将最大值移动到栈的底部
 *
 * @param stack 栈指针
 * @param depth 处理的深度
 * @param max_num 要下沉的最大值
 * @param k 最大值出现的次数
 */
void down(LinkStack *stack, int depth, int max_num, int k)
{
    if (depth == 0)
    {
        // 基准情况：处理完所有元素后，在栈底压入k个最大值
        int i = 0;
        for (i = 0; i < k; i++)
            Push(stack, max_num);
    }
    else
    {
        int num = Pop(stack);               // 弹出栈顶元素
        down(stack, depth - 1, max_num, k); // 递归处理剩余元素
        if (num != max_num)
        {
            Push(stack, num); // 如果不是最大值，重新压回栈中
        }
        // 如果是最大值，就不压回，相当于将其"过滤"掉
    }
}

/**
 * 递归排序算法的主函数
 * 使用递归方式对栈进行排序(数大的在栈底,数小的在栈顶)
 * 算法思路：
 * 1. 找到当前未排序部分的最大值及其出现次数
 * 2. 将这些最大值移动到栈底(已排序区域)
 * 3. 递归处理剩余未排序部分
 *
 * @param stack 要排序的栈指针
 */
void sort_stack(LinkStack *stack)
{
    int depth = stack->size; // 获取栈的当前深度
    // 也可以使用：int depth = deep(stack);   // 使用deep函数计算深度

    while (depth > 0)
    {
        int max_num = depth_max(stack, depth); // 找到前depth个元素的最大值
        int k = times(stack, depth, max_num);  // 统计最大值出现的次数
        down(stack, depth, max_num, k);        // 将最大值下沉到栈底
        depth -= k;                            // 减少待处理深度，排除已排序的最大值
    }
}

// #########################################################################
// 递归排序一个栈
// #########################################################################


// #########################################################################
// 数据测试...
// #########################################################################

// 主函数 - 测试排序算法
int main()
{
    // 创建栈
    LinkStack *stack = InitStack();
    if (stack == NULL)
    {
        printf("栈初始化失败!\n");
        return -1;
    }

    // 10个无序的数字
    int test_data[] = {7, 2, 9, 1, 5, 8, 3, 6, 4, 10};
    int data_count = sizeof(test_data) / sizeof(test_data[0]);

    printf("=== 栈排序算法测试 ===\n\n");

    // 压入无序数据
    printf("1. 压入10个无序数字到栈中:\n");
    for (int i = 0; i < data_count; i++)
    {
        Push(stack, test_data[i]);
        printf("压入: %d\n", test_data[i]);
    }

    printf("\n2. 压入后的栈状态:\n");
    PrintStack(stack);
    printf("栈大小: %d\n", StackLength(stack));

    // 执行排序
    printf("\n3. 开始执行递归排序...\n");
    sort_stack(stack);

    // 显示排序结果
    printf("\n4. 排序后的栈状态:\n");
    PrintStack(stack);
    printf("栈大小: %d\n", StackLength(stack));

    // 验证排序结果（从栈顶弹出所有元素）
    printf("\n5. 验证排序结果（弹出所有元素）:\n");
    printf("弹出顺序(栈顶→栈底): ");
    while (!StackEmpty(stack))
    {
        printf("%d ", Pop(stack));
    }
    printf("\n");

    // 清理资源
    DestoryStack(stack);

    printf("\n=== 测试完成 ===\n");

    return 0;
}
