/*
 * @Author: Neil.Chen Zifeng 
 * @Date: 2021-11-02 00:08:26 
 * @Last Modified by: Neil.Chen Zifeng
 * @Last Modified time: 2021-11-04 16:36:45
 */
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "mcst.hpp"
#define MAXN 8
using namespace std;

void print_board(int **board)
{
    cout << "start print game board" << endl;
    for (int i = 0; i < MAXN; i ++)
    {
        for (int j = 0; j < MAXN; j ++)
        {
            int val = board[i][j];
            val = (val < 0) ? 2 : val;
            cout << val << ' ';
        }
        cout << endl;
    }
    cout << "end print game board" << endl;
}

int main ()
{
    int **board;
    board = new int*[MAXN];
    for (int i = 0; i <= MAXN; i ++)
    {
        board[i] = new int[MAXN]();
    }
    std::pair<int, int> last_drop(-1, -1);
    int last_piece = 0;
    for (int round = 0; round < 10; round ++)
    {
        cout << "start round " << round << endl;
        Mcst mcst(board, last_drop, last_piece);
        std::pair<int, int> drop_on = mcst.deduction(1000);
        int x = drop_on.first;
        int y = drop_on.second;
        last_drop.first = x;
        last_drop.second = y;
        last_piece = (last_piece == 0) ? 1 : -1 * last_piece;
        cout << "drop " << last_piece << " on " << "(" << x << ", " << y << ")" << endl;
        board[x][y] = last_piece;
        cout << "after round " << round << endl;
        print_board(board);
        Mcst::check_win(board, last_piece);
    }
}