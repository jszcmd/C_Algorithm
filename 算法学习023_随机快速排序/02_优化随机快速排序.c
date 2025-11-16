#include <stdio.h>
#include <stdlib.h> // 使用srand()和rand()函数
#include <time.h> // 导入时间模块,使用time()函数

#define MAXN 100001  // 根据题目数据范围定义

int arr[MAXN]; // 使用静态数组,避免动态分配开销


// 力扣测试链接:https://leetcode.cn/problems/sort-an-array/
// 从13到90行全部复制到力扣里面,不要修改函数名和打乱函数顺序

// 全局静态变量,用于记录分区后的边界位置
// first: 等于基准值的第一个元素位置
// last: 等于基准值的最后一个元素位置
static int first = 0;
static int last = 0;

// 模拟python中的randint函数:生成[l, r]范围内的随机整数
int randint(int l, int r) {
    static int initialized = 0; // 静态变量,只在第一次调用时初始化为0
    if (!initialized) {
        srand(time(NULL)); // 只在第一次调用时执行,设置随机数种子
        initialized = 1; // 标记为已初始化,避免重复设置种子
    }
    return rand() % (r - l + 1) + l; // 生成[l, r]范围内的随机整数
}

// 交换数组中两个位置的元素
void swap(int arr[], int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

// 三路分区函数:将数组分为三部分
// 小于x的元素 | 等于x的元素 | 大于x的元素
void partition(int arr[], int l, int r, int x) {
    first = l; // 初始化第一个等于x的位置
    last = r; // 初始化最后一个等于x的位置
    int i = l; // 当前遍历指针

    // 遍历当前分区
    while (i <= last) {
        if (arr[i] == x) {
            // 当前元素等于基准值，继续向后遍历
            i++;
        } else if (arr[i] < x) {
            // 当前元素小于基准值，交换到前半部分
            swap(arr, first, i);
            first++; // 前边界向右移动
            i++; // 继续检查下一个元素
        } else {
            // 当前元素大于基准值，交换到后半部分
            swap(arr, last, i);
            last--; // 后边界向左移动
            // 注意：这里不增加i,因为需要检查从后面交换过来的新元素
        }
    }
    // 分区完成后：
    // [l, first-1] 包含所有小于x的元素
    // [first, last] 包含所有等于x的元素
    // [last+1, r] 包含所有大于x的元素
}

// 快速排序递归函数
void quickSort(int arr[], int l, int r) {
    if (l >= r) return; // 递归终止条件：分区只有一个元素或为空

    // 随机选择基准值,避免最坏情况
    int x = arr[randint(l, r)];

    // 对当前分区进行三路分区
    partition(arr, l, r, x);

    // 使用局部变量,保存分区后的边界位置
    int left = first;
    int right = last;

    // 递归排序小于基准值的左半部分
    quickSort(arr, l, left - 1);
    // 递归排序大于基准值的右半部分
    quickSort(arr, right + 1, r);
}

// 排序数组入口函数
int *sortArray(int *nums, int numsSize, int *returnSize) {
    *returnSize = numsSize; // 设置返回数组的长度
    quickSort(nums, 0, numsSize - 1); // 对整个数组进行快速排序
    return nums; // 返回排序后的数组
}


// 洛谷测试链接:https://www.luogu.com.cn/problem/P1177
// 把这个文件都复制到洛谷里面.

// 竞赛级快速读入整数
static inline int read() {
    int x = 0;
    char ch = getchar();
    // 跳过空白字符
    while (ch <= ' ') ch = getchar();
    // 读取数字
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x;
}

// 竞赛级快速输出整数
static inline void write(int x) {
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}


int main() {
    // 快速读入N
    int N = read();

    // 快速读入N个整数
    for (int i = 0; i < N; i++) arr[i] = read();

    // 对数组进行排序
    quickSort(arr, 0, N - 1);

    // 快速输出结果
    for (int i = 0; i < N; i++) {
        write(arr[i]);
        if (i < N - 1) {
            putchar(' '); // 数字间空格
        }
    }
    putchar('\n'); // 行末换行

    return 0;
}
