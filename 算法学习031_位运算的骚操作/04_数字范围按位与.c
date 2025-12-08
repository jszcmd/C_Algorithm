// 🌟 题目(4): 区间 [left, right] 内所有数字 & 的结果
// 🔗 测试链接: https://leetcode.cn/problems/bitwise-and-of-numbers-range/
// 🧠 核心思想: 寻找 left 和 right 的二进制公共前缀 (Common Prefix)

#include <stdio.h>

/**
 * 🛠️ 计算区间按位与
 * @param left  区间左边界
 * @param right 区间右边界
 * @return      结果
 */
int rangeBitwiseAnd(int left, int right)
{
    // 🔄 循环条件: 只要 right 还比 left 大, 说明还没有找到公共前缀部分
    // (因为 right 比 left 大, 说明 right 的低位肯定还有 1 是 left 没有的, 或者进位导致的差异)
    while (left < right)
    {
        // ✂️ 核心操作: 抹去 right 最右边的 1 (Lowbit)
        // right & -right : 提取出最右侧的 1 (例如 6(110) -> 2(010))
        // right -= ...   : 减去这个 1 (例如 6 - 2 = 4)
        // 这一步等价于 Brian Kernighan 算法: right = right & (right - 1)
        right -= (right & -right);
    }

    // ✅ 当循环结束时, right <= left.
    // 由于我们是一直在"抹零", 此时的 right 就是 left 和 right 的公共高位部分(后面全补0了)
    return right;
}

int main()
{
    // 🧪 测试用例 1
    // [5, 7] -> 5(101) & 6(110) & 7(111) = 4(100)
    int l1 = 5, r1 = 7;
    printf("Range [%d, %d] AND result: %d\n", l1, r1, rangeBitwiseAnd(l1, r1));

    // 🧪 测试用例 2
    // [0, 0] -> 0
    int l2 = 0, r2 = 0;
    printf("Range [%d, %d] AND result: %d\n", l2, r2, rangeBitwiseAnd(l2, r2));

    // 🧪 测试用例 3
    // [1, 2147483647] -> 0 (因为 1 的高位全是 0, 只要有一个数高位是 0, 结果就是 0)
    int l3 = 1, r3 = 2147483647;
    printf("Range [%d, %d] AND result: %d\n", l3, r3, rangeBitwiseAnd(l3, r3));

    return 0;
}
