#ifndef HUF_CLASS_STRUCTS_H
#define HUF_CLASS_STRUCTS_H


#include <iostream>
#include <memory>
#include <algorithm>

class Node {
public:
    typedef std::shared_ptr<Node> ptr;
    ptr left{nullptr};
    ptr right{nullptr};
    ptr parent{nullptr};
    Node() = default;
    Node(unsigned char uch, int f) : ch(uch), frequency(f) {};
    Node(const std::string& n, int f) : name(n), frequency(f) {};
    bool operator < (const Node& oth) const;
    std::string get_name() const ;
    unsigned char get_byte();
    int get_frequency() const;
    void set_frequency(int f);
    std::string code();
    void code(const std::string& c);
    friend std::ostream& operator << (std::ostream &out, Node node);
private:
    std::string name{""};
    unsigned char ch{0};
    int frequency{0};
    std::string code_string{""};
};

#endif //HUF_CLASS_STRUCTS_H
