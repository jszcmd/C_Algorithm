// 4.题目(4): 找出出现奇数次的数 [LeetCode: Single Number]
// 核心逻辑: 利用 a^a=0 和 a^0=a, 偶数次出现的数会全部抵消, 仅保留奇数次那个.
// 测试连接: https://leetcode.cn/problems/single-number/

#include <stdio.h>

int singleNumber(int *nums, int numsSize)
{
    int eor = 0;                       // 0异或任何数不变
    for (int i = 0; i < numsSize; i++) // 遍历数组
    {
        eor ^= nums[i]; // 累积异或: 成对的数抵消为0, 最终只剩目标值
    }
    return eor;
}

int main()
{
    int arr[] = {1, 1, 2, 3, 46, 1, 78, 1, 78, 1, 2, 3, 46};
    int len = sizeof(arr) / sizeof(arr[0]);         // 计算数组长度
    printf("Result: %d\n", singleNumber(arr, len)); // 预期输出 1 (它出现了5次, 其他都是2次)
    return 0;
}
