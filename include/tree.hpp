#pragma once

#include <fstream>
#include <functional>
#include <vector>
#include <stack>

namespace tree {
    template<typename KeyT = int, typename Comp = std::less<int> >
    class rb_tree_t final{
        enum color_t { red, black };

        struct node_t {
            KeyT key_;
            node_t *left_, *right_, *parent_ = nullptr;
            color_t color_;
            int subtr_sz_;

            node_t(KeyT key, color_t color = black, node_t* left = nullptr, node_t* right = nullptr,
                   node_t* parent = nullptr, int subtr_sz = 0) :
                key_(key), color_(color), left_(left), right_(right), parent_(parent), subtr_sz_(subtr_sz) {};
        };

        std::vector<node_t*> nodes_;
        using node_iter = node_t*;

        node_iter nil_ = nullptr, root_ = nullptr;

        int dump_cnt = 0;

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

        void parent_rotate(node_iter new_node) {
            if (new_node == new_node->parent_->right_ &&
                new_node->parent_ == get_grandad(new_node)->left_) {
                left_rotate(new_node->parent_);
            }
            else if (new_node == new_node->parent_->left_ &&
                     new_node->parent_ == get_grandad(new_node)->right_) {
                right_rotate(new_node->parent_);
            }
        }

        void grandad_rotate(node_iter new_node) {
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

        void balance(node_iter new_node) {
            if (new_node->parent_->color_ == black) return;

            node_iter uncle = get_uncle(new_node);

            if (uncle == nil_ || uncle->color_ == black) {
                parent_rotate(new_node);
                grandad_rotate(new_node);
            }
            else {
                new_node->parent_->color_ = black;
                uncle->color_ = black;

                node_iter grandad = get_grandad(new_node);

                if (grandad != root_) {
                    grandad->color_ = red;
                    balance(grandad);
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

        void clone_left(node_iter clone, node_iter orig) {
            clone->left_ = new node_t{orig->left_->key_, orig->left_->color_,
                                              nil_, nil_, clone, orig->left_->subtr_sz_};
            nodes_.push_back(clone->left_);
        }

        void clone_right(node_iter clone, node_iter orig) {
            clone->right_ = new node_t{orig->right_->key_, orig->right_->color_,
                                               nil_, nil_, clone, orig->right_->subtr_sz_};
            nodes_.push_back(clone->right_);
        }

        void copy_tree(const rb_tree_t& tr) {
            if (tr.root_ == tr.nil_) return;

            root_ = new node_t{tr.root_->key_, tr.root_->color_,
                                nil_, nil_, nullptr, tr.root_->subtr_sz_};
            nodes_.push_back(root_);

            node_iter clone = root_,
                      orig  = tr.root_;

            while (orig != tr.nil_ && orig != nullptr) {
                if (orig->left_ != tr.nil_ && clone->left_ == nil_) {
                    clone_left(clone, orig);

                    orig = orig->left_;
                    clone = clone->left_;
                }
                else if (orig->right_ != tr.nil_ && clone->right_ == nil_) {
                    clone_right(clone, orig);

                    orig = orig->right_;
                    clone = clone->right_;
                }
                else {
                    orig = orig->parent_;
                    clone = clone->parent_;
                }
            }
        }

        void add_nodes(std::ofstream &stream) const;
        void link_nodes_gr(std::ofstream &stream) const;

        void insert_leaf(KeyT key) {
            node_iter curr = root_;

            while (curr != nil_) {
                if (Comp()(key, curr->key_)) {
                    curr->subtr_sz_++;
                    if (curr->left_ == nil_) {
                        curr->left_ = new node_t{key, red, nil_, nil_, curr, 1};
                        nodes_.push_back(curr->left_);
                        balance(curr->left_);
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
                        curr->right_ = new node_t{key, red, nil_, nil_, curr, 1};
                        nodes_.push_back(curr->right_);
                        balance(curr->right_);
                        break;
                    }
                    curr = curr->right_;
                }
            }
        }

        void insert_root(KeyT key) {
            root_ = new node_t{key, black, nil_, nil_, nullptr, 1};
            nodes_.push_back(root_);
        }

        int count_parents_left_sizes(node_iter first) const {
            node_iter curr = first;
            int lower_cnt = 0;

            while (curr != root_) {
                if (curr == curr->parent_->right_)
                    lower_cnt += curr->parent_->left_->subtr_sz_ + 1;
                curr = curr->parent_;
            }
            return lower_cnt;
        }

        int count_parents_right_sizes(node_iter second) const {
            node_iter curr = second;
            int upper_cnt = 0;

            while (curr != root_) {
                if (curr == curr->parent_->left_)
                    upper_cnt += curr->parent_->right_->subtr_sz_ + 1;
                curr = curr->parent_;
            }
            return upper_cnt;
        }

        public:
            rb_tree_t() : nil_(new node_t{0}), root_(nil_) {
                nodes_.push_back(nil_);
            }

            void insert(KeyT key) {
                if (root_ != nil_) insert_leaf(key);
                else               insert_root(key);
            }

            node_iter lower_bound(KeyT key) const {
                node_iter curr = root_, answer = nil_;

                while (curr != nil_) {
                    if (Comp()(key, curr->key_)) {
                        answer = curr;
                        if (curr->left_ == nil_) return answer;
                        curr = curr->left_;
                    }
                    else if (key == curr->key_) return curr;

                    else curr = curr->right_;
                }
                return answer;
            }

            node_iter upper_bound(KeyT key) const {
                node_iter curr = root_, answer = nil_;

                while (curr != nil_) {
                    if (Comp()(key, curr->key_)) {
                        answer = curr;
                        if (curr->left_ == nil_) return answer;
                        curr = curr->left_;
                    }
                    else curr = curr->right_;

                }
                return answer;
            }

            int distance(node_iter first, node_iter second) const {
                if (first == nil_ && second == nil_) return 0;

                int lower_cnt = 0, upper_cnt = 0;

                if (first != nil_)
                    lower_cnt = first->left_->subtr_sz_ + count_parents_left_sizes(first);

                if (second != nil_)
                    upper_cnt = second->right_->subtr_sz_ + 1 + count_parents_right_sizes(second);

                return root_->subtr_sz_ - lower_cnt - upper_cnt;

            }

            void dump();

            // BIG FIVE
            ~rb_tree_t() {
                for (auto *node : nodes_) delete node;
            }

            rb_tree_t(const rb_tree_t& tr) : rb_tree_t() {
                copy_tree(tr);
            }

            rb_tree_t(rb_tree_t&& tr) noexcept :
                nodes_(std::move(tr.nodes_)), nil_(tr.nil_), root_(tr.root_) {}

            rb_tree_t& operator=(const rb_tree_t& tr) {
                if (this == &tr) return *this;

                nodes_.erase(std::next(nodes_.begin()), nodes_.end());
                copy_tree(tr);
                return *this;
            }

            rb_tree_t& operator=(rb_tree_t&& tr) noexcept {
                if (this == &tr) return *this;

                nodes_ = std::move(tr.nodes_);
                nil_ = tr.nil_;
                root_ = tr.root_;

                return *this;
            }
    };


    constexpr int MAX_NODES_IN_DUMP = 512;

    template<typename KeyT, typename Comp>
    void rb_tree_t<KeyT, Comp>::dump() {
        std::ofstream out;

        if (root_->subtr_sz_ > MAX_NODES_IN_DUMP) {
            std::cerr << "There are too much nodes to dump (max = " <<  MAX_NODES_IN_DUMP << ")" << std::endl;
            return;
        }

        out.open("../tmp/graphviz.dot");

        if (!out.is_open()) {
            std::cerr << "Can't open graphviz.dot" << std::endl;
            return;
        }

        out << "digraph\n{\n";
        out << "    node_info[shape = record, label = \"{root = " << root_ << "}\"];\n\n";

        if (root_ != nullptr)
            out << "    node_info->node_" << root_ << " [color = \"green\"];\n";

        add_nodes(out);
        link_nodes_gr(out);

        out << "\n}";
        out.close();

        std::string cmd = "dot ../tmp/graphviz.dot -Tpng -o ../dumps/tree_dump", cmd_end = ".png";

        cmd.append(std::to_string(dump_cnt++)).append(cmd_end);
        std::system(cmd.data());
    }

    template<typename KeyT, typename Comp>
    void rb_tree_t<KeyT, Comp>::add_nodes(std::ofstream &stream) const
    {
        std::stack<node_iter> nd_stk;
        nd_stk.push(root_);

        node_iter node;

        while (!nd_stk.empty()) {
            node = nd_stk.top();
            nd_stk.pop();

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

            if (node->right_ != nil_) nd_stk.push(node->right_);
            if (node->left_ != nil_)  nd_stk.push(node->left_);
        }
    }

    template<typename KeyT, typename Comp>
    void rb_tree_t<KeyT, Comp>::link_nodes_gr(std::ofstream &stream) const
    {
        std::stack<node_iter> nd_stk;
        nd_stk.push(root_);

        node_iter node;

        while (!nd_stk.empty()) {
            node = nd_stk.top();
            nd_stk.pop();

            if (node->left_ != nil_) {
                stream << "    node_" << node << "->node_" << node->left_ << "\n";
                nd_stk.push(node->left_);
            }

            if (node->right_ != nil_) {
                stream << "    node_" << node << "->node_" << node->right_ << "\n";
                nd_stk.push(node->right_);
            }
        }
    }
}


