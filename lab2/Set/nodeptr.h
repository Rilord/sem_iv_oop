#ifndef _SETLIB_NODE_PTR
#define _SETLIB_NODE_PTR

#include <memory>
#include "compare.h"

template<class T>
class TreeNode {
public: 
    typedef std::shared_ptr<TreeNode<T>> tree_node_ptr;
    typedef T valueType;
    TreeNode(void);
    explicit TreeNode(const T);
    TreeNode(const T _data, const tree_node_ptr _parent, bool _color);
    TreeNode(const T _data, const tree_node_ptr _parent); 

    virtual ~TreeNode();

    void setData(const T data);

    T getData() const;
    T &getPtrToData();
    bool getNodeColor();

    void setLeft(const tree_node_ptr left);
    void setRight(const tree_node_ptr right);
    void setNodeColor(const bool color);


    bool operator==(const TreeNode<T> &other) const;
    bool operator!=(const TreeNode<T> &other) const;
    bool operator< (const TreeNode<T> &other) const;
    bool operator> (const TreeNode<T> &other) const;
    bool operator<=(const TreeNode<T> &other) const;
    bool operator>=(const TreeNode<T> &other) const;

    bool IsLeftSon(void);
    bool IsRightSon(void);


    tree_node_ptr Max(void);
    tree_node_ptr Min(void);

    tree_node_ptr Successor(void);
    tree_node_ptr Sibling(void);
    tree_node_ptr Predcessor(void);


private:
        T data;
        tree_node_ptr parent, left, right;
        bool color; // black - 1, red - 0
};

template<class T> 
TreeNode<T>::TreeNode() : parent(nullptr), left(nullptr), right(nullptr), color(true) {}

template<class T>
TreeNode<T>::TreeNode(const T _data, const tree_node_ptr _parent, bool _color) : 
    data(_data), parent(_parent), color(_color), left(nullptr), right(nullptr) {}

template<class T>
TreeNode<T>::TreeNode(const T _data, const tree_node_ptr _parent) : 
    data(_data), parent(_parent), color(false), left(nullptr), right(nullptr) {}

template<class T> 
TreeNode<T>::TreeNode(const T _data) : data(_data), parent(nullptr), left(nullptr), right(nullptr), color(false) {}


template<class T>
TreeNode<T>::~TreeNode() {
    this->data = 0;
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

template<class T>
T TreeNode<T>::getData() const {
    return this->data;
}

template<class T>
T &TreeNode<T>::getPtrToData() {
    return this->data;
}

template<class T>
void TreeNode<T>::setLeft(const tree_node_ptr left) {
    this->left = left;
}

template<class T>
void TreeNode<T>::setRight(const tree_node_ptr right) {
    this->right = right;
}

template<class T>
std::shared_ptr<TreeNode<T>> TreeNode<T>::Max() {
    return (this.right == nullptr) ? this : this.right.Max();
}

template<class T>
std::shared_ptr<TreeNode<T>> TreeNode<T>::Min() {
    return (this.left == nullptr) ? this : this.left.Min();
}

template<class T>
bool TreeNode<T>::IsLeftSon() {
    return (parent != nullptr) && (parent->left == this);
}

template<class T>
bool TreeNode<T>::IsRightSon() {
    return (parent != nullptr) && (parent->right == this);
}

template<class T>
std::shared_ptr<TreeNode<T>> TreeNode<T>::Successor() {
    if (this.right != nullptr)
        return this.right.Min(); 

    if (IsLeftSon())
        return parent;

    std::shared_ptr<TreeNode<T>> succ = this;

}
#endif // _SETLIB_NODE_PTR
