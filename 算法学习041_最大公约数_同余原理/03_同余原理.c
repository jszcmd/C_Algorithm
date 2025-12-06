// *****加法的同余原理:
// 如果有:((a + b) + (c + d)) = m;
// (a + b) % MOD = m1 ; (c + d) % MOD = m2
// 那么:(m1+m2)%MOD = m

// *****乘法的同余原理:
// 如果有:((a * b) * (c * d)) % MOD = m;
// (a * b) % MOD = m1; (c *d) % MOD = m2;
// 那么:(m1 *m2) % MOD = m;

// *****减法的同余原理:
// 如果:(x) % 7 = -2 ; 那么就有:(x) % 7 = 5
// (a-b+MOD)%MOD 这样可以保证是正数;

#include <stdio.h>  // 标准输入输出函数
#include <stdlib.h> // 随机数函数和内存分配
#include <time.h>   // 时间函数

// 生成 [l, r] 范围内的随机整数
int randint(int l, int r)
{
    static int initialized = 0; // 静态变量，只在第一次调用时初始化为0
    if (!initialized)
    {
        srand(time(NULL)); // 设置随机数种子，使用当前时间
        initialized = 1;   // 标记已初始化，避免重复设置
    }
    // 生成[l, r]范围内的随机整数
    // rand() % (r - l + 1) 生成 [0, r-l] 范围的随机数
    // 加上 l 得到 [l, r] 范围的随机数
    return rand() % (r - l + 1) + l;
}

// 方法一：直接计算法
int f1(int a, int b, int c, int d, int mod)
{
    // 使用 long long 防止中间结果溢出
    // 注意：C语言中整数字面量默认是int类型,需要显式转换
    long long result = ((long long)a + b) * ((long long)c - d);
    result += ((long long)a * c - (long long)b * d);

    // 确保结果为非负数
    // 先加 mod 再取模，防止结果为负数
    result = (result % mod + mod) % mod;

    return (int)result;
}

// 方法二：逐步取模法
int f2(int a, int b, int c, int d, int mod)
{
    // 第一步：对每个输入取模
    int o1 = a % mod; // a 对 mod 取模
    int o2 = b % mod; // b 对 mod 取模
    int o3 = c % mod; // c 对 mod 取模
    int o4 = d % mod; // d 对 mod 取模

    // 第二步：计算 (a + b) % mod
    int o5 = (o1 + o2) % mod;

    // 第三步：计算 (c - d) % mod，+mod 确保结果非负
    int o6 = (o3 - o4 + mod) % mod;

    // 第四步：计算 (a * c) % mod，使用 long 防止乘法溢出
    int o7 = (int)((long long)o1 * o3 % mod);

    // 第五步：计算 (b * d) % mod，使用 long 防止乘法溢出
    int o8 = (int)((long long)o2 * o4 % mod);

    // 第六步：计算 ((a+b) * (c-d)) % mod
    int o9 = (int)((long long)o5 * o6 % mod);

    // 第七步：计算 (a*c - b*d) % mod，+mod 确保结果非负
    int o10 = (o7 - o8 + mod) % mod;

    // 第八步：计算最终结果
    int ans = (o9 + o10) % mod;

    return ans;
}

int main()
{
    printf("测试开始:\n");
    int testTimes = 10000; // 测试次数
    int mod = 1000000007;  // 模数 10^9 + 7

    for (int i = 0; i < testTimes; i++)
    {
        // 生成 [1, mod] 范围内的随机数
        int a = randint(1, mod);
        int b = randint(1, mod);
        int c = randint(1, mod);
        int d = randint(1, mod);

        // 比较两种方法的结果是否一致
        if (f1(a, b, c, d, mod) != f2(a, b, c, d, mod))
        {
            printf("测试失败！第 %d 次测试结果不一致\n", i + 1);
            printf("a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);
            printf("f1=%d, f2=%d\n", f1(a, b, c, d, mod), f2(a, b, c, d, mod));
            return 1; // 返回非0表示测试失败
        }
    }

    printf("测试结束: 所有 %d 次测试通过！\n", testTimes);
    printf("================================\n");

    // 显示一个具体示例
    printf("随机示例展示:\n");
    int a = randint(1, mod);
    int b = randint(1, mod);
    int c = randint(1, mod);
    int d = randint(1, mod);

    printf("a: %d\n", a);
    printf("b: %d\n", b);
    printf("c: %d\n", c);
    printf("d: %d\n", d);
    printf("------------------------\n");

    int result1 = f1(a, b, c, d, mod);
    int result2 = f2(a, b, c, d, mod);

    printf("f1(直接计算): %d\n", result1);
    printf("f2(逐步取模): %d\n", result2);

    if (result1 == result2)
    {
        printf("结果一致\n");
    }
    else
    {
        printf("结果不一致\n");
    }

    return 0;
}
