// 不同的子序列 II
// 给定一个字符串 s，计算 s 的 不同非空子序列 的个数
// 因为结果可能很大，答案对 1000000007 取模
// 字符串的 子序列 是经由原字符串删除一些（也可能不删除）
// 字符但不改变剩余字符相对位置的一个新字符串
// 例如，"ace" 是 "abcde" 的一个子序列，但 "aec" 不是
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences-ii/

// s = "abc"
// 输出: 7
// 解释: 7 个不同的子序列分别是 "a", "b", "c", "ab", "ac", "bc", 以及 "abc".

// 输入: s = "aba"
// 输出: 6
// 解释: 6 个不同的子序列分别是 "a", "b", "ab", "ba", "aa" 以及 "aba".

// 输入: s = "aaa"
// 输出: 3
// 解释: 3 个不同的子序列分别是 "a", "aa" 以及 "aaa".

// 纯新增的数量: all - 当前字符的上次记录
// 当前字符记录 += 纯新增的数量
// all += 纯新增的数量

#include <string.h>
int distinctSubseqII(char *s)
{
    int n = strlen(s); // 字符串s的长度
    if (n == 0)        // 空字符串,就不用考虑了
    {
        return 0; // 直接返回0
    }
    else // 时间复杂度O(n),n是字符串s的长度
    {
        int mod = 1000000007; // 取模mod
        int cnt[26];
        memset(cnt, 0, sizeof(cnt)); // 初始化为全0
        int all = 1, newAdd = 0;
        for (int i = 0; i < n; i++)
        {
            char x = s[i];                                // 当前遍历到的字符
            newAdd = (all - cnt[x - 'a'] + mod) % mod;    // 纯新增的数量: all - 当前字符的上次记录
            cnt[x - 'a'] = (cnt[x - 'a'] + newAdd) % mod; // 当前字符记录 += 纯新增的数量
            all = (all + newAdd) % mod;                   // all += 纯新增的数量
        }
        return (all - 1 + mod) % mod;
    }
}
