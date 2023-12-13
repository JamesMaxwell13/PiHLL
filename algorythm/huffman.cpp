#include "huffman.h"


int Huffman_code::read_file( std::vector<int>& frequency) {
    std::ifstream ifs(filename, std::ifstream::binary);
    if(!ifs.is_open()) {
        //std::cout << "error file access" << std::endl;
        return 1;
    }
    char ch;
    while(ifs.read(&ch, 1)) {
        frequency[static_cast<unsigned char>(ch)]++; //to unsigned char
    }
    ifs.close();
    return 0;
}

void Huffman_code::make_code(Node::ptr& node, std::string str, std::vector<std::string>& codes) {
    if(node->left != nullptr) {
        make_code(node->left, str + '0', codes);
    }
    if(node->right != nullptr) {
        make_code(node->right, str + '1', codes);
    }
    if(node->left == nullptr && node->right == nullptr) {
        node->code(str);
        codes[node->get_byte()] = str;
    }
}

int Huffman_code::message_to_code(const std::vector<std::string>& codes, std::string& message) {
    std::ifstream ifs(filename, std::ifstream::binary);
    if(!ifs.is_open()) {
        //std::cout << "error file access" << std::endl;
        return 1;
    }
    char ch;
    while(ifs.read(&ch, 1)) {
        message += codes[static_cast<unsigned char>(ch)];
    }
    return 0;
}

int Huffman_code::write_file(std::vector<int>& frequency, const std::string message) {
    std::string new_filename = filename + ".arch";
    std::ofstream ofs(new_filename, std::ofstream::binary);
    if(!ofs.is_open()) {
        //std::cout << "error archive file access" << std::endl;
        return 1;
    }
    unsigned char count = count_if(frequency.begin(), frequency.end(), [](const int& value) { return (value != 0); });
    ofs.write(reinterpret_cast<char*> (&count), sizeof(count));

    unsigned char index = 0;
    for_each(frequency.begin(), frequency.end(), [&index, &ofs] (int &value) mutable {
        if(value != 0) {
            ofs.write(reinterpret_cast<char*> (&index), sizeof(index));
            ofs.write(reinterpret_cast<char*> (&value), sizeof(value));
        }
        index++;
    });

    int byte_count = message.size() / CHAR_BIT;
    unsigned char modulo = message.size() % CHAR_BIT;
    ofs.write(reinterpret_cast<char*> (&byte_count), sizeof(byte_count));
    ofs.write(reinterpret_cast<char*> (&modulo), sizeof(modulo));

    int i = 0;
    for(; i < byte_count; i++) {
        std::bitset<CHAR_BIT> b(message.substr(i * CHAR_BIT, CHAR_BIT));
        unsigned char value = static_cast<unsigned char>(b.to_ulong());
        ofs.write(reinterpret_cast<char*> (&value), sizeof(value));
    }
    if(modulo > 0) {
        std::bitset<CHAR_BIT> b(message.substr(i * CHAR_BIT, modulo));
        unsigned char value = static_cast<unsigned char>(b.to_ulong());
        ofs.write(reinterpret_cast<char*> (&value), sizeof(value));
    }
    ofs.close();
    return 0;
}

int Huffman_code::read_decoding_file(std::vector<int>& frequency, std::string& message) {
    // std::string new_filename = filename + ".arch";
    std::ifstream ifs(filename, std::ifstream::binary);
    if(!ifs.is_open()) {
        //std::cout << "error archive file access" << std::endl;
        return 1;
    }
    unsigned char count = 0;
    ifs.read(reinterpret_cast<char*> (&count), sizeof(count));

    int i = 0;
    while(i < count) {
        unsigned char ch;
        ifs.read(reinterpret_cast<char*> (&ch), sizeof(ch));

        int f = 0;
        ifs.read(reinterpret_cast<char*> (&f), sizeof(f));
        frequency[ch] = f;
        i++;
    }

    int byte_count = 0;
    unsigned char modulo = 0;

    ifs.read(reinterpret_cast<char*> (&byte_count), sizeof(byte_count));
    ifs.read(reinterpret_cast<char*> (&modulo), sizeof(modulo));

    i = 0;
    for(; i < byte_count; i++) {
        unsigned char byte;
        ifs.read(reinterpret_cast<char*> (&byte), sizeof(byte));
        std::bitset<CHAR_BIT> b(byte);
        message += b.to_string();
    }
    if(modulo > 0) {
        unsigned char byte;
        ifs.read(reinterpret_cast<char*> (&byte), sizeof(byte));
        std::bitset<CHAR_BIT> b(byte);
        message += b.to_string().substr(CHAR_BIT - modulo, CHAR_BIT);
    }
    return 0;
}

void Huffman_code::make_char(const Node::ptr& root, const std::string& message, std::string&text) {
    Node::ptr node = root;
    for(size_t i = 0; i < message.size(); i++) {
        char ch = message[i];
        if(ch == '0') {
            if (node->left != nullptr) {
                node = node->left;
                if (node->left == nullptr && node->right == nullptr) {
                    text += node->get_byte();
                    node = root;
                }
            }
        }
        else if(ch == '1') {
            if (node->right != nullptr) {
                node = node->right;
                if (node->left == nullptr && node->right == nullptr) {
                    text += node->get_byte();
                    node = root;
                }
            }
        }
    }
}

int Huffman_code::write_decoding_file(std::string& text) {
    std::string old_filename = filename.substr(0, filename.rfind(".arch")) ;
    std::string new_filename;
    std::ifstream exist(old_filename);
    if(exist.is_open()) {
        new_filename = old_filename.substr(0, old_filename.rfind('.'))
                       + "_1" + old_filename.substr(old_filename.rfind('.'), old_filename.size());
        exist.close();
    }
    else
        new_filename = old_filename;

    std::ofstream ofs(new_filename, std::ofstream::binary);
    if(!ofs.is_open()) {
        //std::cout << "error archive file access" << std::endl;
        return 1;
    }
    ofs << text;
    ofs.close();
    return 0;
}

Huffman_code::~Huffman_code() {
    message.clear();
    filename.clear();
}

bool Huffman_code::is_compressed() {
    if(filename.rfind(".arch") == std::string::npos)
        return false;
    return true;
}

bool Huffman_code::can_compress() {
    if(filename.rfind(".arch") == std::string::npos)
        return true;
    return false;
}

std::string Huffman_code::compress_file() {
    if(!can_compress())
        return std::string("Can't compress this file");

    std::vector<int> frequency(0x100, 0);
    if(read_file(frequency) == 1)
        return std::string("Error file reading");

    Queue_t queue(frequency);
    queue.build_tree();
    std::vector<std::string> codes(0x100, "");
    Node::ptr root = queue.top();
    make_code(root, "", codes);

    if(message_to_code(codes, message) == 1)
        return std::string("Error making code");
    if(write_file(frequency, message) == 1)
        return std::string("Error writing data to file");
    return std::string("Compressing was successfull");
}

std::string Huffman_code::decompress_file() {
    if(!is_compressed())
        return std::string("Cannot decompress this file");

    std::vector<int> frequency(0x100, 0);

    if(read_decoding_file(frequency, message) == 1)
        return std::string("Error file reading");

    Queue_t queue2(frequency);
    queue2.build_tree();
    Node::ptr root2 = queue2.top();

    std::string text = "";
    make_char(root2, message, text);
    if(write_decoding_file(text) == 1)
        return std::string("Error writing data to file");
    return std::string("Decompressing was succesfull");
}
