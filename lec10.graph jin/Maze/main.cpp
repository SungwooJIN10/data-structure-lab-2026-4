#include <stdio.h>
#include <stack>
#include <deque>
#include "Location2D.h"

using namespace std;

const int MAZE_SIZE = 6;

char map[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'},
};

void resetMap()
{
    char temp[MAZE_SIZE][MAZE_SIZE] = {
        {'1', '1', '1', '1', '1', '1'},
        {'e', '0', '1', '0', '0', '1'},
        {'1', '0', '0', '0', '1', '1'},
        {'1', '0', '1', '0', '1', '1'},
        {'1', '0', '1', '0', '0', 'x'},
        {'1', '1', '1', '1', '1', '1'},
    };

    for (int i = 0; i < MAZE_SIZE; i++)
        for (int j = 0; j < MAZE_SIZE; j++)
            map[i][j] = temp[i][j];
}

bool isValidLoc(int r, int c)
{
    if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE)
        return false;

    return map[r][c] == '0' || map[r][c] == 'x';
}

void searchByStack()
{
    stack<Location2D> locStack;

    locStack.push(Location2D(1, 0));

    while (locStack.empty() == false) {
        Location2D here = locStack.top();
        locStack.pop();

        int r = here.row;
        int c = here.col;

        printf("(%d,%d) ", r, c);

        if (map[r][c] == 'x') {
            printf("미로 탐색 성공\n");
            return;
        }

        map[r][c] = '.';

        if (isValidLoc(r - 1, c))
            locStack.push(Location2D(r - 1, c));

        if (isValidLoc(r + 1, c))
            locStack.push(Location2D(r + 1, c));

        if (isValidLoc(r, c - 1))
            locStack.push(Location2D(r, c - 1));

        if (isValidLoc(r, c + 1))
            locStack.push(Location2D(r, c + 1));
    }

    printf("미로 탐색 실패\n");
}

void searchByDeque()
{
    deque<Location2D> locDeque;

    locDeque.push_front(Location2D(1, 0));

    while (locDeque.empty() == false) {
        Location2D here = locDeque.front();
        locDeque.pop_front();

        int r = here.row;
        int c = here.col;

        printf("(%d,%d) ", r, c);

        if (map[r][c] == 'x') {
            printf("미로 탐색 성공\n");
            return;
        }

        map[r][c] = '.';

        if (isValidLoc(r - 1, c))
            locDeque.push_front(Location2D(r - 1, c));

        if (isValidLoc(r + 1, c))
            locDeque.push_front(Location2D(r + 1, c));

        if (isValidLoc(r, c - 1))
            locDeque.push_front(Location2D(r, c - 1));

        if (isValidLoc(r, c + 1))
            locDeque.push_front(Location2D(r, c + 1));
    }

    printf("미로 탐색 실패\n");
}

int main()
{
    int ds_num;

    while (true) {
        printf("\nDFS 데이터 구조 라이브러리 선택: 1)stack, 2)deque, 0)exit\n");
        scanf_s("%d", &ds_num);

        if (ds_num == 0)
            break;

        resetMap();

        if (ds_num == 1) {
            printf("STACK DFS\n");
            searchByStack();
        }
        else if (ds_num == 2) {
            printf("DEQUE DFS\n");
            searchByDeque();
        }
        else {
            printf("잘못된 선택입니다.\n");
        }
    }

    return 0;
}