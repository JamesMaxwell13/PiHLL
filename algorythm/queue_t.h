#ifndef HUF_CLASS_QUEUE_T_H
#define HUF_CLASS_QUEUE_T_H

#include <queue>
#include "structs.h"

class LowestPriority {
public:
    bool operator () (const Node::ptr& left, const Node::ptr& right) const;
};

class Queue_t {
private:
    std::priority_queue<Node::ptr, std::vector<Node::ptr>, LowestPriority> q_data;
public:
    Queue_t(std::vector<int>& frequency);
    void build_tree();
    Node::ptr top();
};


#endif //HUF_CLASS_QUEUE_T_H
