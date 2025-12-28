#include <stdbool.h>

#define MAXN 101
#define MAXM 101

int queue[MAXN * MAXM][2];
int l, r;

bool visited[MAXN][MAXM];
int move[5] = {-1, 0, 1, 0, -1};
//           0  1  2  3   4
// (x,y) i来到0位置: x+move[i],y+move[i+1]  ---> x-1,y   ---> 往上走
// (x,y) i来到1位置: x+move[i],y+move[i+1]  ---> x,y+1   ---> 往右走
// (x,y) i来到2位置: x+move[i],y+move[i+1]  ---> x+1,y   ---> 往下走
// (x,y) i来到3位置: x+move[i],y+move[i+1]  ---> x,y-1   ---> 往左走

int maxDistance(int **grid, int gridSize, int *gridColSize)
{
    l = r = 0;
    int n = gridSize;
    int m = gridColSize[0];
    int seas = 0; // 发现的海洋的数量
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 1)
            {
                visited[i][j] = true;
                queue[r][0] = i;
                queue[r][1] = j;
                r++;
            }
            else
            {
                visited[i][j] = false;
                seas++;
            }
        }
    }
    if (seas == 0 || seas == n * m)
    {
        return -1;
    }
    int level = 0;
    while (l < r)
    { // 队列里面还有东西.
        level++;
        int size = r - l; // 当前队列里面还有东西,下面过程就执行几次
        for (int k = 0, x, y, nx, ny; k < size; k++)
        {
            x = queue[l][0];
            y = queue[l][1];
            l++; // 当前弹出的节点在x行y列.
            for (int i = 0; i < 4; i++)
            {
                nx = x + move[i];
                ny = y + move[i + 1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 0 && !visited[nx][ny])
                {
                    visited[nx][ny] = true;
                    queue[r][0] = nx;
                    queue[r][1] = ny;
                    r++;
                }
            }
        }
    }
    return level - 1;
}
