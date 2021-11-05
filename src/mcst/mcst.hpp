/*
 * @Author: Neil.Chen Zifeng 
 * @Date: 2021-11-01 21:19:04 
 * @Last Modified by: Neil.Chen Zifeng
 * @Last Modified time: 2021-11-04 16:33:34
 */
#ifndef MCST_HPP
#define MCST_HPP
#include "node.hpp"
#include "LogUtils.h"
#include "GameUtils.hpp"
#include <stack>
#include <cmath>
#include <vector>
#include <ctime>
#include <algorithm>
#define MAXN 8

class Mcst
{
private:
    int simulation_round;
    Node *root;
    void do_single_search();
    double get_node_uct_value(Node *, double simlation_time, double c=std::sqrt(2));
    Node *expand(Node *);
    double do_simulation(Node *);
    std::pair<int, int> *find_random_valid_position(int **);
    static int required_pieces;
public:
    Mcst(int **game_board, std::pair<int, int>, int);
    std::pair<int, int> deduction(time_t time_limit);
    static bool check_win(int **, int which_piece);
    static bool check_win_row(int **, int, int, int);
    static bool check_win_col(int **, int, int, int);
    static bool check_win_diagnal(int **, int, int, int);
    static bool check_win_anti_diagnal(int **, int, int, int);
    ~Mcst();
};

int Mcst::required_pieces = 5;

//init with a certain game board
Mcst::Mcst(int **game_board, std::pair<int, int> last_drop, int last_piece)
{
    LOGD("%s", "mcst()");
    root = new Node(game_board);
    LOGD("%s", "created root");
    root->last_drop = last_drop;
    root->last_piece = last_piece;
    root->generate_all_possible_successive_drop();
    root->is_completed = root->should_be_completed();
    simulation_round = 0;
    srand(time(NULL));
}

//single status query deduction
std::pair<int, int> Mcst::deduction(time_t time_limit)
{
    using namespace std::chrono;
    LOGD("%s", "starting deducting");
    milliseconds start_time = duration_cast< milliseconds > (system_clock::now().time_since_epoch());
    while (true)
    {
        //execute single round search
        LOGD("%s", "ready to do single search");
        do_single_search();
        LOGD("%s", "finish doing single search");
        milliseconds current_time = duration_cast< milliseconds > (system_clock::now().time_since_epoch());
        duration<double> time_length = current_time - start_time;
        //time limit reached
        if (time_length.count() * 1000 > time_limit - 500)
        {
            break;
        }
    }
    // the most visited node is the recommendation
    LOGD("%s", "ready to get most visited childe");
    Node* chosen_node = root->most_visited_child();
    if (chosen_node == nullptr)
    {
        LOGD("%s", "most visited child is null");
    } else{
        LOGD("%s", "got most visited child");
    }
    LOGD("%s %d %d", "the chosen drop is ", chosen_node->last_drop.first, chosen_node->last_drop.second);
    return chosen_node->last_drop;
}

void Mcst::do_single_search()
{
    simulation_round ++;
    LOGD("%s %d", "start single search, round", simulation_round);
    std::stack<Node *> dfs_stack;
    Node *current_node = root;
    //select
    //find the max uct son node
    while (current_node != NULL)
    {
        dfs_stack.push(current_node);
        if (current_node->children.size() < current_node->max_child_node_number)
        {
            break;
        }
        std::list<Node*>::iterator it;
        double max_son_uct = 0;
        Node *max_son = NULL;
        // visit all the chilren
        for (it = current_node->children.begin(); it != current_node->children.end(); it ++)
        {
            Node *current_son = *it;
            double current_son_uct = get_node_uct_value(current_son, simulation_round);
            // find the son with max uct 
            if (current_son_uct > max_son_uct)
            {
                current_son_uct = max_son_uct;
                max_son = current_son;
            }
        }
        current_node = max_son;
    }
    LOGD("%s", "finish selection");

    //expand
    current_node = dfs_stack.top();
    Node *new_node = expand(current_node);
    LOGD("%s", "finish expansion");
    //simluate 1 for win, 0.5 for draw, 0 for lose
    double is_win = do_simulation(new_node);
    LOGD("%s", "finish simulation");
    //backpropagate
    new_node->visited_time += 1;
    new_node->win_time += is_win;
    //if no expand
    if (new_node == current_node)
    {
        dfs_stack.pop();
    }
    while (!dfs_stack.empty())
    {
        is_win = 1 - is_win;
        current_node = dfs_stack.top();
        dfs_stack.pop();
        current_node->visited_time += 1;
        current_node->win_time += is_win;
        // is_completed should also handle in backpropagation
        current_node->is_completed = current_node->should_be_completed();
    }
    LOGD("%s", "finish backpropagation");
}

// how to identify each child node as different movement without repeat?
Node* Mcst::expand (Node *current_node)
{
    //if the is_completed, it's no need to expand
    if (current_node->is_completed)
    {
        LOGD("%s", "not expand");
        return current_node;
    }
    Node *new_node = new Node(current_node->game_board);
    current_node->children.push_back(new_node);
    LOGD("%s", "added child node");
    //set last dropÍ
    new_node->last_drop = current_node->pop_one_possible_successive_drop();
    //set last piece
    //as oppsite to father node, if it's first drop of a game, drop a white piece(1)
    new_node->last_piece = (current_node->last_piece != 0) ? -1 * current_node->last_piece : 1;
    //drop last_piece on last_drop
    new_node->game_board[new_node->last_drop.first][new_node->last_drop.second] = new_node->last_piece;
    //generate all successive drop, and check if it's completed
    new_node->generate_all_possible_successive_drop();
    new_node->is_completed = new_node->should_be_completed();
    return new_node;
}

double Mcst::do_simulation(Node *current_node)
{
    //init
    LOGD("%s", "init for doing simulation");
    int next_piece = -1 * current_node->last_piece;
    int **game_board;
    game_board = new int*[MAXN];
    for (int i = 0; i <= MAXN; i ++)
    {
        game_board[i] = new int[MAXN]();
    }
    //copy game board status
    for (int i = 0; i < MAXN; i ++)
    {
        for (int j = 0; j < MAXN; j ++)
        {
            game_board[i][j] = current_node->get_piece(i, j);
        }
    }
    //drop alternatively
    double result = 0;
    LOGD("%s", "start dropping");
    std::pair<int, int> next_position(0, 0);
    while (true)
    {
        //if someone wins
        if (check_win(game_board, current_node->last_piece))
        {
            result = 1;
            break;
        }
        if (check_win(game_board, -1 * current_node->last_piece))
        {
            result = 0;
            break;
        }
        //if draw
        if (is_full_game_board(game_board))
        {
            result = 0.5;
            break;
        }
        LOGD("%s", "start to find random valid position");
        std::pair<int, int> *suggested_position = find_random_valid_position(game_board);
        next_position.first = suggested_position->first;
        next_position.second = suggested_position->second;
        delete(suggested_position);
        LOGD("%s", "found random valid position");
        LOGD("%s %d %d", "found random valid position", next_position.first, next_position.second);
        //drop a new piece
        game_board[next_position.first][next_position.second] = next_piece;
        next_piece = -1 * next_piece;
    }
    return result;
}

// if win in some way
bool Mcst::check_win (int **game_board, int which_piece)
{
    for (int i = 0; i < MAXN; i ++)
    {
        for (int j = 0; j < MAXN; j ++)
        {
            bool win_flag = false;
            win_flag |= check_win_row(game_board, which_piece, i, j);
            win_flag |= check_win_col(game_board, which_piece, i, j);
            win_flag |= check_win_diagnal(game_board, which_piece, i, j);
            win_flag |= check_win_anti_diagnal(game_board, which_piece, i, j);
            if (win_flag)
            {
                return true;
            }
        }
    }
    return false;
}

//if win by row
bool Mcst::check_win_row (int **game_board, int which_piece, int x, int y)
{
    LOGD("%s", "run in");
    if (x + required_pieces >= MAXN)
    {
        return false;
    }
    for (int i = x; i < x + required_pieces; i ++)
    {
        if (game_board[i][y] != which_piece)
        {
            return false;
        }   
    }
    return true;
}

//if win by column
bool Mcst::check_win_col (int **game_board, int which_piece, int x, int y)
{
    LOGD("%s", "run in");
    if (y + required_pieces >= MAXN)
    {
        return false;
    }
    for (int j = y; j < y + required_pieces; j ++)
    {
        if (game_board[x][j] != which_piece)
        {
            return false;
        }
    }
    return true;
}

// if win by diagnal
bool Mcst::check_win_diagnal (int **game_board, int which_piece, int x, int y)
{
    LOGD("%s", "run in");
    if ((x + required_pieces >= MAXN) || (y + required_pieces >= MAXN))
    {
        return false;
    }
    for (int step = 0; step < required_pieces; step ++)
    {
        if (game_board[x+step][y+step] != which_piece)
        {
            return false;
        }
    }
    return true;
}

// if win by antidiagnal
bool Mcst::check_win_anti_diagnal (int **game_board, int which_piece, int x, int y)
{
    LOGD("%s", "run in");
    if ((x + required_pieces >= MAXN) || (y - required_pieces < 0))
    {
        LOGD("%s", "run out");
        return false;
    }
    for (int step = 0; step < required_pieces; step ++)
    {
        if (game_board[x+step][y-step] != which_piece)
        {
            return false;
        }
    }
    LOGD("%s", "run out");
    return true;
}

std::pair<int, int>* Mcst::find_random_valid_position (int **game_board)
{
    LOGD("%s", "run in");
    std::vector<std::pair<int, int > > valid_positions;
    //reserve cause segment fault, why?
    //valid_positions.reserve(32);
    //if the game board is empty, all position is valid
    //randomly pick one position on the game_board
    if (is_empty_game_board(game_board))
    {
        LOGD("%s", "empty game board");
        int x = rand() % MAXN;
        int y = rand() % MAXN;
        LOGD("%s %d %d", "game board is empty, randomly choose", x, y);
        auto *result = new std::pair<int, int>(x, y);
        LOGD("%s", "set result");
        return result;
    } else 
    {
        LOGD("%s", "common game board");
        //find all valid position and randomly pick one
        for (int i = 0; i < MAXN; i ++)
        {
            for (int j = 0; j < MAXN; j ++)
            {
                if (is_valid_position(game_board, i, j))
                {
                    valid_positions.emplace_back(i, j);
                }
            }
        }
        LOGD("%s %d", "valid_positions size:", valid_positions.size());
        if (valid_positions.size() == 0) {
            print_board(game_board);
            return new std::pair<int, int>(-1, -1);
        }
        int chosen_pair = rand() % valid_positions.size();
        return new std::pair<int, int>(valid_positions[chosen_pair].first, valid_positions[chosen_pair].second);
    }
    return nullptr;
}

double Mcst::get_node_uct_value(Node *current_node, double simlation_time, double c)
{
    double wins = current_node->visited_time - current_node->win_time;
    double value = wins / current_node->visited_time;
    value += c * std::sqrt(std::log(simulation_round) / current_node->visited_time);
    return value;
}

Mcst::~Mcst()
{
    delete(root);
}
#endif