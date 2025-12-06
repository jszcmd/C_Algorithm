#include <stdio.h>

// 求a和b的最大公因数
// 时间复杂度:O(log(a)的三次方)
int gcd(int a, int b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

// 求a和b的最小公倍数
int lcm(int a, int b)
{
    return a / gcd(a, b) * b;
}

int main()
{
    // 我们这里测试的数比较小,所以函数的参数和返回值都设置成为了int类型的;
    int a = 0;
    int b = 0;
    scanf("%d %d", &a, &b);
    printf("最大公约数:%d\n", gcd(a, b));
    printf("最小公倍数:%d\n", lcm(a, b));
    return 0;
}

// 求50和30的最大公约数示例:

//  初始调用: gcd(50, 30)
//    50 ÷ 30 = 1 余 20
//    递归调用: gcd(30, 20)

//  第二次调用: gcd(30, 20)
//    30 ÷ 20 = 1 余 10
//    递归调用: gcd(20, 10)

//  第三次调用: gcd(20, 10)
//    20 ÷ 10 = 2 余 0
//    递归调用: gcd(10, 0)

//  第四次调用: gcd(10, 0)
//    b = 0,触发终止条件
//    返回结果: 10

// 调用链: gcd(50,30) → gcd(30,20) → gcd(20,10) → gcd(10,0) → 返回10
// 递归深度: 4层
