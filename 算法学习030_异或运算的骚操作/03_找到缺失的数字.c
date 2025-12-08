// 3.题目(3): 找到缺失的数字 [LeetCode: Missing Number]
// 核心逻辑: 利用异或性质 a^a=0, 将"理想全集0~n"与"实际数组"异或, 相同的抵消, 剩下的即为缺失项.
// 测试链接: https://leetcode.cn/problems/missing-number/
// 提交的时候只需要提交 missingNumber 这个函数

#include <stdio.h>

int missingNumber(int *nums, int numsSize)
{
    int eorAll = 0, eorHas = 0;        // eorAll存0~n的异或和, eorHas存数组元素的异或和
    for (int i = 0; i < numsSize; i++) // 遍历数组
    {
        eorAll ^= i;       // 累积异或下标: 0 到 n-1
        eorHas ^= nums[i]; // 累积异或数组中存在的元素
    }
    eorAll ^= numsSize;     // 补全范围: 异或上 n (因为循环只到了n-1)
    return eorAll ^ eorHas; // 此时 eorAll^eorHas = 理想^实际 = 缺失的数字
}

int main()
{
    int arr[10] = {1, 2, 6, 0, 9, 8, 7, 10, 3, 5}; // 0~10中缺了4
    printf("The missing num is : %d\n", missingNumber(arr, 10));
    return 0;
}
