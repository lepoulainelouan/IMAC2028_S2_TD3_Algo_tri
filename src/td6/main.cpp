#include "node.hpp"

int main() {
    Node* root = create_node(10);
    pretty_print_left_right(*root);
    delete root;
}