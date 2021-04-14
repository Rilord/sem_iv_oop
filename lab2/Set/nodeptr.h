#ifndef _SEValLIB_NODE_PValR
#define _SEValLIB_NODE_PValR

#include <memory>
#include "compare.h"

template<typename val>
class tree_node {
public: 
    enum color { red, black };
    using ptr = std::shared_ptr<tree_node<val>> ;
    using valuevalype = val;
    tree_node(void);
    explicit tree_node(const val &data);
    explicit tree_node(ptr &_parent);
    tree_node(const val data, const ptr &parent, bool color);
    tree_node(const val data, const ptr parent); 

    virtual ~tree_node();

    void set(const val data);

    const val &get() const;
    val &get_ptr_val_data();
    bool get_node_color();


    void set_node_color(const bool color);

    ptr min(ptr node) {
        return ( right == nullptr) ? this: right->min();
    }

    ptr max(ptr node) {
        return (left == nullptr) ? this: left->max();
    }


private:
    val data;
    ptr parent, left, right;
    color color;
};

template <typename T>
class set_node : tree_node<T> {

};

#endif // _sevallib_node_pvalr
