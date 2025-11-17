#include <stdio.h>

// 力扣测试(填函数风格)
// 测试链接:https://leetcode.cn/problems/sort-an-array/

/**
 * 交换数组中两个元素的位置
 * @param arr 目标数组
 * @param a 第一个元素的索引
 * @param b 第二个元素的索引
 */
void swap(int arr[], int a, int b)
{
    int temp = arr[a]; // 临时保存第一个元素的值
    arr[a] = arr[b];   // 将第二个元素的值赋给第一个位置
    arr[b] = temp;     // 将临时保存的值赋给第二个位置
}

/**
 * 向下调整算法 - 维持大根堆结构
 * 当i位置的元素值变小时,将其向下调整到合适位置
 * @param arr 堆数组
 * @param i 需要调整的起始位置索引
 * @param size 当前堆的大小
 */
void heapify(int arr[], int i, int size)
{
    int l = 2 * i + 1; // 计算左孩子索引：基于完全二叉树的性质，左孩子位置为2*i+1
    // 当存在左孩子时继续循环调整：只要有左孩子就说明当前节点不是叶子节点
    while (l < size)
    {
        // 选择左右孩子中值较大的那个
        // 如果存在右孩子且右孩子值大于左孩子,选择右孩子,否则选择左孩子
        int best = (l + 1 < size && arr[l + 1] > arr[l]) ? l + 1 : l;
        // 比较当前节点与较大孩子的值，选择值更大的那个
        // 如果较大孩子比当前节点大，就选择孩子节点，否则保持当前节点
        best = (arr[best] > arr[i]) ? best : i;
        if (best == i)
            break;          // 如果当前节点已经是最大值,不需要继续调整，退出循环
        swap(arr, best, i); // 交换当前节点与较大孩子的位置：将较大的值向上移动
        i = best;           // 更新当前位置,继续向下调整：从交换后的位置继续检查
        l = 2 * i + 1;      // 重新计算左孩子索引：更新左孩子位置以便下一轮循环
    }
}

/**
 * 堆排序主函数
 * 使用大根堆实现数组的升序排序
 * @param arr 待排序数组
 * @param len 数组长度
 */
void heapSort(int arr[], int len)
{
    if (len <= 1)
        return; // 边界条件:数组长度小于等于1时直接返回，无需排序

    int i = 0;
    // 建堆阶段：从后往前遍历数组,对每个元素执行向下调整
    // 从最后一个元素开始向前遍历,逐步建立大根堆
    for (i = len - 1; i >= 0; i--)
    {
        heapify(arr, i, len); // 对当前位置i的元素执行向下调整，堆大小为整个数组长度
    }

    int size = len; // 当前堆的大小:初始时整个数组都是堆
    // 排序阶段：依次将最大值交换到末尾并调整堆
    // 每次循环将当前最大值放到数组末尾,然后缩小堆的范围
    while (size > 1)
    {
        swap(arr, 0, --size); // 将堆顶最大值交换到当前堆的末尾,堆大小减1
        // 先将size减1,然后将堆顶元素与新的末尾位置交换
        heapify(arr, 0, size); // 对新的堆顶元素执行向下调整,恢复堆性质
        // 交换后堆顶元素可能破坏堆结构，需要重新调整
    }
}

/**
 * 排序数组的接口函数
 * @param nums 待排序数组
 * @param numsSize 数组大小
 * @param returnSize 返回数组大小（与输入相同）
 * @return 排序后的数组
 */
int *sortArray(int *nums, int numsSize, int *returnSize)
{
    *returnSize = numsSize;   // 设置返回数组的大小：输出数组大小与输入相同
    heapSort(nums, numsSize); // 调用堆排序算法对数组进行排序
    return nums;              // 返回排序后的数组：原地排序，直接返回输入数组
}

#define MAXN 100001 // 根据题目数据范围定义

int arr[MAXN]; // 使用静态数组,避免动态分配开销

// 洛谷测试链接:https://www.luogu.com.cn/problem/P1177
// 把这个文件的代码都复制到洛谷里面.
// 洛谷测试注意要引入头文件#include <stdio.h>

// 竞赛级快速读入整数
static inline int read()
{
    int x = 0;
    char ch = getchar();
    // 跳过空白字符
    while (ch <= ' ')
        ch = getchar();
    // 读取数字
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x;
}

// 竞赛级快速输出整数
static inline void write(int x)
{
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

int main()
{
    // 快速读入N
    int N = read();

    // 快速读入N个整数
    for (int i = 0; i < N; i++)
        arr[i] = read();

    // 对数组进行排序
    heapSort(arr, N);

    // 快速输出结果
    for (int i = 0; i < N; i++)
    {
        write(arr[i]);
        if (i < N - 1)
        {
            putchar(' '); // 数字间空格
        }
    }
    putchar('\n'); // 行末换行

    return 0;
}
