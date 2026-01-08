
// 0: 0 1  ---> 第0号情侣
// 1: 2 3  ---> 第1号情侣
// 2: 4 5  ---> 第2号情侣
// 3: 5 7  ---> 第3号情侣
// 4: 8 9  ---> 第4号情侣
// x号人,他是第(x/2)对情侣

#include <stdio.h>

#define MAX 31
int father[MAX];
int sets;

void build(int m)
{
    for (int i = 0; i < m; i++)
    {
        father[i] = i;
    }
    sets = m;
}

int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]);
    }
    return father[i];
}

void do_union(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
    {
        father[fx] = fy;
        sets--;
    }
}

int minSwapsCouples(int *row, int rowSize)
{
    int n = rowSize;
    build(n / 2);
    for (int i = 0; i < n; i += 2)
    {
        do_union(row[i] / 2, row[i + 1] / 2);
    }
    return n / 2 - sets;
}
