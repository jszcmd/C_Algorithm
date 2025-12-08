// 题目(2): 判断一个数是不是3的幂
// 测试链接: https://leetcode.cn/problems/power-of-three/

#include <stdio.h>
#include <stdbool.h>

// 逻辑分析:
// 1. 3 是一个质数 (Prime Number).
// 2. 在 32 位有符号整数 (int) 范围内, 最大的 3 的幂是 3^19 = 1162261467.
//    (因为 3^20 > 2147483647, 会溢出).
// 3. 原理: 因为 3 是质数, 所以 3^19 的因子只有 3^0, 3^1, ..., 3^19.
//    因此, 只要 n 是 3^19 的约数, n 就一定是 3 的幂.

bool isPowerOfThree(int n)
{
    // n > 0 : 3 的幂必须是正数.
    // 1162261467 % n == 0 : 检查 n 是否能整除 int 范围内最大的 3 的幂.
    return n > 0 && 1162261467 % n == 0;
}

int main()
{
    int n = 0;
    if (scanf("%d", &n) != EOF)
    {
        bool res = isPowerOfThree(n);
        printf("%d is power of 3? : %s\n", n, res ? "true" : "false");
    }
    return 0;
}
