#include <stdio.h>
#include <stdbool.h>

// ==========================================
// 方法一：暴力枚举法 (Brute Force)
// ==========================================
// 逻辑:尝试从 1 开始,或者从 start 开始累加,看能否等于 num
// 缺点:时间复杂度高 (O(N^2)),如果 num 很大(比如 10^9),这个函数会超时.
// 作用:通常用于验证小数据的正确性,或者作为对比基准.
bool IsSumOfConsecutiveNumbers1(int num)
{
    int start = 0;
    int j = 0;
    int sum = 0;
    // 外层循环:枚举连续序列的"起点"start
    for (start = 0; start <= num; start++)
    {
        sum = start;
        // 内层循环:从起点往后累加
        for (j = start + 1; j <= num; j++)
        {
            // 如果加爆了(超过 num)说明以当前 start 为起点的序列不行,直接跳出
            if (sum + j > num)
            {
                break;
            }
            // 如果刚好等于 num,说明找到了!
            if (sum + j == num)
            {
                return true;
            }
            // 累加
            sum += j;
        }
    }
    // 试遍了所有起点都找不到,说明不能表示
    return false;
}


// 蓝桥杯测试链接:https://www.lanqiao.cn/problems/19714/learning/?page=1&first_category_id=1

// ==========================================
// 方法二:数学规律法 (Math / Bitwise) - 推荐解法
// ==========================================
#include <stdio.h>
#include <stdbool.h>

// 1. 核心判断: 是否为 2 的幂
// 参数使用 long long 防止大数溢出
bool isPowerOfTwo(long long n)
{
    // 利用位运算 n & (n-1) 快速判断
    return n > 0 && ((n & (n - 1)) == 0);
}

// 2. 业务逻辑: 判断是否"有诗意"
// 只有 2 的幂无法表示为连续整数之和 (缺乏诗意)
bool IsSumOfConsecutiveNumbers2(long long num)
{
    if ((num == 0) || isPowerOfTwo(num))
    {
        return false; // 是 2 的幂 -> 要删除
    }
    return true; // 非 2 的幂 -> 保留
}

int main()
{
    int n = 0;
    int ans = 0;        // 记录需要删除的数字个数
    long long temp = 0; // 【关键】必须用 long long 存大数

    if (scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; i++)
        {
            // 【关键】输入格式符必须是 %lld
            scanf("%lld", &temp);

            // 如果函数返回 false (说明它是 2 的幂)，则需要删除
            if (!IsSumOfConsecutiveNumbers2(temp))
            {
                ans++;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}
