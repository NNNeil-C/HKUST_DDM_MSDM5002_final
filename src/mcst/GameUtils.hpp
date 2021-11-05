//
// Created by 陈梓峰 on 5/11/2021.
//

#ifndef HKUST_DDM_MSDM5002_FINAL_GAMEUTILS_HPP
#define HKUST_DDM_MSDM5002_FINAL_GAMEUTILS_HPP

#include <iostream>

bool is_empty_game_board(int **game_board)
{
    LOGD("%s", "run in ");
    bool is_empty = true;
    for (int i = 0; i < MAXN; i ++)
    {
        if (!is_empty)
        {
            break;
        }
        for (int j = 0; j < MAXN; j ++)
        {
            if (game_board[i][j] != 0)
            {
                is_empty = false;
                break;
            }
        }
    }
    return is_empty;
}

void print_board(int **board)
{
    LOGD("%s", "start to print game board");
    std::cout << "start print game board" << std::endl;
    for (int i = 0; i < MAXN; i ++)
    {
        for (int j = 0; j < MAXN; j ++)
        {
            int val = board[i][j];
            val = (val < 0) ? 2 : val;
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "end print game board" << std::endl;
}

// a valid position: not ocuppied and has neighbor piece within a 4*4 matrix
bool is_valid_position (int **game_board, int x, int y)
{
    if (game_board[x][y] != 0)
    {
        return false;
    }
    for (int i = -2; i < 3; i ++)
    {
        for (int j = -2; j < 3; j ++)
        {
            if ((i == 0) && (j == 0))
            {
                continue;
            }
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < MAXN && ny >= 0 && ny < MAXN)
            {
                if (game_board[nx][ny] != 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

#endif //HKUST_DDM_MSDM5002_FINAL_GAMEUTILS_HPP
