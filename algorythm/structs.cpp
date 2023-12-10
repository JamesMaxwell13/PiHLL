#include "structs.h"


bool Node::operator < (const Node& oth) const {
    return frequency < oth.frequency;
}

std::ostream& operator << (std::ostream &out, Node node) {
    out << node.get_name() << " - " << node.frequency << std::endl;
    return out;
}

std::string Node::get_name() const {
    if (ch == 0) { return name; }
    else {
        if(ch == 10) { return "\\n"; }
        return std::string(1, static_cast<char>(ch));
    }
}

unsigned char Node::get_byte() {
    return ch;
}

int Node::get_frequency() const  {
    return frequency;
}

void Node::set_frequency(int f) {
    frequency = f;
}

std::string Node::code() {
    return code_string;
}

void Node::code(const std::string& c) {
    code_string = c;
}

