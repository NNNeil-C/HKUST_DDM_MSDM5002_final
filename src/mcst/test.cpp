/*
 * @Author: Neil.Chen Zifeng 
 * @Date: 2021-11-02 00:08:26 
 * @Last Modified by: Neil.Chen Zifeng
 * @Last Modified time: 2021-11-04 19:30:57
 */
#include <algorithm>
#include <iostream>
#include "mcst.hpp"
#include "LogUtils.h"
#include "GameUtils.hpp"
#define MAXN 8
using namespace std;

int main ()
{
    int **board;
    board = new int*[MAXN];
    for (int i = 0; i < MAXN; i ++)
    {
        board[i] = new int[MAXN]{};
    }
    print_board(board);
    std::pair<int, int> last_drop(-1, -1);
    int last_piece = 0;

    for (int round = 0; round < 10; round ++)
    {
        LOGD("%s : %d", "start round", round);
        LOGD("%s", "start to call msct()");
        Mcst mcst(board, last_drop, last_piece);
        LOGD("%s %d", "start to deduction, time limit", 1000);
        std::pair<int, int> drop_on = mcst.deduction(5000);
        int x = drop_on.first;
        int y = drop_on.second;
        LOGD("%s %d %d", "ready to drop on ", x, y);
        last_drop.first = x;
        last_drop.second = y;
        last_piece = (last_piece == 0) ? 1 : -1 * last_piece;
        board[x][y] = last_piece;
        print_board(board);
        LOGD("%s", "reday to check win");
        if (check_win(board, last_piece))
        {
            cout << last_piece << " wins." << endl;
            break;
        }
    }
    print_board(board);
    recycle_game_board(board);
}