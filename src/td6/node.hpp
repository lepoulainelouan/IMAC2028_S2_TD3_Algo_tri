#pragma once
#include <string>
#include <iostream>

struct Node {
    int value;
    Node* left  { nullptr };
    Node* right { nullptr };
};

Node* create_node(int value);

void pretty_print_left_right(Node const& node, std::string const& prefix, bool is_left);
void pretty_print_left_right(Node const& node);