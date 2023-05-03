#include <node.h>
#include <iostream>
#include <sstream>
#include <map>
#include <stack>

int node::node_id = 0;

node::node(const std::string &name) {
    node_id++;
    if (name.empty()) {
        std::stringstream str_sm;
        str_sm << node_id;
        std::string node_id_str = str_sm.str();
        name_ = "node_" + node_id_str;
    } else {
        name_ = name;
    }
}

node::~node() {
//    std::cout << "enter ~node() of " << "\"" << name_ << "\"" << std::endl;
    for (node *child: children) {
        delete child;
    }
//    std::cout << "leave ~node() of " << "\"" << name_ << "\"" << std::endl;
}

// get_name() Methode
std::string node::get_name() const {
    return name_;
}

// set_name() Methode
void node::set_name(const std::string &new_name) {
    name_ = new_name;
}

// get_nr_children() Methode
size_t node::get_nr_children() const {
    return children.size();
}

// get_child() Methode
node *node::get_child(size_t i) const {
    if (i < children.size()) {
        return children[i];
    }
    return nullptr;
}

// add_child() Methode
void node::add_child(node *child) {
    children.push_back(child);
}


node *create_complete_tree(int nr_child_nodes, int tree_depth) {
    node *root = new node();
    if (tree_depth == 1) {
        return root;
    }

    for (int i = 0; i < nr_child_nodes; i++) {
        root->add_child(create_complete_tree(nr_child_nodes, tree_depth - 1));
    }
    return root;
}

void node::print(std::ostream &str, int indentation) const {
    for (int i = 0; i < indentation; ++i) {
        str << "    ";
    }
    str << name_ << "\n";

    for (const auto &child: children) {
        child->print(str, indentation + 1);
    }
}

void node::print_iteratively(std::ostream &str) const {
    std::stack<std::pair<node *, int>> stack;
    std::map<std::string, bool> visited;
    stack.emplace(const_cast<node *>(this), 0);

    while (!stack.empty()) {
        node *current_node = stack.top().first;
        int current_indentation = stack.top().second;
        stack.pop();

        for (int i = 0; i < current_indentation; ++i) {
            str << "    ";
        }
        if (visited[current_node->name_]) {
            str << current_node->name_ << " (cycle found from " << current_node->name_ << ")" << std::endl;
            continue;
        }
        str << current_node->name_ << std::endl;
        visited[current_node->name_] = true;
        for (int i = current_node->children.size() - 1; i >= 0; --i) {
            if (!visited[current_node->children[i]->name_]) {
                stack.push(std::make_pair(current_node->children[i], current_indentation + 1));
            } else {
                for (int j = 0; j < current_indentation + 1; ++j) {
                    str << "    ";
                }
                str << current_node->children[i]->name_ << " (cycle found from " << current_node->name_ << ")"
                    << std::endl;
            }
        }
    }
}

void node::print_with_cycles(std::ostream &str, int indentation, std::map<std::string, bool> &visited) const {

    for (int i = 0; i < indentation; ++i) {
        str << "    ";
    }
    str << name_ << std::endl;

    visited[name_] = true;
    for (const auto &child: children) {

        if (visited[child->name_]) {
            for (int i = 0; i < indentation + 1; ++i) {
                str << "    ";
            }
            str << child->name_ << " (cycle found from " << name_ << ")" << std::endl;
        } else {
            child->print_with_cycles(str, indentation + 1, visited);
        }
    }
}

std::ostream &operator<<(std::ostream &str, const node &n) {
//    n.print(str, 0);
//    std::map<std::string, bool> visited;
//    n.print_with_cycles(str, 0, visited);
    n.print_iteratively(str);
    return str;
}