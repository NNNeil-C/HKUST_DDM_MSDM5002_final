/*
 * @Author: Neil.Chen Zifeng 
 * @Date: 2021-11-02 00:08:26 
 * @Last Modified by: Neil.Chen Zifeng
 * @Last Modified time: 2021-11-04 16:22:01
 */
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "mcst.hpp"
#define MAXN 8
using namespace std;
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