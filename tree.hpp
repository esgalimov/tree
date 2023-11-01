#pragma once

#include <fstream>
#include <list>

namespace tree {
    template<typename KeyT, typename Comp>
    class rb_tree_t {
        enum color_t { red, black };

        struct node_t {
            KeyT key_;
            node_t *left_, *right_, *parent_ = nullptr;
            color_t color_;
            int subtr_sz_;

            node_t(KeyT key, color_t color = black, node_t* left = nullptr, node_t* right = nullptr, int subtr_sz = 0) :
                key_(key), color_(color), left_(left), right_(right), subtr_sz_(subtr_sz) {};
        };

        std::list<node_t> nodes_;
        using node_iter = typename std::list<node_t>::pointer;

        node_iter nil_ = nullptr, root_ = nullptr;

        node_iter get_brother(node_iter node) const {
            if (node == node->parent_->left_)
                return node->parent_->right;
            else
                return node->parent_->left;
        }

        node_iter get_uncle(node_iter node) const {
            if (node->parent_ == node->parent_->parent_->left_)
                return node->parent_->parent_->right_;
            else
                return node->parent_->parent_->left_;
        }

        node_iter get_grandad(node_iter node) const {
            return node->parent_->parent_;
        }

        void balance_tree(node_iter new_node) {
            if (new_node->parent_->color_ == black) return;

            node_iter uncle = get_uncle(new_node);

            if (uncle == nil_ || uncle->color_ == black) {
                if (new_node == new_node->parent_->right_ &&
                    new_node->parent_ == get_grandad(new_node)->left_) {
                    left_rotate(new_node->parent_);
                }
                else if (new_node == new_node->parent_->left_ &&
                         new_node->parent_ == get_grandad(new_node)->right_) {
                    right_rotate(new_node->parent_);
                }
                if (new_node == new_node->parent_->left_ &&
                    new_node->parent_ == get_grandad(new_node)->left_) {
                    new_node->parent_->color_ = black;
                    get_grandad(new_node)->color_ = red;
                    right_rotate(get_grandad(new_node));
                }
                else if (new_node == new_node->parent_->right_ &&
                         new_node->parent_ == get_grandad(new_node)->right_) {
                    new_node->parent_->color_ = black;
                    get_grandad(new_node)->color_ = red;
                    left_rotate(get_grandad(new_node));
                }
            }
            else {
                new_node->parent_->color_ = black;
                uncle->color_ = black;

                node_iter grandad = get_grandad(new_node);

                if (grandad != root_) {
                    grandad->color_ = red;
                    balance_tree(grandad);
                }
            }
        }

        void left_rotate(node_iter node) {
            swap_nodes(node, node->right_);

            node_iter saved_left = node->left_;

            node->subtr_sz_ = node->right_->subtr_sz_;

            node->right_->subtr_sz_ = node->left_->subtr_sz_ + node->right_->left_->subtr_sz_ + 1;

            node->left_ = node->right_;

            node->right_ = node->left_->right_;
            node->right_->parent_ = node;

            node->left_->right_ = node->left_->left_;

            node->left_->left_ = saved_left;
            saved_left->parent_ = node->left_;
        }

        void right_rotate(node_iter node) {
            swap_nodes(node, node->left_);

            node_iter saved_right = node->right_;

            node->subtr_sz_ = node->left_->subtr_sz_;

            node->left_->subtr_sz_ = node->right_->subtr_sz_ + node->left_->right_->subtr_sz_ + 1;

            node->right_ = node->left_;

            node->left_ = node->right_->left_;
            node->left_->parent_ = node;

            node->right_->left_ = node->right_->right_;

            node->right_->right_ = saved_right;
            saved_right->parent_ = node->right_;
        }

        void swap_nodes(node_iter nd1, node_iter nd2) {
            KeyT key = nd1->key_;
            nd1->key_ = nd2->key_;
            nd2->key_ = key;

            color_t color = nd1->color_;
            nd1->color_ = nd2->color_;
            nd2->color_ = color;

            int subtr_sz = nd1->subtr_sz_;
            nd1->subtr_sz_ = nd2->subtr_sz_;
            nd2->subtr_sz_ = subtr_sz;
        }

        void add_nodes(node_iter node, std::ofstream &stream);
        void link_nodes_gr(node_iter node, std::ofstream &stream);

        int dump_cnt = 0;

        public:
            rb_tree_t() {
                nodes_.emplace_back(0);
                nil_ = &nodes_.back();
                root_ = nil_;
            }

            void insert(KeyT key) {
                nodes_.emplace_back(key, red, nil_, nil_, 1);

                if (root_ != nil_) {
                    node_iter curr = root_;

                    while (curr != nil_) {
                        if (Comp()(key, curr->key_)) {
                            curr->subtr_sz_++;
                            if (curr->left_ == nil_) {
                                curr->left_ = &nodes_.back();
                                curr->left_->parent_ = curr;
                                break;
                            }
                            curr = curr->left_;
                        }
                        else if (key == curr->key_){
                            curr = curr->parent_;
                            while (curr != nullptr) {
                                curr->subtr_sz_--;
                                curr = curr->parent_;
                            }
                            return;
                        }
                        else {
                            curr->subtr_sz_++;
                            if (curr->right_ == nil_) {
                                curr->right_ = &nodes_.back();
                                curr->right_->parent_ = curr;
                                break;
                            }
                            curr = curr->right_;
                        }
                    }
                    balance_tree(&nodes_.back());
                }
                else {
                    root_ = &nodes_.back();
                    root_->color_ = black;
                }
            }

            node_iter lower_bound(KeyT key) const {
                node_iter curr = root_;

                while (curr != nil_) {
                    if (curr->key_ > key) {
                        if (curr->left_ != nil_ && curr->left_->key_ < key) return curr;
                        curr = curr->left_;
                    }
                    else if (curr->key_ < key) {
                        if (curr->right_ != nil_ && curr->right_->key_ > key) return curr;
                        curr = curr->right_;
                    }
                    else return curr;
                }
                return curr;
            }

            node_iter upper_bound(KeyT key) const {
                node_iter curr = root_;

                while (curr != nil_) {
                    if (curr->key_ > key) {
                        if (curr->left_ != nil_ && curr->left_->key_ < key ||
                            curr->left_ == nil_) return curr;
                        curr = curr->left_;
                    }
                    else if (curr->key_ < key) {
                        if (curr->right_ != nil_ && curr->right_->key_ > key)
                            curr = curr->right_;
                    }
                }
                return curr;
            }

            int distance(node_iter first, node_iter second) const {
                if (second->parent_ == first)
                    return second->left_->subtr_sz_ - first->left_->subtr_sz_ + 2;
                else if (first->parent_ == second)
                    return first->right_->subtr_sz_ + 1;
                else
                    return second->left_->subtr_sz_ + first->right_->subtr_sz_ + 2;
            }

            void dump();
    };


    template<typename KeyT, typename Comp>
    void rb_tree_t<KeyT, Comp>::dump() {
        std::ofstream out;

        out.open("graphviz.dot");

        if (!out.is_open()) {
            std::cerr << "Can't open graphviz.dot" << std::endl;
            return;
        }

        out << "digraph\n{\n";
        out << "    node_info[shape = record, label = \"{root = " << root_ << "}\"];\n\n";

        if (root_ != nullptr)
            out << "    node_info->node_" << root_ << " [color = \"green\"];\n";

        add_nodes(root_, out);
        link_nodes_gr(root_, out);

        out << "\n}";
        out.close();

        std::string cmd = "dot ./graphviz.dot -Tpng -o ./tree_dump", cmd_end = ".png";

        cmd.append(std::to_string(dump_cnt++)).append(cmd_end);
        std::system(cmd.data());
    }

    template<typename KeyT, typename Comp>
    void rb_tree_t<KeyT, Comp>::add_nodes(node_iter node, std::ofstream &stream)
    {
        if (node == nil_) return;

        stream << "    node_" << node << "[shape = Mrecord, label = \"{{" << node <<
                "} | {parent =  " << node->parent_ << "} | {key = " << node->key_ << "} | {subtr_sz = " << node->subtr_sz_ << "} | {";

        if (node->left_ == nil_) stream << "nil | ";
        else stream  << node->left_ << "| ";

        if (node->right_ == nil_) stream << "nil";
        else stream << node->right_;

        stream <<"}}\",\n style=\"filled\", fillcolor=";

        if (node->color_ == black) {
            stream << "\"grey\"];\n";
        }
        else {
            stream << "\"red\"];\n";
        }

        add_nodes(node->left_, stream);
        add_nodes(node->right_, stream);
    }

    template<typename KeyT, typename Comp>
    void rb_tree_t<KeyT, Comp>::link_nodes_gr(node_iter node, std::ofstream &stream)
    {
        if (node == nil_) return;

        if (node->left_ != nil_)
        {
            stream << "    node_" << node << "->node_" << node->left_ << "\n";
            link_nodes_gr(node->left_, stream);
        }
        if (node->right_ != nil_)
        {
            stream << "    node_" << node << "->node_" << node->right_ << "\n";
            link_nodes_gr(node->right_, stream);
        }
    }
}


