// 注意:用经典的随机快速排序算法实现在力扣里面是通过不了的;
// 在洛谷里面不能完全通过,也是会超时的

#include <stdio.h>  // 用于输入输出函数
#include <stdlib.h> // 用于rand()和srand()函数
#include <time.h>   // 用于time()函数

// 生成 [l, r] 范围内的随机整数
int randint(int l, int r) {
    static int initialized = 0; // 静态变量,只在第一次调用时初始化为0
    if (!initialized) {
        srand(time(NULL)); // 只在第一次调用时执行，设置随机数种子
        initialized = 1; // 标记为已初始化，避免重复设置种子
    }
    return rand() % (r - l + 1) + l; // 生成[l, r]范围内的随机整数
}

// 交换数组中两个位置的元素
void swap(int arr[], int a, int b) {
    int temp = arr[a]; // 临时保存arr[a]的值
    arr[a] = arr[b]; // 将arr[b]的值赋给arr[a]
    arr[b] = temp; // 将临时保存的值赋给arr[b]
}

// 分区函数：将数组分为小于等于x和大于x的两部分
int partition(int arr[], int l, int r, int x) {
    int a = l; // 分区指针，指向当前小于等于x区域的下一个位置
    int xi = 0; // 记录基准值x在数组中的位置
    int i = l; // 遍历指针

    // 遍历整个区间
    for (i = l; i <= r; i++) {
        if (arr[i] <= x) {
            // 当前元素小于等于基准值x，将其交换到前面
            swap(arr, i, a);
            if (arr[a] == x) xi = a; // 记录基准值x的位置
            a++; // 扩大小于等于x的区域
        }
    }
    // 将基准值x交换到正确的位置（小于等于区域和大于区域的分界处）
    swap(arr, xi, a - 1);
    return a - 1; // 返回基准值的最终位置
}

// 快速排序递归函数
void quickSort(int arr[], int l, int r) {
    if (l >= r) return; // 递归终止条件：区间为空或只有一个元素

    int x = arr[randint(l, r)]; // 随机选择基准值
    int mid = partition(arr, l, r, x); // 对当前区间进行分区

    // 递归排序左半部分（小于基准值的元素）
    quickSort(arr, l, mid - 1);
    // 递归排序右半部分（大于基准值的元素）
    quickSort(arr, mid + 1, r);
}

// 排序数组入口函数
int *sortArray(int *nums, int numsSize, int *returnSize) {
    *returnSize = numsSize; // 设置返回数组的长度
    quickSort(nums, 0, numsSize - 1); // 对整个数组进行快速排序
    return nums; // 返回排序后的数组
}
