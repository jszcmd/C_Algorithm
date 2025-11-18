// 力扣测试(填函数风格)
// 力扣测试链接:https://leetcode.cn/problems/minimum-operations-to-halve-array-sum/
// 提交的时候,把下面的代码都复制到力扣里面

// 定义全局堆数组和大小
long long heap[100001]; // 使用long long避免整数溢出
int size;

// 交换堆中两个元素的位置
void swap(int a, int b)
{
    long long temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

// i位置的数变小了,维持大根堆的特性 - 向下调整
// 时间复杂度: O(log n)
void heapify(int i)
{
    int l = 2 * i + 1; // 计算左孩子索引
    // 当存在左孩子时继续调整
    while (l < size)
    {
        // 选择左右孩子中较大的那个
        int best = (l + 1 < size && heap[l + 1] > heap[l]) ? l + 1 : l;
        // 比较当前节点和较大的孩子
        best = (heap[best] > heap[i]) ? best : i;
        // 如果当前节点已经是最大值,无需调整
        if (best == i)
            break;
        // 交换当前节点和较大的孩子
        swap(best, i);
        i = best;      // 更新当前位置
        l = 2 * i + 1; // 重新计算左孩子索引
    }
}

// 将数组减半的最少操作次数
// 时间复杂度: O(n log n)
// 空间复杂度: O(n)
int halveArray(int *nums, int numsSize)
{
    size = numsSize;   // 设置堆大小
    long long sum = 0; // 数组总和(放大后)
    int i = 0;

    // 从底向上建堆,同时计算总和
    // 使用左移20位来避免浮点数精度问题,将整数放大2^20倍
    for (i = size - 1; i >= 0; i--)
    {
        heap[i] = (long long)nums[i] << 20; // 数值放大2^20倍
        sum += heap[i];                     // 累加总和
        heapify(i);                         // 调整堆维持大根堆特性
    }

    long long target_sum = sum / 2; // 目标减少量（总和的一半）
    long long cur_sum = 0;          // 当前已减少的量
    int ans = 0;                    // 操作次数

    // 循环直到减少的幅度达到目标
    // 使用for循环巧妙结合操作计数,每次循环处理一个减半操作
    for (cur_sum = 0; cur_sum < target_sum; ans++)
    {
        heap[0] /= 2;       // 堆顶元素减半
        cur_sum += heap[0]; // 累计减少量
        heapify(0);         // 调整堆维持大根堆特性
    }

    return ans; // 返回操作次数
}
