/*
* =================================================================================
 * 📘 程序名称:二分查找算法对数器 (Binary Search Validator)
 * =================================================================================
 * 【主要功能】
 * 用于验证二分查找算法 (Binary Search) 的正确性.通过大量随机样本测试,
 * 比对"二分查找"与"暴力遍历"的结果,检测算法是否存在边界条件错误.
 *
 * 【核心逻辑】
 * 1. 目标算法 (exist): 实现 O(logN) 的二分查找,高效但容易写错.
 * 2. 验证算法 (right): 实现 O(N) 的线性遍历,简单且绝对正确 (作为标准答案)。
 * 3. 随机测试 (test):
 * - 生成随机长度、随机数值的数组.
 * - 使用 qsort 对数组进行排序 (二分查找的前提).
 * - 生成一个随机查找目标 (num).
 * - 比较 exist() 和 right() 的结果是否一致.
 * 4. 压力测试 (main): 循环几十万次调用 test(),确保算法鲁棒性.
 *
 * 【使用方法】
 * 直接运行程序.如果控制台打印 "Test is finished." 且无其他错误提示,
 * 则说明二分查找算法实现正确.
 * =================================================================================
 */

#include <stdio.h>  // 使用printf()函数
#include <stdlib.h> // 使用rand(),srand()和qsort()
#include <stdbool.h> // 使用bool类型
#include <time.h>    // 使用time()函数

// [核心算法] 二分查找
// 时间复杂度: O(logN)
// 前提: 数组必须有序
bool exist(const int arr[], const int len, const int num) {
    if (arr == NULL || len == 0) return false;
    int l = 0, r = len - 1, m = 0;

    // 经典二分逻辑: 在 [l, r] 区间内查找
    while (l <= r) {
        m = (l + r) / 2; // 取中间位置 (防溢出写法: l + (r-l)/2)
        if (arr[m] == num) {
            return true; // 找到了
        } else if (arr[m] > num) {
            r = m - 1; // 中间值太大, 去左半边找
        } else {
            l = m + 1; // 中间值太小, 去右半边找
        }
    }
    return false;
}

// [验证算法] 暴力遍历
// 时间复杂度: O(N)
// 作用: 逻辑简单绝对正确, 用作"标准答案"
bool right(const int arr[], const int len, const int num) {
    int i = 0;
    for (i = 0; i < len; i++) {
        if (arr[i] == num) return true;
    }
    return false;
}

// 辅助工具: 生成 [l, r] 范围内的随机整数
int randint(int l, int r) {
    static int initialized = 0; // 静态变量, 全局只初始化一次
    if (!initialized) {
        srand(time(NULL)); // 设置随机种子
        initialized = 1; // 标记已初始化
    }
    return rand() % (r - l + 1) + l;
}

// qsort的比较函数 (升序)
int int_cmp(const void *a, const void *b) {
    return (*(int *) a) - (*(int *) b);
}

// [测试单次逻辑]
void test(int n, int v) {
    // 1. 生成随机数组 (VLA变长数组, C99支持)
    int arr[n];
    int i = 0;
    for (i = 0; i < n; i++) {
        arr[i] = randint(0, v); // 填入 [0, v] 的随机数
    }

    // 2. 排序 (二分查找的前置条件)
    qsort(arr, n, sizeof(int), int_cmp);

    // 3. 生成一个随机的目标值
    int num = randint(0, v);

    // 4. 比对: 如果二分结果 != 暴力结果, 说明二分写错了
    if (exist(arr, n, num) != right(arr, n, num)) {
        printf("Something went wrong\n");
        // 实际应用中这里可以打印出出错的 arr 和 num 以便调试
    }
}

int main() {
    int N = 100; // 最大数组长度
    int V = 1000; // 最大数值范围
    int testTime = 500000; // 测试次数 (样本量)

    printf("Test is begin.\n");

    // 开始海量随机测试
    for (int i = 0; i < testTime; i++) {
        int n = randint(0, N); // 随机生成本次数组长度
        test(n, V);
    }

    printf("Test is finished.\n");
    return 0;
}
