// 递归和master公式学习笔记

// 1. 从思想上理解递归:对于新手来说,递归去画调用图是非常重要的,有利于分析递归
// 2. 从实际上理解递归:递归不是玄学,底层是利用系统栈来实现的
// 3. 任何递归函数都一定可以改成非递归,不用系统帮你压栈(系统栈空间),自己压栈呗(内存空间)
// 4. 递归改成非递归的必要性:
//    a. 工程上几乎一定要改,除非确定数据量再大递归也一定不深,归并排序、快速排序、线段树、很多的平衡树等,后面都讲
//    b. 算法尝试或者比类中(能通过就不改)
// 5. master公式:
//    a). 所有子问题规模相同的递归才能用master公式, T(n) = a * T(n/b) + 0(n^c) ,a、b、c都是常数
//    b). 如果log(b,a) < c,复杂度为: 0(n^c)
//    c). 如果log(b,a) > c,复杂度为: 0(n^log(b,a))
//    d). 如果log(b,a) == c,复杂度为: 0(n^c * logn)
// 6. 一个补充
//     T(n) = 2*T(n/2) + 0(n*logn) ,时间复杂度是0(n * ((logn)的平方)),证明过程比较复杂,记住即可

#include <stdio.h>

// 递归查找数组指定范围内的最大值
int find_max(int arr[], int l, int r) {
    // Base Case: 当范围内只有一个元素时
    if (l == r) return arr[l];

    // 计算中间位置
    int m = (l + r) / 2;

    // 递归求解左右两半的最大值
    int lmax = find_max(arr, l, m);
    int rmax = find_max(arr, m + 1, r);

    // 合并结果：返回左右两部分的最大值
    return (lmax > rmax) ? lmax : rmax;
}

// Master公式分析本算的时间复杂度
// a = 2, b = 2, c = 0
// log(b,a) = log(2,2) = 1 > c = 0
// 时间复杂度为：O(n^log(2,2)) = O(n)

// 主函数 - 使用分治算法求数组最大值
int max_value(int arr[], int len) {
    return find_max(arr, 0, len - 1);
}

int main() {
    int arr[] = {1, 9, 58, 4, 5, 6};
    int len = sizeof(arr) / sizeof(arr[0]);
    printf("max num in arr: %d\n", max_value(arr, len));
    return 0;
}
