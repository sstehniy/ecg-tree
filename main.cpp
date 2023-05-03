//
// Created by Stanislav Stehniy on 01.05.23.
//

#include "node.h"
#include "iostream"

int main() {
    node *tree = create_complete_tree(2, 4);
    node *cycled_node1 = new node();
    cycled_node1->add_child(cycled_node1);
    cycled_node1->add_child(cycled_node1);
    tree->get_child(1)->get_child(1)->add_child(cycled_node1);
    node *cycled_node2 = new node();
    cycled_node2->add_child(tree->get_child(1)->get_child(1));
    cycled_node2->add_child(tree->get_child(1)->get_child(0));
    tree->get_child(1)->get_child(1)->add_child(cycled_node2);
    std::cout << node::node_id << std::endl;
    std::cout << *tree;


    return 0;
}