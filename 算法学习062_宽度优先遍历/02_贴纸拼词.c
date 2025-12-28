#include <stdbool.h>
#include <stdlib.h> // 使用qsort()函数
#include <string.h> // 使用strlen()函数

// #include "uthash.h" // 确保这个文件在同一目录下

#define MAX 401
char *queue[MAX];
int l, r;

struct ListNode
{
    char *str;
    struct ListNode *next;
};

typedef struct ListNode ListNode;

ListNode *adjList[26]; // 邻接表
// 0位置 ----> 能够搞定a字母的
// 1位置 ----> 能够搞定b字母的
// ....
// 25位置 ----> 能够搞定z字母的

void build()
{
    // 遍历每一个节点的边链表
    for (int i = 0; i < 26; i++)
    {
        ListNode *cur = adjList[i]; // cur 指向当前节点的链表头
        while (cur)                 // 循环直到链表末尾
        {
            ListNode *tmp = cur; // 暂存当前节点指针
            cur = cur->next;     // 指针后移到下一个边节点
            free(tmp);           // 释放当前动态申请的结构体内存
        }
        adjList[i] = NULL; // 将该节点的表头指针归零,防止野指针
    }
}

int char_cmp(const void *e1, const void *e2)
{
    return (*(char *)e1) - (*(char *)e2); // ⚖️ 比较规则:数值小的排前面,用于排序初始病毒数组
}

void addListEdge(char ch, char *my_str)
{
    int i = ch - 'a';
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->str = my_str;
    newNode->next = adjList[i];
    adjList[i] = newNode;
}

// bool visited[MAX];

int minStickers(char **stickers, int stickersSize, char *target)
{
    for (int i = 0; i < stickersSize; i++)
    {
        char *str = stickers[i];
        int str_len = strlen(str);
        qsort(str, str_len, sizeof(char), char_cmp); // 给每一个贴纸都排序一下
        for (int j = 0; j < str_len; j++)
        {
            if (j == 0 || str[j] != str[j - 1])
            {
                addListEdge(str[j], str);
            }
        }
    }

    // 给target排一下序
    qsort(target, strlen(target), sizeof(char), char_cmp); // 给每一个贴纸都排序一下
    // visit.add(target)
    l = r = 0;
    queue[r++] = target;
    int level = 1;
    while (l < r)
    {
        int size = r - l;
        for (int i = 0; i < size; i++)
        {
            char *cur_str = queue[l++];
            // 遍历这个字符串的第一个字符,能够搞定第一个字符字母的 贴纸
            char *s = adjList[cur_str[0] - 'a']->str;
            char *next = get_next(cur_str, s);
            if (*next == "")
            {
                return level;
            }
        }
    }

    return 0;
}
