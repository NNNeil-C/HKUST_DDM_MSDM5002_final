/*
 * @Author: Neil.Chen Zifeng 
 * @Date: 2021-11-01 21:19:04 
 * @Last Modified by: Neil.Chen Zifeng
 * @Last Modified time: 2021-11-02 17:03:42
 */

#include "node.hpp"
#include <stack>
#include <cmath>
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
    bool check_win(int game_board[][MAXN], int which_piece);
    bool check_win_row(int [][MAXN], int, int, int);
    bool check_win_col(int [][MAXN], int, int, int);
    bool check_win_diagnal(int [][MAXN], int, int, int);
    bool check_win_anti_diagnal(int [][MAXN], int, int, int);
    static int required_pieces;
public:
    Mcst(int **game_board);
    std::pair<int, int> deduction(time_t time_limit);
    ~Mcst();
};

int Mcst::required_pieces = 5;

//init with a certain game board
Mcst::Mcst(int **game_board)
{
    root = new Node(game_board);
    simulation_round = 0;
}

//single status query deduction
std::pair<int, int> Mcst::deduction(time_t time_limit)
{
    using namespace std::chrono;
    milliseconds start_time = duration_cast< milliseconds > (system_clock::now().time_since_epoch());
    while (true)
    {
        //execute single round search
        do_single_search();
        milliseconds current_time = duration_cast< milliseconds > (system_clock::now().time_since_epoch());
        duration<double> time_length = current_time - start_time;
        //time limit reached
        if (time_length.count() > time_limit - 500)
        {
            break;
        }
    }
    // the most visited node is the recommendation
    Node* chosen_node = root->most_visited_child();
    return chosen_node->last_drop;
}

void Mcst::do_single_search()
{
    simulation_round ++;
    std::stack<Node *> dfs_stack;
    Node *current_node = root;
    //select
    //find the max uct son node
    while (current_node != NULL)
    {
        dfs_stack.push(current_node);
        std::list<Node*>::iterator it;
        double max_son_uct = 0;
        Node *max_son = NULL;
        // visit all the chilren
        for (it = current_node->children.begin(); it != current_node->children.end(); it ++)
        {
            Node *current_son = *it;
            double current_son_uct = get_node_uct_value(current_son, simulation_round);
            // find the son with max uct and uncompleted
            if (current_son_uct > max_son_uct && !current_son->is_completed)
            {
                current_son_uct = max_son_uct;
                max_son = current_son;
            }
        }
        current_node = max_son;
    }

    //expand
    current_node = dfs_stack.top();
    Node *new_node = expand(current_node);
    //simluate 1 for win, 0.5 for draw, 0 for lose
    double is_win = do_simulation(new_node);
    //backpropagate
    new_node->visited_time += 1;
    new_node->win_time += is_win;
    while (!dfs_stack.empty())
    {
        is_win = 1 - is_win;
        current_node = dfs_stack.top();
        dfs_stack.pop();
        current_node->visited_time += 1;
        current_node->win_time += is_win;
    }
}

Node* Mcst::expand (Node *currnet_node)
{

}

double Mcst::do_simulation(Node *current_node)
{
    //init
    int next_piece = -1 * current_node->last_piece;
    int game_board[MAXN][MAXN];
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
    while (true)
    {
        std::pair<int, int> next_position = find_random_vaild_position(game_board);
        //if draw
        if (next_position.first == -1 && next_position.second == -1)
        {
            result = 0.5;
            break;
        }
        //drop a new piece
        game_board[next_position.first][next_position.second] = next_piece;
        next_piece = -1 * next_piece;

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
    }
    return result;
}

bool Mcst::check_win (int game_board[][MAXN], int which_piece)
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

bool Mcst::check_win_row (int game_board[][MAXN], int which_piece, int x, int y)
{
    if (x + required_pieces > MAXN)
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

Mcst::~Mcst()
{
    delete(root);
}
