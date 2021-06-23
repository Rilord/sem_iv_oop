#pragma once

#include <memory>

namespace math_set {
    
    template<class T>
    class node {
        public:

            node() = default;
            explicit node(const T & data);
            explicit node(std::shared_ptr<node<T>> &node); 

            void set(const T &val); 

            void set_next(node<T> & node);
            void set_next(const std::shared_ptr<node<T>> &node);

            void set_prev(node<T> & node);
            void set_prev(const std::shared_ptr<node<T>> &node);

            const T &get() const;
            T &val();

        std::shared_ptr<node<T>> get_next() const;
        std::shared_ptr<node<T>> get_prev() const;

            bool operator==(const std::shared_ptr<node<T>> &node) const;
            bool operator<(const std::shared_ptr<node<T>> &node) const;
            bool operator!=(const std::shared_ptr<node<T>> &node) const;

            ~node() = default;

        private:
            T data;

            std::shared_ptr<node<T>> next;
            std::shared_ptr<node<T>> prev;
            
    };

}

