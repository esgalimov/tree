#include <iostream>
#include <vector>

namespace tree {
    template<typename KeyT>
    class rb_tree_t {

        enum class color_t {
            red, black,
        };

        struct node_t {
            KeyT key_;
            node_t *left_ = nullptr, *right_ = nullptr, *parent_ = nullptr;
            color_t color = red;

            node_t(key_t key) key_(key) : {}
        };

        std::vector<node_t> nodes_;
        using node_iter = std::vector<node_t>::pointer;

        node_iter root_ = nullptr;

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

            if (uncle->color_ == red) {
                new_node->parent_->color_ = black;
                uncle->color_ = black;

                node_iter grandad = get_grandad(new_node);

                if (grandad != root_) grandad->color_ = red;
            }
        }

        public:
            void insert(KeyT key) {
                nodes_.emplace_back(key);

                if (root_ != nullptr) {
                    node_iter curr = root_;

                    while (curr->left_ != nullptr && curr->right_ != nullptr) {
                        if (key > curr->key) {
                            if (curr->right_ == nullptr) {
                                curr->right_ = &nodes_.back();
                                break;
                            }
                            curr = curr->right_;
                        }
                        else {
                            if (curr->left_ == nullptr) {
                                curr->left_ = &nodes_.back();
                                break;
                            }
                            curr = curr->left_;
                        }
                    }
                    balance_tree(&nodes_.back());
                }
                else {
                    root_ = &nodes_.back();
                    root_->color_ = black;
                }
            }

    };
}
