/*
* =================================================================================
 * 📘 题目: P3370 【模板】字符串哈希
 * 🔗 来源: 洛谷 (Luogu)
 * #### 测试链接:https://www.luogu.com.cn/problem/P3370
 * =================================================================================
 * * 【题目描述】
 * 如题,给定 N 个字符串(字符串内包含数字、大小写字母,大小写敏感),
 * 请求出 N 个字符串中共有多少个不同的字符串.
 * * 友情提醒:如果真的想好好练习哈希的话,请自觉.
 *
 * --------------------------------------------------------------------------------
 * 【输入格式】
 * 第一行包含一个整数 N,为字符串的个数.
 * 接下来 N 行每行包含一个字符串,为所提供的字符串.
 *
 * 【输出格式】
 * 输出包含一行,包含一个整数,为不同的字符串个数.
 *
 * --------------------------------------------------------------------------------
 * 🌟 样例输入:
 * 5
 * abc
 * aaaa
 * abc
 * abcc
 * 12345
 *
 * 🌟 样例输出:
 * 4
 * =================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10001       // 题目最大字符串数量
#define BASE 499         // 哈希进制数(通常取质数减少冲突)
#define MAX_STR_LEN 1501 // 单个字符串最大长度

// ⚠️ C语言 unsigned long long 自然溢出等价于对 2^64 取模
// 必须保证是 64 位,避免 32 位系统下碰撞率过高
unsigned long long nums[MAXN];
int n; // 输入的字符串个数
char buffer[MAX_STR_LEN]; // 临时读入缓冲区

// 🔢 [字符映射] 将字符 '0'-'z' 映射为数值 1-62
int v(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0' + 1;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 11;
    } else {
        return c - 'a' + 37;
    }
}

// 🧮 [核心] 计算字符串哈希值 (Rolling Hash)
unsigned long long value(char *s) {
    if (s == NULL || *s == '\0') return 0;
    int len = strlen(s); // 获取长度
    unsigned long long ans = v(s[0]);
    int i;
    // 迭代计算: hash = hash * BASE + value
    for (i = 1; i < len; i++) {
        ans = ans * BASE + v(s[i]);
    }
    return ans;
}

// ⚖️ [辅助] qsort 比较函数 (升序)
int cmp(const void *a, const void *b) {
    unsigned long long arg1 = *(const unsigned long long *) a;
    unsigned long long arg2 = *(const unsigned long long *) b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

// 📊 [统计] 排序并统计不同元素的个数
int cnt() {
    if (n == 0) return 0;
    // 1. 排序: 让相同的哈希值排在一起
    qsort(nums, n, sizeof(unsigned long long), cmp);

    int ans = 1; // 第一个元素肯定算一种
    int i;
    // 2. 遍历: 只要当前值 != 前一个值, 说明是新种类
    for (i = 1; i < n; i++) {
        if (nums[i] != nums[i - 1]) ans++;
    }
    return ans;
}

int main() {
    // 1. 读入字符串总数
    if (scanf("%d", &n) != 1) return 0;

    int i;
    // 2. 循环读入并计算哈希
    for (i = 0; i < n; i++) {
        scanf("%s", buffer); // 读入字符串到缓冲
        nums[i] = value(buffer); // 算出哈希值存入数组
    }

    // 3. 统计并输出结果
    printf("%d\n", cnt());
    return 0;
}
