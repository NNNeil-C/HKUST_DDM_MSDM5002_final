/*
 * @Author: Neil.Chen Zifeng 
 * @Date: 2021-11-01 21:23:55 
 * @Last Modified by: Neil.Chen Zifeng
 * @Last Modified time: 2021-11-02 00:10:06
 */
#ifndef NODE_HPP
#define NODE_HPP
#define MAXN 8
#include <cstdlib>
class Node
{
private:
    int visitd_time;
    int win_time;
    int **game_board;
public:
    Node();
    Node(Node &src);
    ~Node();
};

Node::Node() : visitd_time(0), win_time(0), game_board(NULL)
{
    game_board = new int*[MAXN];
    for (int i = 0; i <= MAXN; i ++)
    {
        game_board[i] = new int[MAXN];
    }
}

Node::~Node()
{
    for (int i = 0; i <= MAXN; i ++)
    {
        free(game_board[i]);
    }
    free(game_board);
}

#endif
