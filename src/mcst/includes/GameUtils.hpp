//
// Created by 陈梓峰 on 5/11/2021.
//

#ifndef HKUST_DDM_MSDM5002_FINAL_GAMEUTILS_HPP
#define HKUST_DDM_MSDM5002_FINAL_GAMEUTILS_HPP

#include <iostream>
#include "../exceptions/CustomBaseException.hpp"

const unsigned int MAXN = 8;
const unsigned int REQUIRED_PIECES = 5;

bool is_empty_game_board(int **game_board) {
    LOGD("%s", "run in ");
    bool is_empty = true;
    for (unsigned int i = 0; i < MAXN; i++) {
        if (!is_empty) {
            break;
        }
        for (unsigned int j = 0; j < MAXN; j++) {
            if (game_board[i][j] != 0) {
                is_empty = false;
                break;
            }
        }
    }
    return is_empty;
}

bool is_full_game_board(int **game_board) {
    LOGD("%s", "run in ");
    bool is_full = true;
    for (unsigned int i = 0; i < MAXN; i++) {
        if (!is_full) {
            break;
        }
        for (unsigned int j = 0; j < MAXN; j++) {
            if (game_board[i][j] == 0) {
                is_full = false;
                break;
            }
        }
    }
    return is_full;
}

void print_board(int **board) {
    LOGD("%s", "start to print game board");
    std::cout << "start print game board" << std::endl;
    for (unsigned int i = 0; i < MAXN; i++) {
        for (unsigned int j = 0; j < MAXN; j++) {
            int val = board[i][j];
            val = (val < 0) ? 2 : val;
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "end print game board" << std::endl;
}

//if win by row
bool check_win_row(int **game_board, int which_piece, int x, int y) {
    LOGD("%s", "run in");
    if (x + REQUIRED_PIECES > MAXN) {
        return false;
    }
    for (int i = x; i < x + REQUIRED_PIECES; i++) {
        if (game_board[i][y] != which_piece) {
            return false;
        }
    }
    return true;
}

//if win by column
bool check_win_col(int **game_board, int which_piece, int x, int y) {
    LOGD("%s", "run in");
    if (y + REQUIRED_PIECES > MAXN) {
        return false;
    }
    for (int j = y; j < y + REQUIRED_PIECES; j++) {
        if (game_board[x][j] != which_piece) {
            return false;
        }
    }
    return true;
}

// if win by diagnal
bool check_win_diagonal(int **game_board, int which_piece, int x, int y) {
    LOGD("%s", "run in");
    if ((x + REQUIRED_PIECES > MAXN) || (y + REQUIRED_PIECES > MAXN)) {
        return false;
    }
    for (int step = 0; step < REQUIRED_PIECES; step++) {
        if (game_board[x + step][y + step] != which_piece) {
            return false;
        }
    }
    return true;
}

// if win by antidiagnal
bool check_win_anti_diagonal(int **game_board, int which_piece, int x, int y) {
    LOGD("%s", "run in");
    if ((x + REQUIRED_PIECES > MAXN) || (y - REQUIRED_PIECES < -1)) {
        LOGD("%s", "run out");
        return false;
    }
    for (int step = 0; step < REQUIRED_PIECES; step++) {
        if (game_board[x + step][y - step] != which_piece) {
            return false;
        }
    }
    LOGD("%s", "run out");
    return true;
}

// if win in some way
bool check_win(int **game_board, int which_piece) {
    for (unsigned int i = 0; i < MAXN; i++) {
        for (unsigned int j = 0; j < MAXN; j++) {
            bool win_flag = false;
            win_flag |= check_win_row(game_board, which_piece, i, j);
            win_flag |= check_win_col(game_board, which_piece, i, j);
            win_flag |= check_win_diagonal(game_board, which_piece, i, j);
            win_flag |= check_win_anti_diagonal(game_board, which_piece, i, j);
            if (win_flag) {
                return true;
            }
        }
    }
    return false;
}

bool in_board(int x, int y) {
    return x >= 0 && x < int(MAXN) && y >= 0 && y < int(MAXN);
}

bool quick_check_win_row(int **game_board, int piece, int x, int y) {
    int number = 1;
    for (int u = x, v = y; in_board(u, v - 1) && (game_board[u][v - 1] == piece); v--) {
        number++;
    }
    for (int u = x, v = y; in_board(u, v + 1) && (game_board[u][v + 1] == piece); v++) {
        number++;
    }
    return number >= REQUIRED_PIECES;
}

bool quick_check_win_col(int **game_board, int piece, int x, int y) {
    int number = 1;
    for (int u = x, v = y; in_board(u - 1, v) && (game_board[u - 1][v] == piece); u--) {
        number++;
    }
    for (int u = x, v = y; in_board(u + 1, v) && (game_board[u + 1][v] == piece); u++) {
        number++;
    }
    return number >= REQUIRED_PIECES;
}

bool quick_check_win_diag(int **game_board, int piece, int x, int y) {
    int number = 1;
    for (int u = x, v = y; in_board(u - 1, v - 1) && (game_board[u - 1][v - 1] == piece); u--, v--) {
        number++;
    }
    for (int u = x, v = y; in_board(u + 1, v + 1) && (game_board[u + 1][v + 1] == piece); u++, v++) {
        number++;
    }
    return number >= REQUIRED_PIECES;
}

bool quick_check_win_anti_diag(int **game_board, int piece, int x, int y) {
    int number = 1;
    for (int u = x, v = y; in_board(u - 1, v + 1) && (game_board[u - 1][v + 1] == piece); u--, v++) {
        number++;
    }
    for (int u = x, v = y; in_board(u + 1, v - 1) && (game_board[u + 1][v - 1] == piece); u++, v--) {
        number++;
    }
    return number >= REQUIRED_PIECES;
}

// judge by the last drop
bool quick_check_win(int **game_board, std::pair<int, int> position) {
    int x = position.first;
    int y = position.second;
    int piece = game_board[x][y];
    if (piece == 0) {
        throw CustomBaseException("call quick check with a 0 piece");
    }
    //row
    if (quick_check_win_row(game_board, piece, x, y)) {
        return true;
    }
    //col
    if (quick_check_win_col(game_board, piece, x, y)) {
        return true;
    }
    //diagonal
    if (quick_check_win_diag(game_board, piece, x, y)) {
        return true;
    }
    //anti diagonal
    if (quick_check_win_anti_diag(game_board, piece, x, y)) {
        return true;
    }
    return false;
}

// a valid position: not occupied and has neighbor piece within a 4*4 matrix
bool is_valid_position(int **game_board, int x, int y) {
    if (game_board[x][y] != 0) {
        return false;
    }
    for (int i = -2; i < 3; i++) {
        for (int j = -2; j < 3; j++) {
            if ((i == 0) && (j == 0)) {
                continue;
            }
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < int(MAXN) && ny >= 0 && ny < int(MAXN)) {
                if (game_board[nx][ny] != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool recycle_game_board(int **board) {
    for (unsigned int i = 0; i < MAXN; i++) {
        delete[] board[i];
    }
    delete[] board;
    return true;
}

#endif //HKUST_DDM_MSDM5002_FINAL_GAMEUTILS_HPP
