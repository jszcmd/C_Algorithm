#include <stdlib.h>
#include <string.h>

// 一维差分,力扣测试(航班预定统计)
// 力扣测试链接:https://leetcode.cn/problems/corporate-flight-bookings/

int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize, int n, int* returnSize) {
    // 1. 初始化：申请 n+2 防止 "last+1" 越界；memset 必须清零，否则是随机值
    int cnt[n+2];
    memset(cnt, 0, sizeof(cnt));

    int i = 0;
    for (i = 0; i < bookingsSize; i++) {
        // 2. 差分核心：【起点】增加，【终点后一位】减少
        cnt[bookings[i][0]] += bookings[i][2];
        cnt[bookings[i][1]+1] -= bookings[i][2];
    }

    // 3. 还原数据：累加前缀和，将“变化量”变回“总量”
    for (i = 1; i < n+2; i++) {
        cnt[i] += cnt[i-1];
    }

    *returnSize = n;
    // *bookingsColSize = n; // 提示：这行通常是多余的，bookingsColSize 是输入参数

    int* arr = (int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++) {
        // 4. 结果偏移：cnt 是 1-based (1~n)，arr 是 0-based
        arr[i] = cnt[i+1];
    }
    return arr;
}
