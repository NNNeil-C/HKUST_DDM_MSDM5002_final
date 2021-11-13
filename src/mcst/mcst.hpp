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
#include "exceptions/NoMostVisitedNodeException.hpp"
#include "exceptions/NullPointerExceptions.hpp"
#include <stack>
#include <cmath>
#include <vector>
#include <ctime>
#include <algorithm>

class Mcst
{
private:
    int simulation_round;
    Node *root;
    void do_single_search();
    static double get_node_uct_value(Node *, double, double c=std::sqrt(2));
    static Node *expand(Node *);
    static double do_simulation(const Node *) ;
    static std::pair<int, int> find_random_valid_position(int **);
    static int required_pieces;
    static int time_buffer;
public:
    Mcst(int **game_board, std::pair<int, int>, int);
    std::pair<int, int> deduction(time_t time_limit);
    ~Mcst();
};

int Mcst::required_pieces = 5;
int Mcst::time_buffer = 100;

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
    using namespace std::chrono;
    srand(time(nullptr));
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
        if (time_length.count() * 1000 > double(time_limit - time_buffer))
        {
            break;
        }
    }
    // the most visited node is the recommendation
    LOGD("%s", "ready to get most visited child");
    Node* chosen_node = root->most_visited_child();
    if (chosen_node == nullptr)
    {
        LOGD("%s", "most visited child is null");
        throw CustomBaseException("chosen node is nullptr in current deduction");
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
    auto current_node = root;
    //select
    //find the max uct son node
    while (current_node != nullptr)
    {
        dfs_stack.push(current_node);
        if (current_node->children.size() < current_node->max_child_node_number)
        {
            break;
        }
        double max_son_uct = 0;
        Node *max_son = nullptr;
        // visit all the children
        for (auto current_son : current_node->children)
        {
            double current_son_uct = get_node_uct_value(current_son, simulation_round);
            // find the son with max uct 
            if (max_son_uct < current_son_uct)
            {
                max_son_uct = current_son_uct;
                max_son = current_son;
            }
        }
        current_node = max_son;
    }
    LOGD("%s", "finish selection");
    //expand
    current_node = dfs_stack.top();
    Node *new_node = nullptr;
    if (current_node->children.size() == current_node->max_child_node_number){
        new_node = current_node;
    } else {
        new_node = expand(current_node);
    }
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

double Mcst::do_simulation(const Node *current_node)
{
    //init
    LOGD("%s", "init for doing simulation");
    int next_piece = -1 * current_node->last_piece;
    int **game_board;
    game_board = new int*[MAXN];
    for (int i = 0; i < MAXN; i ++)
    {
        game_board[i] = new int[MAXN];
        memcpy(game_board[i], current_node->game_board[i], sizeof(int) * MAXN);
    }
    //drop alternatively
    double result = 1;
    auto last_drop = current_node->last_drop;
    LOGD("%s", "start dropping");
    while (true)
    {
        //if someone wins
        if (quick_check_win(game_board, last_drop))
        {
            break;
        }
        //if draw
        if (is_full_game_board(game_board))
        {
            result = 0.5;
            break;
        }
        LOGD("%s", "start to find random valid position");
        last_drop = find_random_valid_position(game_board);
        LOGD("%s", "found random valid position");
        LOGD("%s %d %d", "found random valid position", last_drop.first, last_drop.second);
        //drop a new piece
        game_board[last_drop.first][last_drop.second] = next_piece;
        next_piece = -1 * next_piece;
        result = 1 - result;
    }
    return result;
}


std::pair<int, int> Mcst::find_random_valid_position (int **game_board)
{
    LOGD("%s", "run in");
    std::vector<std::pair<int, int > > valid_positions;
    //if the game board is empty, all position is valid
    //randomly pick one position on the game_board
    if (is_empty_game_board(game_board))
    {
        return std::make_pair(MAXN / 2, MAXN / 2);
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
                    valid_positions.emplace_back(std::make_pair(i, j));
                }
            }
        }
        LOGD("%s %lu", "valid_positions size:", valid_positions.size());
        if (valid_positions.empty()) {
            print_board(game_board);
            throw CustomBaseException("unable to find a ran valid position, the game board is full.");
        }
        auto chosen_pair = random() % valid_positions.size();
        return valid_positions[chosen_pair];
    }
}

double Mcst::get_node_uct_value(Node *current_node, double simulation_round, double c)
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