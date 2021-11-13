/*
 * @Author: Neil.Chen Zifeng 
 * @Date: 2021-11-01 21:23:55 
 * @Last Modified by: Neil.Chen Zifeng
 * @Last Modified time: 2021-11-04 20:27:12
 */
#ifndef NODE_HPP
#define NODE_HPP
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
    unsigned int max_child_node_number{};
    std::list<Node*> children;
    std::pair<int, int> last_drop;
    std::list<std::pair<int, int> > possible_drop_positions;
    Node();
    explicit Node(int **);
    Node* most_visited_child() const;
    ~Node();
    bool should_be_completed() const;
    int get_piece(int, int) const;
    void generate_all_possible_successive_drop();
    std::pair<int, int> pop_one_possible_successive_drop();
    Node(const Node &) = delete;
    Node& operator=(const Node &) = delete;
};

//default constructor
Node::Node() : visited_time(0), win_time(0), game_board(nullptr), is_completed(false), max_child_node_number(0)
{
    game_board = new int*[MAXN];
    for (int i = 0; i <= MAXN; i ++)
    {
        game_board[i] = new int[MAXN]{0};
    }
    last_drop = std::pair<int, int> (-1, -1);
    last_piece = 0;
}

//constructor with a game board
Node::Node(int **game_board) : visited_time(0), win_time(0), is_completed(false), max_child_node_number(0)
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

//return the most visited child after search
Node* Node::most_visited_child() const
{
    double most_time = 0;
    Node *most_node = nullptr;
    for (auto current : children)
    {
        if (most_time < current->visited_time)
        {
            most_time = current->visited_time;
            most_node = current;
        }
    }
    return most_node;
}

int Node::get_piece(int x, int y) const
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
                    this->possible_drop_positions.emplace_back(std::make_pair(i, j));
            }
        }
    } else
    {
        //find all valid position
        for (int i = 0; i < MAXN; i ++)
        {
            for (int j = 0; j < MAXN; j ++)
            {
                if (is_valid_position(game_board, i, j))
                {
                    this->possible_drop_positions.emplace_back(std::make_pair(i, j));
                }
            }
        }
    }

    this->max_child_node_number = this->possible_drop_positions.size();
}

std::pair<int, int> Node::pop_one_possible_successive_drop()
{
    if (possible_drop_positions.empty())
    {
        throw std::out_of_range ("pop_one_possible_successive_drop");
    }
    unsigned int random_one = random() % possible_drop_positions.size();
    auto it = possible_drop_positions.begin();
    for (int i = 0; i < random_one; i ++)
    {
        it ++;
    }
    std::pair<int, int> result((*it).first, (*it).second);
    possible_drop_positions.erase(it);
    return result;
}

bool Node::should_be_completed() const
{
    // not try every child node
    if (this->children.size() < this->max_child_node_number) {
        return false;
    }
    bool result = true;
    // if every child is completed, then the father node is also completed
    for_each(this->children.begin(), this->children.end(), [&result](Node *node){
        result &= node->is_completed;
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
