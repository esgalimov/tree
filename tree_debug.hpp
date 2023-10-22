#include "tree.hpp"

using node_iter = typename std::list<tree::node_t<int>>::pointer;

void dump(tree::rb_tree_t<int> &tr);
void graphviz_init(tree::rb_tree_t<int> &tr);
void add_nodes(node_iter node);
void link_nodes_gr(node_iter node);
