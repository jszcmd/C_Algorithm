// 题目5
// 丑数 II
// 丑数 就是只包含质因数 2、3 或 5 的正整数
// 默认第1个丑数是1，前几项丑数为:
// 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 16, 18, 20,
// 24, 25, 27, 30, 32, 36, 40, 45, 48, 50, 54, 60,
// 64, 72, 75, 80, 81, 90, 96, 100, 108, 120, 125..
// 给你一个整数n ,请你找出并返回第n个丑数
// 比如,n = 37,返回125
// 测试链接 : https://leetcode.cn/problems/ugly-number-ii/

int min(int x, int y, int z)
{
    int min = (x < y) ? x : y;
    min = (min < z) ? min : z;
    return min;
}

int nthUglyNumber(int n)
{
    // 没有第0个丑数,下标0位置弃而不用
    int dp[n + 1]; // dp表要填写到第n项.dp[n]
    dp[1] = 1;     // 第一个丑数是1
    // i 当前在计算第i项丑数
    // i2的意思是 乘2 的指针停在哪一个下标
    // i3的意思是 乘3 的指针停在哪一个下标
    // i5的意思是 乘5 的指针停在哪一个下标
    for (int i = 2, i2 = 1, i3 = 1, i5 = 1, a, b, c, cur; i <= n; i++)
    {
        a = dp[i2] * 2;
        b = dp[i3] * 3;
        c = dp[i5] * 5;
        cur = min(a, b, c);
        if (cur == a)
            i2++;
        if (cur == b)
            i3++;
        if (cur == c)
            i5++;
        dp[i] = cur; // 把当前的丑数放在dp[i]的位置.
    }
    return dp[n];
}
