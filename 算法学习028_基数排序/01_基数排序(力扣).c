// 填写函数风格的测试
// 力扣测试链接:https://leetcode.cn/problems/sort-an-array/
// 直接把下面代码复制到力扣里面就可以通过了;
// 用C语言实现的很快;

#include <stdio.h>
#include <string.h> // 导入这个头文件,使用memset函数
#define BASE 1000   // 基数,使用1000进制进行排序(可以调整)
#define MAXN 50001  // 数组最大长度

int help[MAXN]; // 辅助数组,用于临时存储排序结果
int cnts[BASE]; // 计数器数组,用于统计每个"数字"的出现次数

/**
 * @brief 计算数字在BASE进制下的位数
 * @param number 要计算位数的数字
 * @return 数字在BASE进制下的位数
 */
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

/**
 * @brief 基数排序的核心逻辑
 * @param arr 要排序的数组,arr内要保证没有负数
 * @param n 参数n是arr的长度
 * @param bits 是arr中最大值在BASE进制下有几位,同时控制排序进行几轮
 */
void radixSort(int arr[], int n, int bits)
{
    int offset = 0;
    // 从最低位到最高位进行排序
    for (offset = 1; bits > 0; offset *= BASE, bits--)
    {
        memset(cnts, 0, sizeof(cnts)); // 每轮开始前清空计数器

        int i = 0;
        // 第一步:数字的词频统计
        // 统计当前位上每个"数字"(0到BASE-1)的出现次数
        for (i = 0; i < n; i++)
        {
            cnts[(arr[i] / offset) % BASE]++; // 提取当前位的数字并计数
        }

        // 第二步:处理成前缀次数累加的形式
        // 这样cnts[i]就表示小于等于i的数字有多少个
        for (i = 1; i < BASE; i++)
        {
            cnts[i] = cnts[i] + cnts[i - 1]; // 累计前缀和
        }

        // 第三步:开始分区,从右往左遍历(保证排序的稳定性)
        // 根据计数器的位置信息,将元素放入辅助数组的正确位置
        for (i = n - 1; i >= 0; i--)
        {
            help[--cnts[(arr[i] / offset) % BASE]] = arr[i]; // 从后往前放置元素
        }

        // 第四步:将排序结果从辅助数组复制回原数组
        for (i = 0; i < n; i++)
        {
            arr[i] = help[i]; // 复制当前轮的排序结果
        }
    }
}

/**
 * @brief 主排序函数
 * @param nums 待排序的整数数组
 * @param numsSize 数组长度
 * @param returnSize 返回数组长度(输出参数)
 * @return 排序后的数组
 */
int *sortArray(int *nums, int numsSize, int *returnSize)
{
    *returnSize = numsSize; // 一定要带上这一句,不然没有输出

    int n = numsSize;
    int min = nums[0];
    int i = 0;

    // 第一步:找到数组中的最小值
    for (i = 1; i < n; i++)
    {
        min = (min < nums[i]) ? min : nums[i]; // 三元运算符找最小值
    }

    int max = 0;
    // 第二步：将所有数转换为非负数
    // 同时找到转换后的最大值
    for (i = 0; i < n; i++)
    {
        nums[i] -= min;                        // 减去最小值,消除负数
        max = (max > nums[i]) ? max : nums[i]; // 更新最大值
    }

    // 第三步：对非负数数组进行基数排序
    radixSort(nums, n, bits(max));

    // 第四步：恢复原始数值(加回之前减去的min)
    for (i = 0; i < n; i++)
    {
        nums[i] += min;
    }

    return nums; // 返回排序后的数组
}
