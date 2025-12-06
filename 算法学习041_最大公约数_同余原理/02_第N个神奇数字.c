// 第 n 个神奇数字
// LeetCode 测试链接: https://leetcode.cn/problems/nth-magical-number/
// ===========================================

// 问题描述:
// 一个正整数如果能被 a 或 b 整除,那么它是神奇的.
// 给定三个整数 n, a, b,返回第 n 个神奇的数字.
// 因为答案可能很大,所以返回答案对 10^9 + 7 取模后的值.

// 算法思路:
//  计算 lcm = lcm(a, b)
//  使用二分查找,在 [min(a,b), min(a,b)*n] 范围内搜索
//  用容斥原理计算 [1, mid] 范围内的神奇数字个数:
//  count = mid//a + mid//b - mid//lcm
//  找到第 n 个神奇数字,对 MOD 取模

#define MOD 1000000007LL

// 求最大公因数
long gcd(long long a, long long b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

// 求最小公倍数
long long lcm(long long a, long long b)
{
    return a / gcd(a, b) * b;
}

int nthMagicalNumber(int n, int a, int b)
{
    long long my_lcm = lcm((long long)a, (long long)b);
    long long ans = 0;
    long long l = 0;
    long long r = (long long)n * (long long)((a < b) ? a : b);
    long long mid = (l + r) / 2;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (mid / a + mid / b - mid / my_lcm >= n)
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return ans % MOD;
}
