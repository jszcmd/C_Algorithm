// 牛客测试(ACM风格)
// 牛客测试连接:https://www.nowcoder.com/practice/1ae8d0b6bb4e4bcdbf64ec491f63fc37
// 把下面的所有代码都复制到力扣里面

#include <stdio.h>
#include <stdlib.h>

#define MAX 10001

int min_heap[MAX]; // 最小堆,存储线段终点值
int size_heap = 0; // 堆当前大小

// 交换堆中两个元素 - O(1)
void swap(int a, int b)
{
    int temp = min_heap[a];
    min_heap[a] = min_heap[b];
    min_heap[b] = temp;
}

// 向最小堆添加元素 - O(logN)
// 使用向上调整维护堆性质
void add(int x)
{
    min_heap[size_heap] = x;
    int i = size_heap++;
    while (i > 0 && min_heap[i] < min_heap[(i - 1) / 2])
    {
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// 弹出堆顶最小元素 - O(logN)
// 使用向下调整维护堆性质
int pop()
{
    int min_val = min_heap[0];
    swap(0, --size_heap);
    int i = 0;
    int l = 2 * i + 1;
    while (l < size_heap)
    {
        int best = l;
        if (l + 1 < size_heap && min_heap[l + 1] < min_heap[l])
        {
            best = l + 1;
        }
        if (min_heap[best] < min_heap[i])
        {
            swap(best, i);
            i = best;
            l = 2 * i + 1;
        }
        else
        {
            break;
        }
    }
    return min_val;
}

// 比较函数：按线段起点升序排序 - O(1)
int cmp_int_arr(const void *e1, const void *e2)
{
    int *arr1 = (int *)e1;
    int *arr2 = (int *)e2;
    return arr1[0] - arr2[0];
}

// 计算线段最大重叠数 - 总体O(NlogN)
// 算法步骤:
// 1. 按起点排序线段 O(NlogN)
// 2. 使用最小堆维护当前活跃线段 O(NlogN)
// 3. 遍历时移除已结束线段,添加新线段,记录最大堆大小
int max_overlap(int arr[][2], int len)
{
    size_heap = 0;                                // 重置堆
    qsort(arr, len, sizeof(arr[0]), cmp_int_arr); // 排序线段

    int ans = 0;
    for (int i = 0; i < len; i++)
    {
        // 移除所有终点 ≤ 当前起点的已结束线段
        while (size_heap > 0 && min_heap[0] <= arr[i][0])
        {
            pop(); // O(logN)
        }
        add(arr[i][1]); // O(logN) - 添加当前线段终点
        if (size_heap > ans)
        {
            ans = size_heap; // 更新最大重叠数
        }
    }
    return ans;
}

int main()
{
    int N;
    scanf("%d", &N);

    int arr[N][2];
    for (int i = 0; i < N; i++)
    {
        if (scanf("%d %d", &arr[i][0], &arr[i][1]) != 2)
        {
            return -1;
        }
    }

    int ans = max_overlap(arr, N);
    printf("%d\n", ans);

    return 0;
}
