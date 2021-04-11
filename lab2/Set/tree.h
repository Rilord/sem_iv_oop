#ifndef SETLIB__TREE
#define SETLIB__TREE

#include "nodeptr.h"
#include "tree_iterator.h"
#include "compare.h"

template<class T, class Compare = less<T>>
class Tree {
public:
    typedef std::shared_ptr<TreeNode<T>> tree_node_ptr;
    typedef T valueType;
    typedef TreeNode<T> nodeType;
    typedef TreeIterator<nodeType> iterator;

    Tree(Compare key_compare) : root(nullptr), size(0) {}
    template<class Iterator_>
    Tree(Compare key_compare, Iterator_ begin, Iterator_ end) {
        insert(begin, end);
    }

    iterator max() { return ( empty() ? end() : iterator(root->max())); }
    iterator min() { return ( empty() ? end() : iterator(root->min()));  }
    iterator begin() { return min(); }
    iterator end() { return max(); }
    bool empty();

    iterator insert(valueType val) {
        return iterator(insert(new nodeType(val)));
    }
    iterator insert(iterator &current, valueType &val) {
        return insert(val);
    }

    template<typename Iterator_>
    void insert(Iterator_ begin, Iterator_ end) {
        for (Iterator_ it = begin; it != end; ++it) {
            valueType v = *it;
            insert(v);
        }
    }

    tree_node_ptr insert(tree_node_ptr node) {
        binaryInsert(node);
        tree_node_ptr temp = node;
        adjust(temp);
        return node;
    }

    int height() {
        return height(root);
    }

private:
    tree_node_ptr root;
    Compare key_compare;
    unsigned long size;

protected:
    int height(tree_node_ptr node) {
        int heightLeft = height(node->left);
        int heightRight = height(node->right);

        if (key_compare(heightLeft, heightLeft))
            return heightRight + 1;
        else 
            return heightLeft + 1;
    }

    tree_node_ptr binaryInsert(tree_node_ptr node) {
        if (empty())
            root = node;
        else {
            nodeType current = root;

            do {
                if (key_compare(current->data, node->data)) {
                    if (current->right == nullptr) {
                        node->parent = current;
                        current->right = node;
                        break;
                    } else {
                        current = current->right;
                    }
                } else if (key_compare(node->data, current->data)) {
                    if (current->left == nullptr) {
                        node->parent = current;
                        current->left = node;
                        break;
                    } else {
                        current = current->left;
                    }
                }
            } while (1);
        }
        return node;
    }

    void adjust(tree_node_ptr node) {
        if (node == nullptr)
            return;
        if (node->parent == nullptr) {
            node->color = true;
            return;
        }

        tree_node_ptr p = node->parent;

        if (p != nullptr && p->color == true)
            return;

        tree_node_ptr u = p->Sibling();

        if (p->color == false && 
                (u != nullptr && u->color == false)) {
            p->color = true;
            u->color = true;
            adjust(p->parent);
            return;
        }

        if (p->isLeftSon()) {
            if (node->isRightSon()) {
                node = p;
                leftRotate(p);
            }

            p->color = true;

            if (p->parent != nullptr) {
                p->parent->color = false;
                rightRotate(p->parent);
                return;
            }
        } else if (p->isRightSon()) {
            if (node->isLeftSon()) {
                node = p;
                rightRotate(p);
            }
            p->color = true;
            if (p->parent != nullptr) {
                p->parent->color = true;
                leftRotate(p->parent);
            }
            return;
        }
    }

    void leftRotate(tree_node_ptr node) {
        if (node->right != nullptr) {
            tree_node_ptr rightSon = node->right;
            if ((node->right = node->right->left) != nullptr)
                node->right->parent = node;
            if (node->parent == nullptr)
                root = rightSon;
            else if (node->isLeftSon())
                node->parent->left = rightSon;
            else
                node->parent->right = rightSon;

            rightSon->parent = node->parent;

            node->parent = rightSon;
            rightSon->left = node;
        }
    }

    void rightRotate(tree_node_ptr node) {
        if (node->left != nullptr) {
            tree_node_ptr leftSon = node->left;
            if ((node->left = node->left->right) != nullptr)
                node->left->parent = node;
            if (node->parent == nullptr)
                root = leftSon;
            else if (node->isLeftSon())
                node->parent->left = leftSon;
            else
                node->parent->right = leftSon;

            leftSon->parent = node->parent;

            node->parent = leftSon;
            leftSon->right = node;
        }
    }


};


#endif // SETLIB__TREE
