// 2.题目2):不用任何判断语句和比较操作,返回两个数的最大值
// 测试链接:https://www.nowcoder.com/practice/d2707eaf98124f1e8f1d9c18ad487f76
// 提交的时候提交下面的主要的3个函数(flip,sign,getMax)就可以了

#include <stdio.h>
#include <limits.h>

/**
 * 辅助函数:位反转
 * 如果 n 是 0,返回 1
 * 如果 n 是 1,返回 0
 * 原理:异或运算,相同为0,不同为1.0^1=1, 1^1=0
 */
int flip(int n)
{
    return n ^ 1;
}

/**
 * 核心逻辑:获取符号状态(经过映射)
 * 这里的逻辑是：
 * 1. (unsigned int)n >> 31:取符号位.
 * - 如果 n 是非负数(0或正),符号位是0,右移后结果是 0
 * - 如果 n 是负数,符号位是1,右移后结果是 1
 * 2. 调用 flip 进行反转:
 * - 非负数(符号位0)-> flip(0) -> 返回 1
 * - 负数(符号位1)  -> flip(1) -> 返回 0
 * * 总结:n >= 0 返回 1;n < 0 返回 0
 */
int sign(int n)
{
    // 注意:这里强转 unsigned int 是为了执行逻辑右移(高位补0),
    // 避免部分编译器对 signed int 执行算术右移(高位补符号位)导致结果不为0或1
    return flip((unsigned int)n >> 31);
}

/**
 * 方法一:基础版本(有溢出风险)
 * 逻辑很简单:看 c = a - b 的符号.
 * 如果 c >= 0,说明 a >= b,返回 a
 * 如果 c < 0, 说明 a < b, 返回 b
 * * 致命缺陷:如果 a 是极大正数,b 是极小负数,a - b 会溢出变成负数,导致判断出错.
 */
int getMax1(int a, int b)
{
    int c = a - b;
    int returnA = sign(c);       // 如果 c >= 0,returnA = 1;否则 = 0
    int returnB = flip(returnA); // 如果 returnA 是 1,returnB 就是 0;反之亦然

    // 利用互斥系数 returnA 和 returnB 来选择返回 a 还是 b
    return a * returnA + b * returnB;
}

/**
 * 方法二：进阶版本(解决溢出问题)
 * 这个函数通过分情况讨论来避免直接依赖 a-b 的结果
 */
int getMax(int a, int b)
{
    // 先计算 c,虽然可能溢出,但我们在某些情况下不依赖它
    int c = a - b;

    // 获取 a, b, c 的符号状态(1表示非负,0表示负)
    int sa = sign(a);
    int sb = sign(b);
    int sc = sign(c);

    // 判断 a 和 b 的符号是否不同
    // 异或操作:相同为0,不同为1
    int diffAB = sa ^ sb;      // 如果符号不同,diffAB = 1
    int sameAB = flip(diffAB); // 如果符号相同,sameAB = 1

    // 什么时候应该返回 a? (即什么时候 returnA 应该为 1? )
    // 情况1:a 和 b 符号不同.
    //        此时不需要看 a-b,直接看 a 的符号.
    //        如果 a 是非负数(sa=1),b 肯定是负数,那么 a 一定大.
    //        逻辑项：diffAB * sa
    //
    // 情况2:a 和 b 符号相同.
    //        此时 a - b 绝对不会溢出(正减正 或 负减负)
    //        这种情况下可以放心依赖 c 的符号(sc).
    //        如果 c 是非负数(sc=1),说明 a >= b。
    //        逻辑项：sameAB * sc

    // 将两种情况结合:只要满足其中一种,就返回 a
    int returnA = diffAB * sa + sameAB * sc;

    // returnB 永远和 returnA 相反
    int returnB = flip(returnA);

    // 返回结果
    return a * returnA + b * returnB;
}

int main()
{
    int a = INT_MIN; // -2147483648
    int b = INT_MAX; // 2147483647

    // getMax1 会出错,因为 a - b 发生了下溢出变成了正数,导致错误地返回了 a
    printf("getMax1 (Buggy): %d\n", getMax1(a, b));

    // getMax 正确处理溢出逻辑,返回 b
    printf("getMax (Correct): %d\n", getMax(a, b));

    return 0;
}
