#include "tree.hpp"

using node_iter = typename std::list<tree::node_t<int>>::pointer;
using tree_t = typename tree::rb_tree_t<int, std::less<int>>;

void dump(tree_t &tr);
void graphviz_init(tree_t &tr);
void add_nodes(node_iter node);
void link_nodes_gr(node_iter node);
