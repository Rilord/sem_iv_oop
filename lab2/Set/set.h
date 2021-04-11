#ifndef _SETLIB__SET
#define _SETLIB__SET

#include <initializer_list>
#include "tree.h"

template <class T, class Compare=less<T>>
class Set {

public:
    typedef T valueType;
    explicit Set(const Compare& Pred);
    Set(std::initializer_list<T> items, const Compare & Pred);
    ~Set();

    void insert(const valueType &value) {
        tree.insert(value);
    }
    void erase(const valueType &value);
    void clear() {
        tree.clear();
    }

    bool contains(const valueType &value) const;
    int size() const;
    bool isEmpty();


private:
    typedef Tree<valueType, Compare> rbTree;
    rbTree tree;

};


#endif // _SETLIB__SET
