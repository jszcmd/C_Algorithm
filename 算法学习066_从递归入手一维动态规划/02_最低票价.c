// 最低票价
// 在一个火车旅行很受欢迎的国度，你提前一年计划了一些火车旅行
// 在接下来的一年里，你要旅行的日子将以一个名为 days 的数组给出
// 每一项是一个从 1 到 365 的整数
// 火车票有 三种不同的销售方式
// 一张 为期1天 的通行证售价为 costs[0] 美元
// 一张 为期7天 的通行证售价为 costs[1] 美元
// 一张 为期30天 的通行证售价为 costs[2] 美元
// 通行证允许数天无限制的旅行
// 例如，如果我们在第 2 天获得一张 为期 7 天 的通行证
// 那么我们可以连着旅行 7 天(第2~8天)
// 返回 你想要完成在给定的列表 days 中列出的每一天的旅行所需要的最低消费
// 测试链接 : https://leetcode.cn/problems/minimum-cost-for-tickets/

// 取一个: days  [3 , 4 , 9 , 20 ,50 ...] 为例子
//               0   1   2    3  4  ...
// 0 : 1天 -- a元   1: 7天 -- b元    2 : 30天 -- c元

// 假如我在第3天买了一张7天的票 : 那么接下来的: 3 4 5 6 7 8 9 这7天就不用愁了,都可以自由旅行了, 那么就从第9天开始.
// 假如:我在第3天买了一张30天的票: 那么接下来的: 3 4 5 ... 31 32 这30天都不用愁了, 那么就用第50天开始.

// 1天： a元 + f1(1....)从第days[1] -- 第4天开始的所有旅行的最小花销
// 7天： b元 + f1(3....)从第days[3]--- 第20天开始的所有旅行的最小花销
// 30天：c元 + f1(4...)从第days[4]--- 第50天开始的所有旅行的最小花销

// 假设我有做了一个决定: 先买了1天的票（第3天去旅游）,又买了1天的票（第4天去旅游）,又买了1天的票（第9天去旅游）
// 又买了1天的票（第20天去旅游） : 那么就是 4*a + f1(4.....) 从第days[4]天开始的所有旅游的最小花费.

// -------> 你看这样上面就会重复的计算:f1(4.....)
// 这样就是会有重复的计算.

// =================================================================================================
// 方法1: 暴力递归计算:
// 时间复杂度: O(3^n).  ----> 暴力递归过不了,时间超时.

#include <limits.h> // 使用INT_MAX 32位的int最大值.
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int durations[] = {1, 7, 30};
// 0号方案管着:1天 ---花费: costs[0]元
// 1号方案管着:7天 ---花费: costs[1]元
// 2号方案管着: 30天 --- 花费: costs[2]元.

// days[i .... ] 从days[i]开始,完成后面的所有的旅行的花销,所需要的最小的花费是多少.
int f1(int *days, int daysSize, int *costs, int i)
{
    if (i == daysSize) // 当i来到旅行下标的越界位置.
    {
        return 0; // 后续已经没有旅行了 --- 0花费
    }
    else // i是下标: 第days[i]天,有一场旅行,从第days[i]天之后,都旅行的最小花费
    {
        int ans = INT_MAX;                 // 我们要取最小的花费,一开始ans设置成无穷大
        for (int k = 0, j = i; k < 3; k++) // k是方案编号: 0 1 2
        {
            while (j < daysSize && (days[i] + durations[k] > days[j]))
            {
                j++;
            }
            ans = MIN(ans, costs[k] + f1(days, daysSize, costs, j));
        }
        return ans;
    }
}

int mincostTickets1(int *days, int daysSize, int *costs, int costsSize)
{
    return f1(days, daysSize, costs, 0); // 主函数从第days[0]开始,全部搞定的最小花销.
}

// =================================================================================================
// 方法2：从顶到低的动态规划,记忆化搜索.   ---> 先递归计算大的,把计算过程中的小的用缓存表记录下来
// 时间复杂度和空间复杂度: O(N)          ----> 从顶到低的动态规划

int f2(int *days, int daysSize, int *costs, int i, int *dp)
{
    if (i == daysSize) // i来到越界位置
        return 0;      // 返回0,也是递归结束条件.

    // i下标的这个值我之前展开过,计算过它的值,直接从缓存表里面拿.
    if (dp[i] != INT_MAX) // 之前展开过,直接从缓存表里面拿
    {
        return dp[i]; // 之前设置过.
    }
    else // 没有展开过,去递归展开.
    {
        int ans = INT_MAX;                 // 我们要取最小的花费,一开始ans设置成无穷大
        for (int k = 0, j = i; k < 3; k++) // k是方案编号: 0 1 2
        {
            while (j < daysSize && (days[i] + durations[k] > days[j]))
            {
                // 因为方案2持续的天数最多，30天
                // 所以while循环最多执行30次  ---> 但是这个天数不一定是紧挨着的情况.
                // 枚举行为可以认为是O(1)
                j++;
            }
            ans = MIN(ans, (costs[k] + f2(days, daysSize, costs, j, dp)));
        }
        dp[i] = ans; // 挂上缓存,方便下一次的.
        return ans;
    }
}

// 时间复杂度: 表的大小 * 单独一个格子(返回值)的枚举代价. ----> 时间复杂度: O(n)
int mincostTickets2(int *days, int daysSize, int *costs, int costsSize)
{
    int dp[daysSize];                  // 缓存表.
    for (int i = 0; i < daysSize; i++) // 一开始把所有的值都设置成为费用无穷大.
    {
        dp[i] = INT_MAX; // 一开始缓存表中的数据填充成为:无穷大 --- 表示没有计算过.
    }
    return f2(days, daysSize, costs, 0, dp);
}

// 测试链接 : https://leetcode.cn/problems/minimum-cost-for-tickets/
// =================================================================================================
// 方法3：实现一个从低到顶的，严格位置依赖的动态规划...   ----------> 从后往前计算.
// 时间复杂度: O(N)

int dp[366]; // 算上越界位置,最多366

int mincostTickets(int *days, int daysSize, int *costs, int costsSize)
{
    int n = daysSize;
    for (int i = 0; i <= n; i++)
        dp[i] = INT_MAX;

    dp[n] = 0; // 越界位置也要使用,花0元
    for (int i = n - 1; i >= 0; i--)
    {
        for (int k = 0, j = i; k < 3; k++)
        {
            while (j < daysSize && (days[i] + durations[k] > days[j]))
            {
                j++;
            }
            dp[i] = MIN(dp[i], costs[k] + dp[j]);
        }
    }

    return dp[0];
}
