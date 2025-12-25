/*
 * ================================================================================
 * 📘 题目:2092. 找出知晓秘密的所有专家 (Find All People With Secret)
 * 🔗 链接: https://leetcode.cn/problems/find-all-people-with-secret/
 * 📈 难度: 困难 (Hard)
 * --------------------------------------------------------------------------------
 * 📝 【题目描述】
 * 给你一个整数 n ,表示有 n 个专家从 0 到 n - 1 编号.
 * 另外给你一个下标从 0 开始的二维整数数组 meetings ,其中 meetings[i] = [xi, yi, timei]
 * 表示专家 xi 和专家 yi 在时间 timei 要开一场会.一个专家可以同时参加多场会议.
 * 最后,给你一个整数 firstPerson.
 * * 专家 0 有一个秘密,最初,他在时间 0 将这个秘密分享给了专家 firstPerson.
 * 接着,这个秘密会在每次有知晓这个秘密的专家参加会议时进行传播.更正式的表达是:
 * 每次会议,如果专家 xi 在时间 timei 时知晓这个秘密,那么他将会与专家 yi 分享这个
 * 秘密,反之亦然.
 * * ⚡ 秘密共享是 瞬时发生 的.也就是说,在同一时间,一个专家不仅可以接收到秘密,
 * 还能在其他会议上与其他专家分享.
 * 在所有会议都结束后,返回所有知晓这个秘密的专家列表.你可以按 任何顺序 返回答案.
 * --------------------------------------------------------------------------------
 * 🌟 【示例 1】
 * 输入: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1 -> 输出: [0,1,2,3,5]
 * 🌟 【示例 2】
 * 输入: n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3 -> 输出: [0,1,3]
 * 🌟 【示例 3】
 * 输入: n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1 -> 输出: [0,1,2,3,4]
 * --------------------------------------------------------------------------------
 * 📏 【提示】
 * • 2 <= n <= 10^5
 * • 1 <= meetings.length <= 10^5
 * • meetings[i].length == 3
 * • 0 <= xi, yi <= n - 1 且 xi != yi
 * • 1 <= timei <= 10^5
 * • 1 <= firstPerson <= n - 1
 * ================================================================================
 */

#include <stdlib.h>  // 🛠️ 使用qsort()和malloc()函数
#include <stdbool.h> // 使用bool数据类型

#define MAX 100001 // 📏 定义最大专家数量限制

int father[MAX]; // 🌳 并查集:存储每个节点的父节点

bool secret[MAX] = {false}; // 🔐 秘密状态：标记该集合是否知晓秘密
// 🧬 集合的标签信息:设置集合的一些属性,
// 🔍 属性在哪里? secret[代表元素] 代表集合的属性

void build(int n, int first)
{
    for (int i = 0; i < n; i++)
    {
        father[i] = i;     // 🆔 初始化:每个人的父节点是自己
        secret[i] = false; // ⚪ 初始状态:所有人均不知晓秘密
    }
    father[first] = 0; // 🤝 初始链接:将firstPerson与0号专家归为一集
    secret[0] = true;  // 🔑 源头:0时刻0号专家已知晓秘密
}

int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]); // 🔍 路径压缩:直接指向根节点
    }
    return father[i];
}

void do_union(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
    {
        father[fx] = fy;          // 🔗 合并:将两个集合连通
        secret[fy] |= secret[fx]; // ⚡ 传播:只要有一个集合知晓,合并后全集知晓
    }
}

// ⚖️ 比较函数
int time_cmp(const void *e1, const void *e2)
{
    // 1. 先把 void* 转成 int**
    // 2. 使用 * 进行解引用,获取真正存储会议数据的 int*
    int *arr1 = *(int **)e1;
    int *arr2 = *(int **)e2;

    // 3. 比较第三个元素(时刻)
    return arr1[2] - arr2[2]; // ⏳ 按会议时间升序排列
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findAllPeople(int n, int **meetings, int meetingsSize, int *meetingsColSize, int firstPerson, int *returnSize)
{

    build(n, firstPerson); // 🏗️ 初始化并查集:设定所有人父节点为自身,并建立 0 号与初始专家的连接
    // meetings[a,b,c] // 数据结构说明:a,b 为专家编号,c 为会议时刻

    // m:表示一共开了机场会议
    int m = meetingsSize;                              // 📝 缓存会议总数:避免在循环中多次读取变量
    qsort(meetings, m, sizeof(meetings[0]), time_cmp); // ⏱️ 时序排序:严格按照会议发生的时间戳 c 进行升序排列
    for (int l = 0, r; l < m;)
    {
        r = l; // 📍 窗口起点:标记当前处理的时间段起始索引
        // l...r这些会议,一定是共同时刻
        while (r + 1 < m && meetings[l][2] == meetings[r + 1][2])
        {
            r++; // 🔍 同时性识别:将所有在同一时刻 c 发生的会议划分为一个批次处理
        }
        for (int i = l; i <= r; i++)
        {
            do_union(meetings[i][0], meetings[i][1]); // 📡 秘密传播:在当前时刻,所有开会的人员在并查集中建立连通关系
        }
        // 合并在一起知道秘密的人,不用拆散
        for (int i = l, a, b; i <= r; i++)
        {
            a = meetings[i][0]; // 👤 提取人员 A:获取当前批次会议中的第一位专家
            b = meetings[i][1]; // 👤 提取人员 B:获取当前批次会议中的第二位专家
            if (!secret[find(a)])
            {
                father[a] = a; // 🚫 逻辑回滚:若 A 所在的集合最终没能连接到秘密源,则撤销其在并查集中的连接
            }
            if (!secret[find(b)])
            {
                father[b] = b; // 🚫 逻辑回滚:确保只有在该时刻学到秘密的人,才能将秘密带入下一时刻
            }
        }
        l = r + 1; // ⏭️ 批次更替:移动左指针,准备处理下一个不同时刻的会议组
    }
    int count = 0; // 🔢 计数器:准备统计全城最终知晓秘密的总人数
    for (int i = 0; i < n; i++)
    {
        if (secret[find(i)] == true)
        {
            count++;          // 📊 深度检索:检查每个专家所属集合的根节点是否标记为"知秘"状态
            secret[i] = true; // 那么我们就顺便把第i位专家直接改成知道秘密
        }
    }
    int *ans = (int *)malloc(sizeof(int) * count); // 💾 空间分配:根据统计人数动态申请返回数组的内存
    for (int i = 0, cur = 0; i < n; i++)
    {
        if (secret[i] == true) // 上面我们已经直接修改secret[i] = true了
        {
            ans[cur++] = i; // ✅ 名单录入:按编号顺序将所有知晓秘密的专家存入结果数组
        }
    }
    *returnSize = count; // 🏁 长度回传:通过指针告知调用方结果数组的有效长度
    return ans;          // 🚀 成果提交:返回最终生成的知情专家名单指针
}
