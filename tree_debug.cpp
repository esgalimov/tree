#include "tree_debug.hpp"

#include <fstream>
#include <cstdlib>
#include <string>

std::ofstream out;
int dump_cnt = 0;

using namespace tree;
using node_iter = typename std::list<tree::node_t<int>>::pointer;

void dump(rb_tree_t<int> &tr) {
    out.open("graphviz.dot");

    if (!out.is_open()) { exit(1); }

    graphviz_init(tr);
    add_nodes(tr.get_root());
    link_nodes_gr(tr.get_root());

    out << "\n}";
    out.close();


    std::string s1 = "dot ./graphviz.dot -Tpng -o ./tree_dump";
    std::string s2 = ".png";

    std::string cmd;
    cmd.append(s1).append(std::to_string(dump_cnt)).append(s2);
    std::system(cmd.data());
    dump_cnt++;
}

void graphviz_init(rb_tree_t<int> &tr)
{
    auto root = tr.get_root();

    out << "digraph\n{\n";
    out << "    node_info[shape = record, label = \"{root = " << root << "}\"];\n\n";

    if (root != nullptr)
        out << "    node_info->node_" << root << " [color = \"green\"];\n";
}

void add_nodes(node_iter node)
{
    if (node == nullptr) return;


    out << "    node_" << node << "[shape = Mrecord, label = \"{{" << node <<
            "} | {parent =  " << node->parent_ << "} | {key = " << node->key_ << "} | {" << node->left_ << "| "<< node->right_ <<"}}\",\n\
            style=\"filled\", fillcolor=";

    if (node->color_ == black) {
        out << "\"grey\"];\n";
    }
    else {
        out << "\"red\"];\n";
    }

    add_nodes(node->left_);
    add_nodes(node->right_);
}

void link_nodes_gr(node_iter node)
{
    if (node == nullptr) return;

    if (node->left_ != nullptr)
    {
        out << "    node_" << node << "->node_" << node->left_ << "\n";
        link_nodes_gr(node->left_);
    }
    if (node->right_ != nullptr)
    {
        out << "    node_" << node << "->node_" << node->right_ << "\n";
        link_nodes_gr(node->right_);
    }
}
