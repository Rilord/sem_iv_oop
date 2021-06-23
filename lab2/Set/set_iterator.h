#pragma once
#include <iterator>

#include <node.h>

namespace math_set {
    template<class T>
    class set_iterator : public std::iterator<std::input_iterator_tag, T>{
        set_iterator(); 
        explicit set_iterator(const std::shared_ptr<node<T>> &node);
        set_iterator(const set_iterator<T> &it);

        ~set_iterator() = default;

        virtual void next();
        virtual void prev();

        const T *operator->() const;
        const T &operator*() const;

        explicit operator bool() const;

        set_iterator<T> &operator=(const set_iterator<T> &it);

        virtual set_iterator<T> &operator++();
        virtual const set_iterator<T> operator++(int);
        virtual set_iterator<T> &operator--();
        virtual const set_iterator<T> operator--(int);

        bool operator!=(const set_iterator<T> &it) const;
        bool operator==(const set_iterator<T> &it) const;

        template<class Set>
        friend class set;

        protected:
            virtual void set_current(node<T> &node);
            virtual node<T> &get_current();
            virtual const node<T> &get_current() const;

        private:
            std::weak_ptr<node<T>> current;

    };

}

