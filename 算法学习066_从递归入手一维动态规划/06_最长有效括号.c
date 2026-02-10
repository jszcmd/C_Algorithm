// 最长有效括号
// 给你一个只包含 '(' 和 ')' 的字符串
// 找出最长有效（格式正确且连续）括号子串的长度.
// 测试链接 : https://leetcode.cn/problems/longest-valid-parentheses/

// 如果s[i]是'(', dp[i]=0;
// 如果s[i]是')', 根据dp[i-1]的长度往前跳到匹配的p位置,p = i-dp[i-1]-1
//                a:  s[p]是')', dp[i]=0
//                b:  s[p]是'(', dp[i]=dp[i-1]+2+dp[p-1],如果dp[p-1]不存在,则为0
//                c:  p<0,没有值了,那么dp[i]=0

#include <string.h>

int longestValidParentheses(char *s)
{
    int n = strlen(s);
    if (n == 0) // 有空字符串的情况
    {
        return 0; // 直接返回0
    }
    else // 非空字符串.
    {
        // dp[i]的含义:字串必须以i位置的字符结尾的情况下,往左最多推多远,能整体有效
        int dp[n];
        dp[0] = 0; // dp[0]的字符一定是0
        int ans = 0;
        for (int i = 1, p; i < n; i++)
        {
            if (s[i] == '(') // 如果s[i]是'(', dp[i]=0;
            {
                dp[i] = 0;
            }
            else // 如果s[i]是')', 根据dp[i-1]的长度往前跳到匹配的p位置,p = i-dp[i-1]-1
            {
                p = i - dp[i - 1] - 1;
                if (p < 0) // c:  p<0,没有值了,那么dp[i]=0
                {
                    dp[i] = 0;
                }
                else // p没有越界.
                {
                    if (s[p] == ')') // a:  s[p]是')', dp[i]=0
                    {
                        dp[i] = 0;
                    }
                    else // b:  s[p]是'(', dp[i]=dp[i-1]+2+dp[p-1],如果dp[p-1]不存在,则为0
                    {
                        dp[i] = dp[i - 1] + 2 + (p - 1 > 0 ? dp[p - 1] : 0);
                    }
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            ans = (ans > dp[i]) ? ans : dp[i];
        }
        return ans;
    }
}
