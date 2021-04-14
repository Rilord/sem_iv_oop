#ifndef _SETLIB__SET
#define _SETLIB__SET

#include <initializer_list>
#include "tree.h"

template <class T>
class Set {

public:
    using valueType = T;
    using std::shared_ptr<set_node<T>> = ptr;
    using tree = tree<valueType>;


    explicit Set() = default;
    Set(std::initializer_list<T> items);

    ~Set() override = default;

    void insert(const valueType &value) {
        tree.insert(value);
    }
    void erase(const valueType &value);
    void clear() {
        impl.clear();
    }

    bool contains(const valueType &value) const;
    int size() const;
    bool isEmpty();


private:
    tree impl;

protected:
    std::pair<set_iterator<T>, bool> insert(

};


#endif // _SETLIB__SET
