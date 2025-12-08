// 题目(5): 数组中有2种数出现了奇数次, 其他数都出现了偶数次, 返回这2种数
// 测试链接: https://leetcode.cn/problems/single-number-iii/
// 核心逻辑: 分治法. 利用 a^b 的结果找到一位不同, 将数组拆分为两组, 从而退化为"找1个出现奇数次的数".

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // 为了使用 INT_MIN

int *singleNumber(int *nums, int numsSize, int *returnSize)
{
    // 1. 全员异或: 得到 result = a ^ b
    // 偶数次出现的数全部抵消,结果只剩下两个奇数次出现的数的异或和
    unsigned int eor1 = 0; // 使用unsigned int防止下面 -eor1溢出
    for (int i = 0; i < numsSize; i++)
    {
        eor1 ^= nums[i];
    }

    // 2. 提取区分位: 找到 a 和 b 在二进制上最右边不同的那一位 (Rightmost 1)
    int rightOne = eor1 & (-eor1);

    // 3. 分组异或: 根据 rightOne 那一位是 0 还是 1, 将数组分为两组
    // a 和 b 必然分别落在不同的组里.
    int eor2 = 0; // eor2 将只包含其中一个数(假设是 a)
    for (int i = 0; i < numsSize; i++)
    {
        // 只有在 rightOne 这一位上是 1 的数, 才参与异或
        if ((nums[i] & rightOne) != 0)
        {
            eor2 ^= nums[i];
        }
    }

    // 4. 计算结果
    // eor2 现在就是 a (或者 b) ; other = (a^b) ^ a = b
    int other = eor1 ^ eor2;

    // 5. 封装返回
    *returnSize = 2;
    int *arr = (int *)malloc(sizeof(int) * 2);
    arr[0] = eor2;
    arr[1] = other;
    return arr;
}

int main()
{
    // 测试用例: 1出现5次(奇), 46出现3次(奇), 其他均出现偶数次
    int arr[] = {1, 1, 2, 3, 46, 1, 78, 1, 78, 1, 2, 3, 46, 46};
    int len = sizeof(arr) / sizeof(arr[0]);
    int returnSize = 0;

    // 调用函数
    int *result = singleNumber(arr, len, &returnSize);

    // 打印结果
    printf("Found: %d and %d\n", result[0], result[1]);

    // 释放内存
    free(result);
    return 0;
}
