#pragma once
#include "set.h"
#include "set_iterator.h"
#include "exceptions.h"
#include <memory>
#include <new>
template<class T>
using sh_ptr = std::shared_ptr<T>;

namespace math_set {

    // LVALUE Constructor

    template<class T>
        set<T>::set(const set<T> &list) : set() {

            for (auto i = list.cbegin(); list.cend() != i; i++) {
                sh_ptr<node<T>> tmp_node = nullptr;

                try {
                    tmp_node = sh_ptr<node<T>>(new node<T>);

                } catch (std::bad_alloc &err) {
                    throw wrong_alloc_exception(__FILE__, 
                            typeid(*this).name(), __LINE__, time(nullptr), "wrong alloc");
                }

                tmp_node->set(*i);
                insert(tmp_node);
            }
        }

    // RVAL Constructor

    template<class T>
    set<T>::set(set<T> &&list) noexcept {
        size = list.size;
        head = list.head;
    }

    // {} Constructor

    template<class T>
    set<T>::set(std::initializer_list<T> elems) : set() {
        for (auto &elem: elems) {
            sh_ptr<node<T>> tmp = nullptr; 

                try {
                    tmp = sh_ptr<node<T>>(new node<T>);

                } catch (std::bad_alloc &err) {
                    throw wrong_alloc_exception(__FILE__, typeid(*this).name(), __LINE__, time(nullptr), "wrong alloc");
                }

            tmp->set(elem);
            insert(tmp);
        }
    }

    // Destructor

    template<class T>
    math_set::set<T>::~set() {
        this->clear();
    }

    // Insertion by T value 


    template<typename T>
    set<T> set<T>::update(const T &value) {
        set<int> res(*this);

        res.add(value);

        return res;
    }

    template<typename T>
    set<T> set<T>::update(T &&value) {
        set<int> res(*this);

        res.add(value);

        return res;
    }

    template<typename T>
    set<T> set<T>::update(std::initializer_list<T> ilist) {
        set<int> res(*this);

        for (auto &el : ilist)
            res.add(el);

        return res;
    }

    template<typename T>
    set<T> set<T>::update(T *ilist, size_t len) noexcept(false) {
        set<int> res(*this);

        for (size_t i = 0; i < len; ++i)
            res.add(ilist[i]);

        return res;
    }

    // Intersection overloading

    template<class T>
        set<T> set<T>::intersection(const set<T> &set) {
            return *this & set;
        }
    template<class T>
        set<T> set<T>::intersection(const T &data) {
            return *this & data;
        }

    // Combine overloading

    template<class T>
        set<T> set<T>::combine(const set<T> &set) {
            return *this | set;
        }

    template<class T>
        set<T> set<T>::combine(const T& data) {
            return *this | data;
        }

    // Diff overloading

    template<class T>
        set<T> set<T>::diff(const set<T> &set) {
            return *this - set;
        }

    template<class T>

    set<T> set<T>::diff(std::initializer_list<T> init_list) {
        set<T> tmp = set<T>(init_list);
        return *this - tmp;
    }


    template<class T>
    set<T> set<T>::diff(const T &data) {
        return *this - data;
    }

    // Symmetrical diff overloading

    template<class T>
    set<T> set<T>::sym_diff(const set<T> &set) {
        return *this ^ set;
    }

    template<class T>
    set<T> set<T>::sym_diff(const T &data) {
        return *this ^ data;
    }

    // Erase 

    template<class T>
    void set<T>::erase(const T &val) {

        if (auto t = find(val))
            remove(t);
    }

    template<class T>
    void set<T>::erase(set_iterator<T> where) {
        if (!size)
            return;

        if (!where) {

            throw wrong_iterator_exception(__FILE__, typeid(*this).name(), __LINE__, time(nullptr), "iterator error at erase");
        }

        auto t = std::make_shared<node<T>>(where.get_current());

        if (head->get() == t->get())
            head = t->get_next();

        auto r = t->get_next();
        t->remove();

        --size();
    }

//    template<class T>
//        void set<T>::erase(set_iterator<T>start, set_iterator<T> end){
//            if (!size)
//                return;
//
//            if (!(start &&end))
//                return;
//
//        }

    template<class T>
    void set<T>::clear() {
        while (head) {
            auto t = head;
            head = head->get_next();
            t->set_next(nullptr);

            t = tail;
            tail = tail->get_prev();
            t->set_prev(nullptr);
        }

        size = 0;
    }

    template<class T>
    size_t set<T>::cardinality() {
        return size;
    }

    template<class T>
    set_iterator<T> set<T>::find(const T &val) const {
        for (auto elem = begin(); elem != end(); ++elem)
            if (*elem == val)
                return set_iterator<T>(elem);

        return end();
    }

    /* 

       OPERATOR OVERLOADING

    */

    template<class T>
    set<T> &set<T>::operator=(const set<T> &list) const {
        if (this == &list)
            return *this;

        this->clear();

        size = 0;
        size = 0;
        head = nullptr;
        tail = nullptr;

        for (auto it = list.begin(); it != list.end(); it++) {
            sh_ptr<node<T>> tmp = nullptr;

            try {
                tmp = std::shared_ptr<node<T>>(new node<T>);
            } catch (std::bad_alloc &err) {
                auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                throw bad_alloc_err(ctime(&t), __FILE__, typeid(list).name(), __FUNCTION__);
            }
            tmp = sh_ptr<node<T>>(new node<T>);

            tmp->set(*it);
            insert(tmp);
        }

        return *this;

    }

    template<class T>
    bool set<T>::operator==(const set<T> &list) const {
        if (list.size != size)
            return false;

        for (auto el : list)
            if (!find(el))
                return false;

        return true;
    }

    template<class T>
    bool set<T>::operator!=(const set<T> &list) const {
        return !(*this == list);
    }

    template<class T>
    set<T> set<T>::operator+(const set<T> &_set) {
        set<T> s { *this };
        s += _set;
        return s;
    }

    template<class T>
    set<T> set<T>::operator+(const T &data) {
        set <T> s {*this};
        s += data;
        return s;
    }

    template<typename T>
    set<T> &set<T>::operator+=(const set<T> &list) {
        for (auto iter = list.begin(); list.end() != iter; ++iter)
            update(*iter);

        return *this;
    }

    template<typename T>
    set<T> &set<T>::operator+=(const T &data) {
        update(data);
        return *this;
    }


    template<class T>
    set<T> set<T>::operator&(const set<T> &_set) {
        set<T> s;

        auto it1 = this->begin(), it2 = _set.begin();

        while (it1 && it2) {
            if (*it1 == *it2) {
                s.insert(*it1);
                it1++; it2++;
            } else if (*it1 < *it2) {
                it1++;
            } else {
                it2++;
            }
        }

        return s;
    }

    template<class T>
    set<T> set<T>::operator&(const T & data) {
        if (this->find(data))
            return set<T> {data};
        return set<T>();
    }

    template<typename T>
    set<T> &set<T>::operator&=(const set<T> &list) {
        set<T> res;

        for (auto i = this->begin(), j = list.begin(); i && j;) {
            if (*i == *j) {
                res.append(*i);
                ++i;
                ++j;
            } else if (*i < *j) {
                ++i;
            } else {
                ++j;
            }
        }

        this->clear();

        for (auto i = res.begin(); i && (res.end() != i); ++i)
            append(*i);

        return *this;
    }

    template<typename T>
    set<T> &set<T>::operator&=(const T &data) {
        if (!find(data)) {
            clear();
        } else {
            clear();
            append(data);
        }

        return *this;
    }
    template<class T>
    set<T> set<T>::operator|(const set<T> &set) {
        return *this + set;
    }
    template<class T>
    set<T> set<T>::operator|(const T & data) {
        return *this + data;
    }

    template<typename T>
    set<T> &set<T>::operator|=(const set<T> &set) {
        *this += set;

        return *this;
    }

    template<typename T>
    set<T> &set<T>::operator|=(const T &data) {
        *this += data;

        return *this;
    }

    template<typename T>
    set<T> set<T>::operator-(const set<T> &data) {
        set<T> res;

        for (auto i : *this)
            res.append(i);

        for (auto i : data)
            res.erase(i);

        return res;
    }

    template<typename T>
    set<T> set<T>::operator-(const T &data) {
        set<T> res = *this;
        res.erase(data);

        return res;
    }

    template<typename T>
    set<T> &set<T>::operator-=(const set<T> &set) {
        for (auto i = set.begin(); set.end() != i; erase(*i), ++i)
            ;

        return *this;
    }

    template<typename T>
    set<T> &set<T>::operator-=(const T &data) {
        erase(data);

        return *this;
    }

    template<typename T>
    set<T> set<T>::operator^(const set<T> &data) {
        set<T> res;

        for (auto i : *this)
            if (!data.find(i))
                res.append(i);

        for (auto i : data)
            if (!find(i))
                res.append(i);

        return res;
    }

    template<typename T>
    set<T> set<T>::operator^(const T &data) {
        set<T> res;
        res = *this;
        res.erase(data);

        return res;
    }

    template<typename T>
    set<T> &set<T>::operator^=(const set<T> &list) {
        set<T> temp = *this ^ list;

        clear();
        for (auto i = temp.begin(); i != temp.end(); ++i)
            append(*i);

        return *this;
    }

    template<typename T>
    set<T> &set<T>::operator^=(const T &data) {
        if (!find(data))
            append(data);
        else
            erase(data);

        return *this;
    }

    // Iterators

    template<class T>
    set_iterator<T> set<T>::begin() const {
        return set_iterator<T>(head);
    }

    template<class T>
    set_iterator<T> set<T>::end() const {
        if (tail) {
            return set_iterator<T>(tail->get_next());
        } else {
            return set_iterator<T> (nullptr);
        }
    }

    // IOSTREAM


    template<typename T>
    std::ostream &operator<<(std::ostream &os, set<T> &list) {
        for (auto el = list.begin(); el != list.end(); ++el)
            os << *el << " ";

        return os;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const set<T> &list) {
        for (auto el = list.begin(); el != list.end(); ++el)
            os << *el << " ";

        return os;
    }

}




