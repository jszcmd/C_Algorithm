// 题目(1): 判断一个整数是不是2的幂
// 测试链接: https://leetcode.cn/problems/power-of-two/
// 提交的时候注意提交下面两个中任意一个IsPowerOfTwo函数,函数名一定不能变

#include <stdio.h>
#include <stdbool.h>

// 方法 1: Lowbit 提取法
// 原理: 提取出最右侧的 1, 看是否等于原数 n.
bool IsPowerOfTwo(int n)
{
    // 1. n must be positive.  a必须是正数
    // 2. Extract the rightmost bit (n & -n).  提取取出n的二进制中最右边的1
    // 3. Check if the rightmost bit equals n itself. 判断n的二进制是不是只有一个1
    return n > 0 && (n == (n & -n));
}

// 方法 2: 抹去最低位 1 (推荐, 更常用)
// 原理: 2的幂只有一个 1, 抹去后应该变成 0.
bool IsPowerOfTwo2(int n)
{
    // 1. n must be positive.
    // 2. (n & (n - 1)) removes the rightmost 1.
    // 3. If the result is 0, it means n had only one 1.
    return n > 0 && (n & (n - 1)) == 0;
}

int main()
{
    int n = 0;
    // 使用 long long 防止 scanf 警告, 但本题 int 足够演示逻辑
    if (scanf("%d", &n) != EOF)
    {
        // 建议优先使用方法 2
        bool res = IsPowerOfTwo2(n);
        printf("%d is power of 2? : %s\n", n, res ? "true" : "false");
    }
    return 0;
}
