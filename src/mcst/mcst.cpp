/*
 * @Author: Neil.Chen Zifeng 
 * @Date: 2021-11-01 21:19:04 
 * @Last Modified by: Neil.Chen Zifeng
 * @Last Modified time: 2021-11-01 21:26:45
 */
#include "node.hpp"
#include <stack>
#include <cmath>
#include <algorithm>

class Mcst
{
private:
    int simulation_round;
    Node *root;
    void do_single_search();
    double get_node_uct_value(Node *, double simlation_time, double c=std::sqrt(2));
public:
    Mcst(int **game_board);
    std::pair<int, int> deduction(time_t time_limit);
    ~Mcst();
};

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
    //simluate
    bool is_win = do_simulation(new_node);
    //backpropagate
    new_node->visited_time ++;
    new_node->win_time += is_win;
    while (!dfs_stack.empty())
    {
        is_win = !is_win;
        current_node = dfs_stack.top();
        dfs_stack.pop();
        current_node->visited_time ++;
        current_node->win_time += is_win;
    }
}

Mcst::~Mcst()
{
    delete(root);
}
