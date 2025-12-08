// ? 题目 6: 数组中只有一种数出现次数小于 m 次, 其他数都出现了 m 次
// ? 测试链接: https://leetcode.cn/problems/single-number-ii/
// ? 核心思想: 32位位统计法 (Bit Counting) + 模运算

#include <stdio.h>

/**
 * ?? 通用查找函数
 * @param arr 数组指针
 * @param len 数组长度
 * @param m   其他数出现的次数 (例如 3)
 * @return    那个只出现了一次的数
 */
int find(int arr[], int len, int m)
{
    // ? 准备一个长度为 32 的数组, 用来记录所有数字在每一位上的 1 的总数
    // cnts[0] 记录第 0 位(最低位)有多少个 1
    // cnts[31] 记录第 31 位(最高位)有多少个 1
    int cnts[32] = {0};
    int i = 0;
    int j = 0;

    // ? 遍历每一个数字
    for (i = 0; i < len; i++)
    {
        // ? 遍历这个数字的 32 个二进制位
        for (j = 0; j < 32; j++)
        {
            // (arr[i] >> j) & 1 : 取出第 i 个数在第 j 位上的状态 (0 或 1)
            cnts[j] += (arr[i] >> j) & 1;
        }
    }

    // ? 还原真身
    // 逻辑: 如果一个数出现了 m 次, 那么它在第 j 位上的 1 的贡献一定是 m 的倍数.
    //      cnts[j] % m != 0 说明那个"捣乱的数"在第 j 位上有 1.
    int ans = 0;
    for (j = 0; j < 32; j++)
    {
        if (cnts[j] % m != 0)
        {
            // ?? 关键修正: (unsigned int)1
            // 1 默认是 int (有符号), 直接左移 31 位会触碰符号位导致溢出报错 (Runtime Error).
            // 必须强转为无符号数, 告诉编译器"这是合法的位操作".
            ans |= (unsigned int)1 << j;
        }
    }
    return ans;
}

/**
 * ? LeetCode 接口函数
 * 题目设定 m = 3
 */
int singleNumber(int *nums, int numsSize)
{
    return find(nums, numsSize, 3);
}

int main()
{
    // ? 测试用例
    // 34 出现 1 次 (目标)
    // 1, 2, 5, 6 均出现 3 次 (背景板)
    int arr[] = {1, 2, 34, 5, 6, 6, 6, 5, 5, 2, 2, 1, 1};
    int len = sizeof(arr) / sizeof(arr[0]);

    // ? 直接调用封装好的函数, 不要在 main 里重写逻辑 (DRY原则)
    int ans = singleNumber(arr, len);

    printf("The single number is: %d \n", ans); // 预期输出 34

    return 0;
}
