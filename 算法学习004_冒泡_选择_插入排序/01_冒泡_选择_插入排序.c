// 三傻排序: 冒泡 选择 插入 排序
// 时间时间复杂度:O(n^2)

void swap(int arr[], int a, int b)
{
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

/**
 * 冒泡排序算法
 *
 * @param arr: 待排序的数组
 * @param len: 数组长度
 * @return: 排序后的数组
 */
int *bubble_sort(int arr[], int len)
{
    // 如果数组长度小于等于1,直接返回(不需要排序)
    if (len <= 1)
        return arr; // 修正:应该返回arr,而不是return;

    int i = 0; // 外层循环计数器,控制排序轮数
    int j = 0; // 内层循环计数器,控制每轮比较次数

    // 外层循环:从数组末尾向前遍历,控制排序轮数
    // 每轮会将当前最大元素"冒泡"到正确位置
    for (i = len - 1; i > 0; i--)
    {
        // 内层循环:从数组开头到当前未排序部分的末尾
        // 比较相邻元素,将较大的元素向后移动
        for (j = 0; j < i; j++)
        {
            // 如果前一个元素大于后一个元素,交换它们的位置
            if (arr[j] > arr[j + 1])
            {
                swap(arr, j, j + 1); // 交换相邻元素
            }
        }
    }
    return arr; // 返回排序后的数组
}

/**
 * 选择排序算法
 *
 * @param arr: 待排序的数组
 * @param len: 数组长度
 * @return: 排序后的数组
 */
int *select_sort(int arr[], int len)
{
    // 如果数组长度小于等于1,直接返回(不需要排序)
    if (len <= 1)
        return arr;

    int i = 0; // 外层循环计数器,控制已排序部分的末尾
    int j = 0; // 内层循环计数器,用于在未排序部分中寻找最小值

    // 外层循环:遍历数组,每次确定一个最小元素的位置
    // 只需要遍历到倒数第二个元素,因为最后一个元素会自动就位
    for (i = 0; i < len - 1; i++)
    {
        int min_index = i; // 假设当前索引i处的元素是最小值

        // 内层循环:在未排序部分(i+1到末尾)中寻找真正的最小值
        for (j = i + 1; j < len; j++)
        {
            // 如果找到更小的元素,更新最小值的索引
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }

        // 将找到的最小元素与当前位置i的元素交换
        swap(arr, i, min_index);
    }

    return arr; // 返回排序后的数组
}

/**
 * 插入排序算法
 *
 * @param arr: 待排序的数组
 * @param len: 数组长度
 * @return: 排序后的数组
 */
int *insert_sort(int arr[], int len)
{
    // 如果数组长度小于等于1,直接返回(不需要排序)
    if (len <= 1)
        return arr;

    int i = 0; // 外层循环计数器,表示当前要插入的元素
    int j = 0; // 内层循环计数器,用于在已排序部分中找到插入位置

    // 外层循环:从第二个元素开始,逐个将元素插入到已排序序列中
    // 假设第一个元素(arr[0])已经是已排序序列
    for (i = 1; i < len; i++)
    {
        // 内层循环:将当前元素arr[i]与已排序部分从后往前比较
        // 如果当前元素小于前一个元素,就交换位置
        for (j = i; j >= 1; j--)
        {
            // 如果当前元素小于前一个元素,交换它们的位置
            if (arr[j] < arr[j - 1])
            {
                swap(arr, j, j - 1);
            }
            else
            {
                // 优化：如果当前元素已经大于等于前一个元素，说明已经找到正确位置
                // 可以提前结束内层循环,减少不必要的比较
                break;
            }
        }
    }

    return arr; // 返回排序后的数组
}
