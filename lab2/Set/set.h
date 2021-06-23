#pragma once

// SYSTEM
#include <memory>
#include <initializer_list>
#include <chrono>

// LIBS
#include <base.h>
#include <set_iterator.h>
#include <node.h>

namespace math_set {

    template<class T>
    class set: public base {
        public:
            // Constructors
            set() = default;
            set(const set<T> &list) noexcept(false);
            set(set<T> &&list) noexcept;
            set(std::initializer_list<T> elems);

            // Destructor
            ~set() override;

            // Add, if exists return false
            bool add(const T &val) noexcept(false);
            bool add(T &&rval) noexcept(false);
            bool add(std::initializer_list<T> init_list) noexcept(false);
            void add(T *ilist, size_t len) noexcept(false);
            set<T> &operator+=(const set<T> &set);
            set<T> &operator+=(const T & data);
            
            set<T> update(const T &value) noexcept(false);
            set<T> update(T &&value) noexcept(false);
            set<T> update(std::initializer_list<T> ilist) noexcept(false);
            set<T> update(T *ilist, size_t len) noexcept(false);

            set<T>  operator+(const set<T> &set);
            set<T>  operator+(const T & data);


            // intersection group

            set<T>  intersection(const set<T> &set);
            set<T>  intersection(const T & data);
            set<T> intersection(std::initializer_list<T> init_list);
            set<T> intersection(T *ilist, size_t len);

            set<T>  operator&(const set<T> &set);
            set<T>  operator&(const T & data);
            set<T>  &operator&=(const set<T> &set);
            set<T>  &operator&=(const T & data);


            // Combination group
            set<T> combine(const set<T> &set);
            set<T> combine(const T & data);
            set<T> combine(std::initializer_list<T> init_list);
            set<T> combine(T *ilist, size_t len);

            set<T> operator|(const set<T> &set);
            set<T> operator|(const T & data);
            set<T> &operator|=(const set<T> &set);
            set<T> &operator|=(const T & data);

            // Difference group
            set<T> diff(const set<T> &set);
            set<T> diff(const T & data);
            set<T> diff(std::initializer_list<T> init_list);
            set<T> diff(T *ilist, size_t len);

            set<T> operator-(const set<T> &set);
            set<T> operator-(const T & data);
            set<T> &operator-=(const set<T> &set);
            set<T> &operator-=(const T & data);


            // Symetrical difference group
            set<T> sym_diff(const set<T> &set);
            set<T> sym_diff(const T & data);
            set<T> sym_diff(std::initializer_list<T> init_list);
            set<T> sym_diff(T *ilist, size_t len);

            set<T> operator^(const set<T> &set);
            set<T> operator^(const T &data);
            set<T> &operator^=(const set<T> &set);
            set<T> &operator^=(const T &data);

            // Erase
            void erase(const T &val);
            void erase(set_iterator<T> where);
            void erase(set_iterator<T> start, set_iterator<T> end);

            void clear() override;



            set<T> &operator=(const set<T> &list) const;
            set<T> &operator=(set<T> &&list) const;

            bool operator==(const set<T> &list) const;
            bool operator!=(const set<T> &list) const;

            set_iterator<T> begin() const;
            set_iterator<T> end() const;

            // По-русски мощность
            size_t cardinality(); 

        private:

            std::shared_ptr<node<T>> head;
            std::shared_ptr<node<T>> tail;

        protected:
            set_iterator<T> find(const T & val) const;
            bool insert(const std::shared_ptr<node<T>> &node) noexcept;



    };
}
