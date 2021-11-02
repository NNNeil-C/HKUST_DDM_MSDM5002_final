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
#include <list>
class Node
{
private:
    int **game_board;
    
public:
    int visited_time;
    int win_time;
    bool is_completed;
    std::list<Node*> children;
    std::pair<int, int> last_drop;
    Node();
    Node(Node &);
    Node(int **);
    Node* most_visited_child();
    ~Node();
    bool should_be_completed();
};

//default constructor
Node::Node() : visited_time(0), win_time(0), game_board(NULL), is_completed(false)
{
    game_board = new int*[MAXN];
    for (int i = 0; i <= MAXN; i ++)
    {
        game_board[i] = new int[MAXN];
    }
    last_drop = std::pair<int, int> (-1, -1);
}

//constrtor with a game board
Node::Node(int **game_board) : visited_time(0), win_time(0), is_completed(false)
{
    this->game_board = new int*[MAXN];
    for (int i = 0; i <= MAXN; i ++)
    {
        this->game_board[i] = new int[MAXN];
        //copy from src node
        memcpy(this->game_board[i], game_board[i], sizeof(int) * MAXN);
    }
    last_drop = std::pair<int, int> (-1, -1);
}

//copy constructor
Node::Node(Node &src)
{
    this->visited_time = src.visited_time;
    this->win_time = src.win_time;
    this->game_board = new int*[MAXN];
    for (int i = 0; i <= MAXN; i ++)
    {
        this->game_board[i] = new int[MAXN];
        //copy from src node
        memcpy(this->game_board[i], src.game_board[i], sizeof(int) * MAXN);
    }
    this->last_drop = src.last_drop;
    this->is_completed = src.is_completed;
}

//return the most visited child after search
Node* Node::most_visited_child()
{
    std::list<Node*>::iterator it;
    int most_time = 0;
    Node *most_node = NULL;
    for (it = children.begin(); it != children.end(); it ++)
    {
        Node *current = *it;
        if (most_time < current->visited_time)
        {
            most_time = current->visited_time;
            most_node = current;
        }
    }
    return most_node;
}

//destructor
Node::~Node()
{
    std::list<Node*>::iterator it;
    for (it = children.begin(); it != children.end(); it ++)
    {
        delete(*it);
    }
    for (int i = 0; i <= MAXN; i ++)
    {
        delete(game_board[i]);
    }
    delete(game_board);
}

#endif
