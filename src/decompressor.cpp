#include <string>
#include <iostream>
#include <bitset>
#include <fstream>
#include "constants.h"
#include "types.h"
#include "util.h"

void read_node(std::ifstream& file, Node* node) {
    unsigned char node_type;
    file >> node_type;
    node->type = static_cast<NodeType>(node_type);
    if (node->type == LEAF_NODE)
        file >> node->chr;
}

Node* read_tree(std::ifstream& file) {
    Node* root = new Node;
    read_node(file, root);
    if (root->type == INTERNAL_NODE) {
        root->left = read_tree(file);
        root->right = read_tree(file);
    }
    return root;
}

unsigned char get_bit(const char* const buffer, unsigned int& byte_count, unsigned char& bit_count) {
    char byte = buffer[byte_count];
    unsigned char bit = (byte >> bit_count) & 1;
    (bit_count)++;
    if (bit_count == BITS_PER_BYTE) {
        bit_count = 0;
        byte_count += 1;
    }
    return bit;
}

void get_chars(const char* const buffer, const unsigned int bufsize, char* const outbuf, Node* cur_node, Node* const root, FILE* outfile) {
    unsigned int byte_count = 0, out_byte_count = 0;
    unsigned char bit_count = 0;
    for (int i = 0; i < bufsize * BITS_PER_BYTE; i++) {
        unsigned char bit = get_bit(buffer, byte_count, bit_count);
        if (bit)
            cur_node = cur_node->right;
        else
            cur_node = cur_node->left;
        if (cur_node->type == LEAF_NODE) {
            outbuf[out_byte_count] = cur_node->chr;
            out_byte_count++;
            if (out_byte_count == BUFFER_SIZE)
                fwrite(outbuf, sizeof(char), BUFFER_SIZE, outfile);
        }
        if (cur_node->type != INTERNAL_NODE)
            cur_node = root;
    }
    if (out_byte_count)
        fwrite(outbuf, sizeof(char), out_byte_count, outfile);
}

void read_file_contents(std::ifstream& file, FILE* outfile, const unsigned int num_bytes, Node* const root) {
    Node cur_node = *root;
    char* buffer = new char[BUFFER_SIZE];
    char* outbuf = new char[BUFFER_SIZE];
    unsigned int full_chunks = num_bytes / BUFFER_SIZE;
    unsigned int leftover_bytes = num_bytes % BUFFER_SIZE;
    for (int i = 0; i < full_chunks; i++) {
        file.read(buffer, BUFFER_SIZE);
        get_chars(buffer, BUFFER_SIZE, outbuf, &cur_node, root, outfile);
    }
    if (leftover_bytes) {
        file.read(buffer, leftover_bytes);
        get_chars(buffer, leftover_bytes, outbuf, &cur_node, root, outfile);
    }
    delete[] buffer;
    delete[] outbuf;
}

int main() {
    std::string filename = "out.bin";
    std::ifstream file(filename, std::ios::binary);
    std::string out_filename = "decompressed.txt";
    FILE* outfile = fopen(out_filename.c_str(), "wb");
    Node* root = read_tree(file);
    unsigned int num_bytes;
    file >> num_bytes;
    read_file_contents(file, outfile, num_bytes, root);
    file.close();
    fclose(outfile);
}