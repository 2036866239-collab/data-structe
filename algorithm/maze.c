#include <stdbool.h>
#include  <stdio.h>
#define ROWS 5
#define COLS 5

typedef struct{
    int incx,incy;
}Direction;

typedef struct{
    int x,y;
    int di;
}Box;

static const Direction direct[4] ={
    {0,1},{1,0},{0,-1},{-1,0}
};

bool  findpath(const int maze[ROWS][COLS]){
    int visited[ROWS][COLS] = {0};
    Box stack[ROWS*COLS];
    int top  = 0;
    stack[0] = (Box){0,0,-1};
    visited[0][0] = 1;
    Box *current = &stack[top];
    int di =++current->di;
    int line = current->x + direct[di].incx;
    int col = current->y + direct[di].incy;
    if(maze[0][0] !=0 || maze[ROWS-1][COLS-1] !=0){
        return false;
    }
    while(top >=0){
        if(current->x ==ROWS-1 && current->y ==COLS-1){
            for(int i=0;i<=top;i++){
                printf("(%d,%d)",stack[i].x,stack[i].y)
            }
            reutrn true;
        }
        if(current->di==3){
            top--;
            continue;
        }
        if (line < 0 || line >= ROWS || col < 0 || col >= COLS) {
            continue;
        }
        if (maze[line][col] != 0 || visited[line][col]) {
            continue;
        }
        visited[line][col] = 1;
        stack[++top] = (Box){line,col,-1};
    return false;
    }

}