/*
 * ======================================================================================
 * 题目:2127. 参加会议的最多员工数 (Maximum Employees to Be Invited to a Meeting)
 * #### 测试链接: https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/description/
 * 难度:困难 (Hard)
 * 来源:LeetCode
 * * 描述:
 * 一个公司准备组织一场会议,邀请名单上有 n 位员工。
 * 公司准备了一张 圆形 的桌子,可以坐下 任意数目 的员工.
 * * 员工编号为 0 到 n - 1 .每位员工都有一位 喜欢 的员工,每位员工 当且仅当 他被安排在喜欢员工的旁边,
 * 他才会参加会议.每位员工喜欢的员工 不会 是他自己.
 * * 给你一个下标从 0 开始的整数数组 favorite ,其中 favorite[i] 表示第 i 位员工喜欢的员工.
 * 请你返回参加会议的 最多员工数目.
 * ======================================================================================
 */

#include <string.h> // 使用memset()函数

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int maximumInvitations(int *favorite, int favoriteSize)
{
    // favorite数组本身就可以代表图: favorite[a] = b: a->b
    int n = favoriteSize;
    int indegree[n];                       // 入度表
    memset(indegree, 0, sizeof(indegree)); // 入度表初始化为0
    // 先统计入度
    for (int i = 0; i < n; i++)
    {
        indegree[favorite[i]]++; // 如a->b,b的入度就++
    }
    int queue[n];     // 队列
    int l = 0, r = 0; // 队列初始化为0
    int deep[n];      // deep[i]不包括i在内,i之前的最长链的长度
    memset(deep, 0, sizeof(deep));

    // 先把入度为0的点加入到队列
    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            queue[r++] = i; // 入度为0的节点入队列
        }
    }

    // 拓扑排序
    while (l < r)
    {
        int cur = queue[l++];                        // 弹出入度为0的人
        int next = favorite[cur];                    // cur喜欢的人(邻居)
        deep[next] = max(deep[next], deep[cur] + 1); // 维持最长链的长度
        if (--indegree[next] == 0)
        {
            queue[r++] = next; // 入度为0的节点入队列
        }
    }
    // 拓扑排序结束以后,目前,不在环上的点,都删除了!!! 不在环上面的节点i : indegree[i] = 0.
    // 可能性1: 所有小环(中心个数==2),算上中心点 + 延伸点  总个数
    int sumOfSmallRings = 0;
    // 可能性2: 所有大环(中心个数>2),只算中心点,最大环中心点个数
    int bigRings = 0;
    for (int i = 0; i < n; i++)
    {
        // 只关心环!!!
        if (indegree[i] > 0)
        {
            int ringSize = 1;
            indegree[i] = 0;
            for (int j = favorite[i]; j != i; j = favorite[j]) // j!=i,就一直绕圈
            {
                ringSize++;
                indegree[j] = 0; // 沿途把入度改成0,一个环只绕一次
            }
            if (ringSize == 2) // 遇到小环
            {
                sumOfSmallRings += 2 + deep[i] + deep[favorite[i]]; // 小环累加
            }
            else // 遇到大环
            {
                bigRings = max(bigRings, ringSize); // 大环取最大值
            }
        }
    }
    return max(sumOfSmallRings, bigRings); // 返回大环和小环的最大情况
}
