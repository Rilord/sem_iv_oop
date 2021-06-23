#pragma once

#include "node.h"

namespace math_set {

    template<class T>
    node<T>::node(const T & data) : node<T>() { this->data = data; }

    template<class T>
    node<T>::node(std::shared_ptr<node<T>> &_node) : node<T>(_node.data) { this->next = _node.next; } 

    template<class T>
    void node<T>::set(const T &val) { data = val; } 

    template<class T>
    void node<T>::set_next(node<T> & _node) { 
        this->next = std::make_shared<node<T>>(_node); 
    }

    template<class T>
    void node<T>::set_next(const std::shared_ptr<node<T>> &node) { this->next = node; }

    template<class T>
    void node<T>::set_prev(node<T> & _node)  { this->prev = std::make_shared<node<T>>(_node); }

    template<class T>
    void node<T>::set_prev(const std::shared_ptr<node<T>> &node) { this->prev = node; }

    template<class T>
    const T &node<T>::get() const { return this->data; }

    template<class T>
    T &node<T>::val() { return this->data; }

    template<class T>
    std::shared_ptr<node<T>> node<T>::get_next() const {
        return next;
    }

    template<class T>
    std::shared_ptr<node<T>> node<T>::get_prev() const { return prev; }

    template<class T>
    bool node<T>::operator==(const std::shared_ptr<node<T>> &_node) const { 
        return this == _node; 
    }

    template<class T>
    bool node<T>::operator<(const std::shared_ptr<node<T>> &node) const { 
        return this != node; 
    }

    template<class T>
    bool node<T>::operator!=(const std::shared_ptr<node<T>> &node) const { 
        return this->data < node.lock()->data; 
    }

}
