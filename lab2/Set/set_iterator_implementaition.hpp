#pragma once
#include "exceptions.h"
#include "set_iterator.h"


namespace math_set {


        template<class T>
        set_iterator<T>::set_iterator() {
           this->current.lock() = nullptr; 
        }
        template<class T>
        set_iterator<T>::set_iterator(const std::shared_ptr<node<T>> 
                &node) {
            this->current = node;
        }

        template<class T>
        set_iterator<T>::set_iterator(const set_iterator<T> &it) {
            this->current = it.current.lock();
        }


        template<class T>
        void set_iterator<T>::next() {
            if (this->current.expired())
            {
                throw wrong_iterator_exception(__FILE__, 
                        typeid(*this).name(),
                        __LINE__, time(nullptr),
                        "failed to get pointer");

            }
            this->current = get_current().get_next();
        }

        template<class T>
            void set_iterator<T>::prev() {
                this->current = get_current().get_prev();
            }

        template<class T>
            const T *set_iterator<T>::operator->() const {

                if (this->current.expired()) {
                    throw wrong_iterator_exception(__FILE__, 
                            typeid(*this).name(),
                            __LINE__, time(nullptr),
                            "failed to get pointer");
                }
                return get_current().get();
            }

        template<class T>
            const T &set_iterator<T>::operator*() const {
                if (this->current.expired()) {
                    throw wrong_iterator_exception(__FILE__, 
                            typeid(*this).name(), __LINE__, time(nullptr), "failed to get reference");
                }
                return get_current().value();
            }

        template<class T>
            set_iterator<T>::operator bool() const {
                return this->current.lock() == nullptr;
            }

        template<class T>
            set_iterator<T> &set_iterator<T>::operator=(const set_iterator<T> &it) {
                this->current = it.current.lock();
                return *this;
            }

        template<class T>
            set_iterator<T> &set_iterator<T>::operator++() {
                this->next();
                return *this;
            }

        template<class T>
            const set_iterator<T> set_iterator<T>::operator++(int) {
                auto old = *this;
                this->next();

                return old;
            }

        template<class T>
            set_iterator<T> & set_iterator<T>::operator--(){
                this->prev();
                return *this;
            }

        template<class T>
            const set_iterator<T> set_iterator<T>::operator--(int){
                auto old = *this;
                this->prev();

                return old;

            }

        template<class T>
            bool set_iterator<T>::operator!=(const set_iterator<T> &it) const{
                return this->current.lock() != it.current.lock();
            }

        template<class T>
            bool set_iterator<T>::operator==(const set_iterator<T> &it) const {
                return this->current.lock() == it.current.lock();
            }

        template<class T>
            void set_iterator<T>::set_current(node<T> 
                    &node) {
                this->set_current(node);

            }
        template<class T>
            const node<T> &set_iterator<T>::get_current() const {
                if (this->current.expired()) {
                    throw wrong_iterator_exception(__FILE__, 
                            typeid(*this).name(), __LINE__, time(nullptr), "failed to get pointer");
                }
                return *this->current.lock();
            }

        template<class T>
            node<T> &set_iterator<T>::get_current() {
                if (this->current.expired()) {
                    throw wrong_iterator_exception(__FILE__, 
                            typeid(*this).name(), __LINE__, time(nullptr), "failed to get pointer");
                }
                return *this->current.lock();
            }
}

