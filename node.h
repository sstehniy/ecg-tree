#include <string>
#include <vector>
#include <map>

class node {
public:
    static int node_id;

    explicit node(const std::string &name = "");

    virtual ~node();

    std::string get_name() const;

    void set_name(const std::string &new_name);

    size_t get_nr_children() const;

    node *get_child(size_t i) const;

    void add_child(node *child);

    std::string name_;
    std::vector<node *> children;

    void print_with_cycles(std::ostream &str, int indentation,
                           std::map<std::string, bool> &visited) const;

    void print_iteratively(std::ostream &str) const;

    void print(std::ostream &str, int indentation) const;
};

node *create_complete_tree(int nr_child_nodes, int tree_depth);

extern std::ostream &operator<<(std::ostream &str, const node &n);
