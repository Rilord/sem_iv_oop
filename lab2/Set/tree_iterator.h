#ifndef SETLIB__TREE_ITERATOR
#define SETLIB__TREE_ITERATOR

#include <iterator>
#include <memory>
#include "nodeptr.h"

using std::iterator;
using std::bidirectional_iterator_tag;

template<typename T>
class TreeIterator: 
    public iterator<bidirectional_iterator_tag, typename T::valueType>
{
public:
    typedef std::shared_ptr<TreeNode<T>> tree_node_ptr;
    typedef typename T::valueType &      reference;
    explicit TreeIterator();
    TreeIterator(const tree_node_ptr node);
    virtual ~TreeIterator() = default;

    TreeIterator<T> &operator=(const TreeIterator<T> &listIter);

    TreeIterator<T> &next();
    TreeIterator<T> &prev();
    TreeIterator<T> &operator++();
    TreeIterator<T> operator++(int);
    TreeIterator<T> &operator--();
    TreeIterator<T> operator--(int);

    bool checkRange() const;

    bool operator==(const TreeIterator<T> &listIter) const;
    bool operator!=(const TreeIterator<T> &listIter) const;
    tree_node_ptr operator->(void);
    reference operator *(void);


protected:
    std::weak_ptr<TreeNode<T>> Iterator;

};

template<typename T>
TreeIterator<T>::TreeIterator() : Iterator() {
}

template<typename T>
TreeIterator<T>::TreeIterator(const tree_node_ptr node) : Iterator(node) {
}

template<typename T>
TreeIterator<T> &TreeIterator<T>::next() {
    if (this->currentPointer.expired())
    {

    }
    this->Iterator = this->Iterator->Successor();
    return (*this);
}

template<typename T>
TreeIterator<T> &TreeIterator<T>::prev() {
    if (this->currentPointer.expired())
    {

    }
    this->Iterator = this->Iterator->Predcessor();
    return (*this);
}

template<typename T>
TreeIterator<T> &TreeIterator<T>::operator++() {
    this->next();
    return *this;
}

template<typename T>
TreeIterator<T> TreeIterator<T>::operator++(int) {
    TreeIterator<T> tmp(*this);
    this->operator++();
    return tmp;
}

template<typename T>
TreeIterator<T> &TreeIterator<T>::operator--() {
    this->prev();
    return *this;
}

template<typename T>
TreeIterator<T> TreeIterator<T>::operator--(int) {
    TreeIterator<T> tmp(*this);
    this->operator--();
    return tmp;
}

#endif // SETLIB__TREE_ITERATOR
