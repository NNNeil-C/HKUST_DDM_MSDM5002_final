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
#include <cstring>
class Node
{
private:
    int visited_time;
    int win_time;
    int **game_board;
public:
    Node();
    Node(Node &);
    ~Node();
};

//default constructor
Node::Node() : visited_time(0), win_time(0), game_board(NULL)
{
    game_board = new int*[MAXN];
    for (int i = 0; i <= MAXN; i ++)
    {
        game_board[i] = new int[MAXN];
    }
}

//copy constructor
Node::Node(Node &src)
{
    this->visited_time = src.visited_time;
    this->win_time = src.win_time;
    game_board = new int*[MAXN];
    for (int i = 0; i <= MAXN; i ++)
    {
        game_board[i] = new int[MAXN];
        //copy from src node
        memcpy(game_board[i], src.game_board[i], sizeof(int) * MAXN);
    }

}

//destructor
Node::~Node()
{
    for (int i = 0; i <= MAXN; i ++)
    {
        free(game_board[i]);
    }
    free(game_board);
}

#endif
