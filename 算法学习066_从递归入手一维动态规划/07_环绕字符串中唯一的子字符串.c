// 环绕字符串中唯一的子字符串
// 定义字符串 base 为一个 "abcdefghijklmnopqrstuvwxyz" 无限环绕的字符串
// 所以 base 看起来是这样的：
// "..zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd.."
// 给你一个字符串 s ，请你统计并返回 s 中有多少 不同非空子串 也在 base 中出现
// 测试链接 : https://leetcode.cn/problems/unique-substrings-in-wraparound-string/

#include <string.h>

int findSubstringInWraproundString(char *s)
{
    int n = strlen(s);
    int numStr[n];
    // 'a' --> 0 ; 'b' --> '1' ; ... ; 'z' --> 25
    for (int i = 0; i < n; i++)
    {
        numStr[i] = s[i] - 'a'; // 把字符数组,对应成数字数组.
    }
    // dp[0] 表示在s中必须以'a'结尾的字串,最大延伸的长度是多少,延伸一定要根据base串的规则.
    int dp[26];
    memset(dp, 0, sizeof(dp)); // 初始化为全0.
    // s串中第1个字符,s[0],dp[s[0]-'a'] = 0;
    dp[numStr[0]] = 1;
    for (int i = 1, cur, pre, len = 1; i < n; i++)
    {
        cur = numStr[i];     // 当前字符
        pre = numStr[i - 1]; // 上一个字符.
        // (pre == 25)前一个字符是'z' && (cur == 0)当前字符是'a'
        // 或者前一个字符的ASCII码比后一个字符的ASCII码少一个,也是可以延伸的
        if ((pre == 25) && (cur == 0) || (pre + 1 == cur))
        {
            len++; // 能够延伸,len长度加1
        }
        else // 不能延伸
        {
            len = 1; // 就是只有当前字符,len=1
        }
        dp[cur] = (dp[cur] > len) ? dp[cur] : len; // 更新dp表中当前字符的能够延伸的长度
    }
    int ans = 0;
    for (int i = 0; i < 26; i++)
    {
        ans += dp[i]; // 长度累加.
    }
    return ans;
}
