/*
 * @Author: Neil.Chen Zifeng 
 * @Date: 2021-11-01 21:19:04 
 * @Last Modified by: Neil.Chen Zifeng
 * @Last Modified time: 2021-11-01 21:26:45
 */
#include "node.hpp"

class mcst
{
private:
    Node *root;
    void do_single_search();
public:
    mcst(int **game_board);
    std::pair<int, int> deduction(time_t time_limit);
    ~mcst();
};

mcst::mcst(int **game_board)
{
    root = new Node(game_board);
}



std::pair<int, int> mcst::deduction(time_t time_limit)
{
    using namespace std::chrono;
    milliseconds start_time = duration_cast< milliseconds > (system_clock::now().time_since_epoch());
    while (true)
    {
        do_single_search();
        milliseconds current_time = duration_cast< milliseconds > (system_clock::now().time_since_epoch());
        duration<double> time_length = current_time - start_time;
        if (time_length.count() > time_limit - 500)
        {
            break;
        }
    }
    Node* chosen_node = root->most_visited_child();
    return chosen_node->last_drop;
}

mcst::~mcst()
{
    delete(root);
}
