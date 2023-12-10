#include "queue_t.h"

bool LowestPriority::operator () (const Node::ptr& left, const Node::ptr& right) const{
    return left->get_frequency() > right->get_frequency();
};

Queue_t::Queue_t(std::vector<int>& frequency) {
    unsigned char byte = 0;
    for_each(frequency.begin(), frequency.end(), [this, &byte](const auto &value) {
        if (value != 0) {
            Node::ptr node = std::make_shared<Node>(byte, value);
            q_data.push(node);
        }
        byte++;
    });
}

void Queue_t::build_tree() {
    while (q_data.size() > 1) {
        Node::ptr x = q_data.top();
        q_data.pop();
        Node::ptr y = q_data.top();
        q_data.pop();
        Node::ptr z = std::make_shared<Node>(0, x->get_frequency() + y->get_frequency());

        z->left = x;
        z->right = y;

        x->parent = z;
        x->parent = z;

        q_data.push(z);
    }
}

Node::ptr Queue_t::top() {
    return q_data.top();
}