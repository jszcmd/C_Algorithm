// 填写函数风格的测试
// 力扣测试链接:https://leetcode.cn/problems/sort-an-array/
// 直接把下面代码复制到力扣里面就可以通过了;
// 用C语言实现的很快;

#include <string.h> // 导入这个头文件,使用memset函数
#define BASE 1000   // 基数,使用1000进制进行排序(可以调整)
#define MAXN 50001  // 数组最大长度

int help[MAXN]; // 辅助数组,用于临时存储排序结果
int cnts[BASE]; // 统计数组,多少进制就准备多长的

// number在BASE进制下有几位
int bits(int number)
{
    int ans = 0;
    while (number > 0)
    {
        ans++;          // 位数加1
        number /= BASE; // 除以基数,去掉最低位
    }
    return ans;
}

// 基数排序的核心代码
// arr中要保证没有负数
// n是arr的长度
// bits是arr中最大值在bits进制下有几位
void radixSort(int arr[], int n, int bits)
{
    // 从最低位到最高位进行排序
    for (int offset = 1; bits > 0; offset *= BASE, bits--)
    {
        memset(cnts, 0, sizeof(cnts)); // 最开始把词频都初始化为0
        int i = 0;
        for (i = 0; i < n; i++) // 第一步:数字的词频统计
        {
            cnts[(arr[i] / offset) % BASE]++; // 数字提取某一位的技巧
        }
        for (i = 1; i < BASE; i++) // 第二步:处理前缀次数累加的形式
        {
            cnts[i] = cnts[i] + cnts[i - 1]; // 累计前缀和
        }
        for (i = n - 1; i >= 0; i--) // 第三步:开始分区,从右往左遍历(保证排序的稳定性)
        {
            // (arr[i] / offset) % BASE]: 这一位的数字
            help[--cnts[(arr[i] / offset) % BASE]] = arr[i]; // 从后往前放置元素
        }
        for (i = 0; i < n; i++) // 第四步:将排序结果从辅助数组复制回原数组
        {
            arr[i] = help[i]; // 复制当前轮的排序结果
        }
    }
}

int *sortArray(int *nums, int numsSize, int *returnSize)
{
    *returnSize = numsSize; // 一定要带上这一句,不然没有输出

    int n = numsSize;
    int i = 0;

    // 第一步:找到数组中的最小值
    int min = nums[0];
    for (i = 1; i < n; i++)
        min = (min < nums[i]) ? min : nums[i];

    // 第二步:将所有数转换为非负数,同时找到转换后的最大值
    int max = 0;
    for (i = 0; i < n; i++)
    {
        nums[i] -= min;                        // 减去最小值,消除负数
        max = (max > nums[i]) ? max : nums[i]; // 更新最大值
    }

    // 第三步:对非负数数组进行基数排序
    radixSort(nums, n, bits(max));

    // 第四步:恢复原始数值(加回之前减去的min)
    for (i = 0; i < n; i++)
        nums[i] += min;

    return nums; // 返回排序后的数组
}
