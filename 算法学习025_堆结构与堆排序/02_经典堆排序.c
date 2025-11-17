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
 * 向上调整算法 - 维持大根堆结构
 * 将i位置的元素向上调整，直到满足大根堆条件或到达根节点
 * @param arr 堆数组
 * @param i 需要调整的元素索引
 */
void heapInsert(int arr[], int i)
{
    // 当不是根节点且当前节点值大于父节点值时，继续向上调整
    while (i > 0 && arr[i] > arr[(i - 1) / 2])
    {
        swap(arr, (i - 1) / 2, i); // 交换当前节点与父节点
        i = (i - 1) / 2;           // 更新当前位置为父节点位置，继续向上检查
    }
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
    int l = 2 * i + 1; // 计算左孩子索引
    // 当存在左孩子时继续循环调整
    while (l < size)
    {
        // 选择左右孩子中值较大的那个
        // 如果存在右孩子且右孩子值大于左孩子,选择右孩子,否则选择左孩子
        int best = (l + 1 < size && arr[l + 1] > arr[l]) ? l + 1 : l;
        // 比较当前节点与较大孩子的值，选择值更大的那个
        best = (arr[best] > arr[i]) ? best : i;
        if (best == i)
            break;          // 如果当前节点已经是最大值,不需要继续调整
        swap(arr, best, i); // 交换当前节点与较大孩子的位置
        i = best;           // 更新当前位置,继续向下调整
        l = 2 * i + 1;      // 重新计算左孩子索引
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
        return; // 边界条件:数组长度小于等于1时直接返回

    int i = 0;
    // 建堆阶段：从前往后逐个插入,建立大根堆
    // 时间复杂度: O(n log n)
    for (i = 0; i < len; i++)
    {
        heapInsert(arr, i); // 对每个元素执行向上调整
    }

    int size = len; // 当前堆的大小
    // 排序阶段：依次将最大值交换到末尾并调整堆
    // 时间复杂度: O(n log n)
    while (size > 1)
    {
        swap(arr, 0, --size);  // 将堆顶最大值交换到当前堆的末尾,堆大小减1
        heapify(arr, 0, size); // 对新的堆顶元素执行向下调整,恢复堆性质
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
    *returnSize = numsSize;   // 设置返回数组的大小
    heapSort(nums, numsSize); // 调用堆排序算法
    return nums;              // 返回排序后的数组
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
