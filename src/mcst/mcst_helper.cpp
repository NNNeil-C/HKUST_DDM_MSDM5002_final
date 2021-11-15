//
// Created by 陈梓峰 on 15/11/2021.
//
#include "mcst.hpp"
#include <iostream>

extern "C"
{
    int getNextPosition(const int input[], const int last_x, const int last_y, const int last_piece, const int time_limit)
    {
        int **board;
        board = new int*[MAXN];
        for (unsigned int i = 0; i < MAXN; i ++)
        {
            board[i] = new int[MAXN];
            for (unsigned int j = 0; j < MAXN; j ++)
            {
                board[i][j] = input[i * MAXN + j];
            }
        }
        std::pair<int, int> last_drop(last_x, last_y);
        Mcst mcst(board, last_drop, last_piece);
        auto next = mcst.deduction(time_limit);
        int ans = next.first * 10 + next.second;
        recycle_game_board(board);
        return ans;
    }

    void hello() {
        time_t now = time(0);
        char* dt = ctime(&now);
        std::cout << "hello, it's " << dt << std::endl;
    }
}

