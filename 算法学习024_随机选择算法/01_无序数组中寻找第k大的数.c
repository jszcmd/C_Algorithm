#include <stdlib.h>
#include <time.h>

// 力扣测试连接:https://leetcode.cn/problems/kth-largest-element-in-an-array/
// 用C语言实现真的很快,这段代码的内容很短的,只不过是用AI美化了一下注释

// 分区边界全局变量
static int first = 0; // 等于区的起始位置
static int last = 0;  // 等于区的结束位置

// 生成指定范围内的随机整数
// 参数：l - 范围下限（包含），r - 范围上限（包含）
// 返回：[l, r]范围内的随机整数
int randint(int l, int r)
{
    static int initialized = 0; // 种子初始化标志

    if (!initialized)
    {
        srand(time(NULL)); // 用当前时间初始化随机种子
        initialized = 1;   // 标记已初始化
    }

    return rand() % (r - l + 1) + l; // 生成随机数
}

// 交换数组中的两个元素
// 参数：arr - 目标数组，a - 第一个元素索引，b - 第二个元素索引
void swap(int arr[], int a, int b)
{
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

// 三路快速排序分区算法
// 将数组arr[l..r]划分为三个区域：
//   [l, first-1] : 小于基准值的元素
//   [first, last] : 等于基准值的元素
//   [last+1, r]   : 大于基准值的元素
// 参数：arr - 待分区数组，l - 分区左边界，r - 分区右边界，x - 基准值
void partition(int arr[], int l, int r, int x)
{
    first = l; // 初始化小于区边界
    last = r;  // 初始化大于区边界
    int i = l; // 当前扫描指针

    // 扫描整个区间
    while (i <= last)
    {
        if (arr[i] == x)
        {
            i++; // 等于基准值，留在中间
        }
        else if (arr[i] < x)
        {
            swap(arr, first++, i++); // 小于基准值，交换到左边
        }
        else
        {
            swap(arr, last--, i); // 大于基准值，交换到右边
        }
    }
}

// 快速选择算法：在未排序数组中查找第i小的元素
// 算法思想：随机选择基准值进行分区，只在包含目标的子区间中递归搜索
// 参数：arr - 输入数组，len - 数组长度，i - 目标位置（0-indexed）
// 返回：排序后会在位置i的元素值
// 平均复杂度：O(n)，最坏复杂度：O(n?)
int randomizedSelect(int arr[], int len, int i)
{
    int ans = 0;     // 存储最终结果
    int l = 0;       // 搜索区间左边界
    int r = len - 1; // 搜索区间右边界

    // 迭代搜索目标元素
    while (l <= r)
    {
        // 随机选择基准值并分区
        partition(arr, l, r, arr[randint(l, r)]);

        // 根据分区结果调整搜索区间
        if (i < first)
        {
            r = first - 1; // 目标在左分区
        }
        else if (i > last)
        {
            l = last + 1; // 目标在右分区
        }
        else
        {
            ans = arr[i]; // 找到目标
            break;
        }
    }

    return ans;
}

// 查找数组中第K大的元素
// 核心转换：第k大 = 排序后第(n-k)个元素（0-indexed）
// 参数：nums - 输入数组，numsSize - 数组大小，k - 第k大（1-indexed）
// 返回：第k大的元素值
int findKthLargest(int *nums, int numsSize, int k)
{
    return randomizedSelect(nums, numsSize, numsSize - k);
}
