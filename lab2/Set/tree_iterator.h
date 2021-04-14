#ifndef SETLIB__TREE_ITERATOR
#define SETLIB__TREE_ITERATOR

#include <iterator>
#include <memory>
#include "nodeptr.h"

using std::iterator;
using std::bidirectional_iterator_tag;

template<typename T>
class tree_iterator: 
    public iterator<bidirectional_iterator_tag, typename T::valuetype>
{

    virtual 
public:
    using ptr =  std::shared_ptr<tree_node<T>>;
    using reference = typename T::valuetype &;
    explicit tree_iterator();
    tree_iterator(const ptr node);
    virtual ~tree_iterator() = default;

    tree_iterator<T> &operator=(const tree_iterator<T> &listiter);

    tree_iterator<T> &next();
    tree_iterator<T> &prev();
    tree_iterator<T> &operator++();
    tree_iterator<T> operator++(int);
    tree_iterator<T> &operator--();
    tree_iterator<T> operator--(int);

    bool checkrange() const;

    bool operator==(const tree_iterator<T> &listiter) const;
    bool operator!=(const tree_iterator<T> &listiter) const;
    ptr operator->(void);
    reference operator *(void);
    friend class set;

protected:
    std::weak_ptr<tree_node<T>> iterator;

};
#endif // setlib__tree_iterator
