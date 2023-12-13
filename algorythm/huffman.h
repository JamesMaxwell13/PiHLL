#ifndef HUF_CLASS_HUFFMAN_H
#define HUF_CLASS_HUFFMAN_H

#include "structs.h"
#include "queue_t.h"
#include <fstream>
#include <vector>
#include <bitset>


class Huffman_code {
private:
    std::string filename;
    std::string message = "";

    int read_file(std::vector<int>& frequency);

    void make_code(Node::ptr& node, std::string str, std::vector<std::string>& codes);

    int message_to_code(const std::vector<std::string>& codes, std::string &message);

    int write_file(std::vector<int>& frequency, const std::string message);

    int read_decoding_file(std::vector<int>& frequency, std::string& message);

    void make_char(const Node::ptr& root, const std::string& message, std::string&text);

    int write_decoding_file(std::string& text);

public:
    Huffman_code(std::string file) : filename(file) {}
    ~Huffman_code();
    bool is_compressed();
    bool can_compress();
    std::string compress_file();
    std::string decompress_file();
};






#endif //HUF_CLASS_HUFFMAN_H
