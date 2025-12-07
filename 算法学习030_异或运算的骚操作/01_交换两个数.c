// 1.题目1):交换两个数
#include <stdio.h>
void swap1(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[j] = arr[i];
    arr[i] = temp;
}
// swap1(arr,i,j) --> 怎么都行
void swap2(int arr[], int i, int j)
{
    arr[i] = arr[i] ^ arr[j];
    arr[j] = arr[i] ^ arr[j];
    arr[i] = arr[i] ^ arr[j];
}
// 对于这个swap2
// 当i != j,没问题,会完成交换功能;
// 当i == j,会出现问题
int main()
{
    int a = 10;
    int b = -2312;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("a = %d ; b = %d \n", a, b);
    // 这么写的前提是a和b都有自己的内存空间

    int arr[] = {3, 5};
    printf("------------- i!= j --------------\n");
    printf("交换前:arr[0] = %d ; arr[1] = %d \n", arr[0], arr[1]);
    swap2(arr, 0, 1);
    printf("交换后:arr[0] = %d ; arr[1] = %d \n", arr[0], arr[1]);
    printf("---------------------------\n");
    // 当i和j不一样位置的时候这样写没有问题的

    swap2(arr, 0, 0);
    printf("arr[0] = %d\n", arr[0]); // arr[0] = 0

    return 0;
}
