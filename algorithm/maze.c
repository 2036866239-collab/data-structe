#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 11
#define COLS 11

typedef struct { int incx, incy; } Direction; // 行、列坐标的增量
// di 记录已经尝试过的最后一个方向；-1 表示还没试过。
typedef struct { int x, y; int di; } Box;

// 寻路依次尝试右、下、左、上；生成迷宫时会打乱顺序。
static const Direction direct[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void carve(int maze [ROWS][COLS],int x,int y){
    maze[x][y] = 0;

    int order[4] ={0,1,2,3};
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = order[i]; order[i] = order[j]; order[j] = t;  //洗牌算法
    }

    for (int k = 0; k < 4; k++) {
        int d  = order[k];
        int nx = x + direct[d].incx * 2;  // 跳 2 格
        int ny = y + direct[d].incy * 2;
        if (nx < 0 || nx >= ROWS || ny < 0 || ny >= COLS) continue;
        if (maze[nx][ny] == 0) continue;  // 已挖过（这里代替 visited）

        maze[x + direct[d].incx][y + direct[d].incy] = 0;  // 打通中间的墙
        carve(maze, nx, ny);}
}

void generateMaze(int maze[ROWS][COLS]){
    for(int i = 0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
        maze[i][j] = 1;
    carve(maze,0,0);
    int cnt = 0;
    while (cnt < 3) {           //在已生成好的迷宫上，利用随机函数进行挖洞。
        int x = rand() % ROWS, y = rand() % COLS;
        if (x % 2 != y % 2 && maze[x][y] == 1) {
            maze[x][y] = 0;
            cnt++;
        }
    }
}

bool findPath(int maze[ROWS][COLS])
{
    bool visited[ROWS][COLS] = {false};
    Box stack[ROWS * COLS];
    int top = 0;
    stack[0] = (Box){0, 0, -1};
    visited[0][0] = 1;

    while (top >= 0) {
        Box *current = &stack[top];

        if (current->x == ROWS-1 && current->y == COLS-1) {
            for (int i = 0; i <= top; i++)
                printf("(%d,%d)%s", stack[i].x, stack[i].y,
                       i == top ? "\n" : " -> ");
            return true;
        }
        if (current->di == 3) { top--; continue; }

        int di   = ++current->di;
        int line = current->x + direct[di].incx;
        int col  = current->y + direct[di].incy;

        if (line < 0 || line >= ROWS || col < 0 || col >= COLS) continue;
        if (maze[line][col] != 0 || visited[line][col]) continue;

        visited[line][col] = 1;
        stack[++top] = (Box){line, col, -1};
    }
    return false; //DFS 寻路。
}

void printMaze(int maze[ROWS][COLS])
{
    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLS; y++) {
            putchar(maze[x][y] == 1 ? '#' : '.');
        }
        putchar('\n');
    }
}

/* ================== 4. 主程序 ================== */

int main(void)
{

    int maze[ROWS][COLS];        // 注意：不能是 const，因为要被挖
    generateMaze(maze);

    printMaze(maze);
    putchar('\n');

    if (!findPath(maze))
        puts("没有路径");        // 理论上永远不会执行
    return 0;
}

