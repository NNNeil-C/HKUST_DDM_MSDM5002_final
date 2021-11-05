/*
 * @Author: Neil.Chen Zifeng 
 * @Date: 2021-11-01 21:23:55 
 * @Last Modified by: Neil.Chen Zifeng
 * @Last Modified time: 2021-11-04 20:27:12
 */
#ifndef NODE_HPP
#define NODE_HPP
#define MAXN 8
#include <cstdlib>
#include <cstring>
#include <list>
#include "LogUtils.h"
#include "GameUtils.hpp"

class Node
{
public:
    int **game_board;
    double visited_time;
    double win_time;
    bool is_completed;
    int last_piece;
    int max_child_node_number;
    std::list<Node*> children;
    std::pair<int, int> last_drop;
    std::list<std::pair<int, int> > possible_drop_positions;
    Node();
    Node(Node &);
    Node(int **);
    Node* most_visited_child();
    ~Node();
    bool should_be_completed();
    int get_piece(int, int);
    void generate_all_possible_successive_drop();
    std::pair<int, int> pop_one_possible_successive_drop();
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
    last_piece = 0;
}

//constrtor with a game board
Node::Node(int **game_board) : visited_time(0), win_time(0), is_completed(false)
{
    this->game_board = new int*[MAXN];
    for (int i = 0; i < MAXN; i ++)
    {
        this->game_board[i] = new int[MAXN];
        //copy from src node
        memcpy(this->game_board[i], game_board[i], sizeof(int) * MAXN);
    }
    last_drop = std::pair<int, int> (-1, -1);
    last_piece = 0;
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
    this->last_piece = src.last_piece;
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

int Node::get_piece(int x, int y)
{
    return game_board[x][y];
}

void Node::generate_all_possible_successive_drop()
{
    if (is_empty_game_board(this->game_board))
    {
        for (int i = 0; i < MAXN; i ++)
        {
            for (int j = 0; j < MAXN; j ++)
            {
                    this->possible_drop_positions.push_back(std::make_pair(i, j));
            }
        }
    } else
    {
        //find all valid position and randomly pick one
        for (int i = 0; i < MAXN; i ++)
        {
            for (int j = 0; j < MAXN; j ++)
            {
                if (is_valid_position(game_board, i, j))
                {
                    this->possible_drop_positions.emplace_back(i, j);
                }
            }
        }
    }

    this->max_child_node_number = this->possible_drop_positions.size();
}

std::pair<int, int> Node::pop_one_possible_successive_drop()
{
    if (possible_drop_positions.size() <= 0)
    {
        throw std::out_of_range ("pop_one_possible_successive_drop");
    }
    int random_one = rand() % possible_drop_positions.size();
    std::list<std::pair<int, int> >::iterator it = possible_drop_positions.begin();
    for (int i = 0; i < random_one; i ++)
    {
        it ++;
    }
    std::pair<int, int> result((*it).first, (*it).second);
    possible_drop_positions.erase(it);
    return result;
}

bool Node::should_be_completed()
{
    // not try every child node
    if (this->children.size() < this->max_child_node_number) {
        return false;
    }
    bool result = true;
    for_each(this->children.begin(), this->children.end(), [&result](Node *node){
        result |= node->is_completed;
    });
    return result;
}

//destructor
Node::~Node()
{
    std::list<Node*>::iterator it;
    for (it = children.begin(); it != children.end(); it ++)
    {
        delete(*it);
    }
    for (int i = 0; i < MAXN; i ++)
    {
        delete(game_board[i]);
    }
    delete(game_board);
}

#endif
