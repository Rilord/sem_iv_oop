//
// Created by Kirill Diordiev on 11.06.2021.
//

#pragma once

#include <cstddef>
#include <ctime>
#include <iostream>
#include <vector>

#include <errors/errors.h>

template <class T>
class MatrixBase
{
    class Proxy
    {
    public:
        Proxy(size_t, T *);

        T &at(size_t);
        const T &at(size_t) const;
        T &operator[](size_t);
        const T &operator[](size_t) const;

    private:
        size_t col_count;
        T *data;
    };

public:
    //template <typename U>
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    //typedef ConstIterator<T> const_iterator;

    explicit MatrixBase(size_t, size_t);
    explicit MatrixBase(size_t, size_t, const T &);
    MatrixBase(size_t, size_t, iterator, iterator);
    MatrixBase(size_t, size_t, const_iterator, const_iterator);
    MatrixBase(size_t, size_t, std::initializer_list<T>);
    MatrixBase(const MatrixBase &);
    MatrixBase(MatrixBase &&);
    virtual ~MatrixBase();
    MatrixBase &operator=(const MatrixBase &);
    MatrixBase &operator=(MatrixBase &&);
    MatrixBase &operator=(std::initializer_list<T>);

    Proxy at(size_t);
    const Proxy at(size_t) const;
    Proxy operator[](size_t);
    const Proxy operator[](size_t) const;

    iterator begin();
    const_iterator cbegin() const;
    iterator end();
    const_iterator cend() const;

    iterator rbegin();
    const_iterator rcbegin() const;
    iterator rend();
    const_iterator rcend() const;

    size_t rows() const;
    size_t columns() const;
    size_t capacity() const;
    void zero();
    void swap(MatrixBase &);

    template <class U>
    friend inline void swap(MatrixBase<U> &, MatrixBase<U> &);

    template <class U>
    friend inline bool operator==(const MatrixBase<U> &, const MatrixBase<U> &);
    template <class U>
    friend inline bool operator!=(const MatrixBase<U> &, const MatrixBase<U> &);
    template <class U>
    friend inline bool operator<(const MatrixBase<U> &, const MatrixBase<U> &);
    template <class U>
    friend inline bool operator<=(const MatrixBase<U> &, const MatrixBase<U> &);
    template <class U>
    friend inline bool operator>(const MatrixBase<U> &, const MatrixBase<U> &);
    template <class U>
    friend inline bool operator>=(const MatrixBase<U> &, const MatrixBase<U> &);

    template <class U>
    friend inline std::ostream &operator<<(std::ostream &, const MatrixBase<U> &);

protected:
    size_t row_count;
    size_t col_count;
    size_t memory_dump;
    T *_data;
};

template <class T>
MatrixBase<T>::Proxy::Proxy(size_t col_count, T *data) : col_count(col_count), data(data)
{
}

template <class T>
T &MatrixBase<T>::Proxy::at(size_t index)
{
    if (index < this->col_count)
    {
        return *(this->data + index);
    }
}

template <class T>
const T &MatrixBase<T>::Proxy::at(size_t index) const
{
    if (index < this->col_count)
    {
        return *(this->data + index);
    }
}

template <class T>
T &MatrixBase<T>::Proxy::operator[](size_t index)
{
    if (index < this->col_count)
    {
        return *(this->data + index);
    }
}

template <class T>
const T &MatrixBase<T>::Proxy::operator[](size_t index) const
{
    if (index < this->col_count)
    {
        return *(this->data + index);
    }
}

template <class T>
MatrixBase<T>::MatrixBase(size_t row_count, size_t col_count)
        : row_count(row_count), col_count(col_count), memory_dump(row_count * col_count)
{
    try
    {
        this->_data = new T[this->memory_dump];
    }
}

template <class T>
MatrixBase<T>::MatrixBase(size_t row_count, size_t col_count, const T &value)
        : MatrixBase(row_count, col_count)
{
    for (size_t i = 0; i < this->memory_dump; ++i)
    {
        this->_data[i] = value;
    }
}

template <class T>
MatrixBase<T>::MatrixBase(size_t row_count, size_t col_count, iterator first, iterator last)
        : MatrixBase(row_count, col_count)
{
    size_t size = this->memory_dump <= static_cast<size_t>(last - first) ? this->memory_dump : static_cast<size_t>(last - first);

    for (size_t i = 0; i < size; ++i, ++first)
    {
        this->_data[i] = *first;
    }

    for (size_t i = size; i < this->memory_dump; ++i)
    {
        this->_data[i] = 0;
    }
}

template <class T>
MatrixBase<T>::MatrixBase(size_t row_count, size_t col_count, const_iterator first, const_iterator last)
        : MatrixBase(row_count, col_count)
{
    size_t size = this->memory_dump <= static_cast<size_t>(last - first) ? this->memory_dump : static_cast<size_t>(last - first);

    for (size_t i = 0; i < size; ++i, ++first)
    {
        this->_data[i] = *first;
    }

    for (size_t i = size; i < this->memory_dump; ++i)
    {
        this->_data[i] = 0;
    }
}

template <class T>
MatrixBase<T>::MatrixBase(size_t row_count, size_t col_count, std::initializer_list<T> lst)
        : MatrixBase(row_count, col_count)
{
    size_t size = this->memory_dump <= lst.size() ? this->memory_dump : lst.size();
    typename std::initializer_list<T>::iterator iter = lst.begin();

    for (size_t i = 0; i < size; ++i, ++iter)
    {
        this->_data[i] = *iter;
    }

    for (size_t i = size; i < this->memory_dump; ++i)
    {
        this->_data[i] = 0;
    }
}

template <class T>
MatrixBase<T>::MatrixBase(const MatrixBase &other)
        : MatrixBase(other.row_count, other.col_count)
{
    std::copy(other._data, other._data + other.memory_dump, this->_data);
}

template <class T>
MatrixBase<T>::MatrixBase(MatrixBase &&other)
        : row_count(other.row_count), col_count(other.col_count), _data(other._data)
{
    other.row_count = 0;
    other.col_count = 0;
    other.memory_dump = 0;
    other._data = nullptr;
}

template <class T>
MatrixBase<T>::~MatrixBase()
{
    delete[] _data;
    this->row_count = 0;
    this->col_count = 0;
    this->memory_dump = 0;
    this->_data = nullptr;
}

template <class T>
MatrixBase<T> &MatrixBase<T>::operator=(const MatrixBase<T> &other)
{
    if (this != &other)
    {
        this->row_count = other.row_count;
        this->col_count = other.col_count;
        this->memory_dump = other.memory_dump;

        try
        {
            delete[] this->_data;
            this->_data = new T[this->memory_dump];
        }

        std::copy(other._data, other._data + other.memory_dump, this->_data);
    }

    return *this;
}

template <class T>
MatrixBase<T> &MatrixBase<T>::operator=(MatrixBase &&other)
{
    if (this != &other)
    {
        this->row_count = other.row_count;
        this->col_count = other.col_count;
        this->memory_dump = other.memory_dump;

        delete[] this->_data;
        this->_data = other._data;

        other.row_count = 0;
        other.col_count = 0;
        other.memory_dump = 0;
        other._data = nullptr;
    }

    return *this;
}

template <class T>
MatrixBase<T> &MatrixBase<T>::operator=(std::initializer_list<T> lst)
{
    size_t size = this->memory_dump <= lst.size() ? this->memory_dump : lst.size();
    typename std::initializer_list<T>::const_iterator iter = lst.begin();

    for (size_t i = 0; i < size; ++i, ++iter)
    {
        this->_data[i] = *iter;
    }

    for (size_t i = size; i < this->memory_dump; ++i)
    {
        this->_data[i] = 0;
    }

    return *this;
}

template <class T>
typename MatrixBase<T>::Proxy MatrixBase<T>::at(size_t index)
{
    if (index < this->row_count)
    {
        return Proxy(this->col_count, this->_data + this->col_count * index);
    }
}

template <class T>
const typename MatrixBase<T>::Proxy MatrixBase<T>::at(size_t index) const
{
    if (index < this->row_count)
    {
        return Proxy(this->col_count, this->_data + this->col_count * index);
    }
}

template <class T>
typename MatrixBase<T>::Proxy MatrixBase<T>::operator[](size_t index)
{
    if (index < this->row_count)
    {
        return Proxy(this->col_count, this->_data + this->col_count * index);
    }
    else
    {
        std::string message = "Error in Matrix operator []";
        throw range_error(message);
    }
}

template <class T>
const typename MatrixBase<T>::Proxy MatrixBase<T>::operator[](size_t index) const
{
    if (index < this->row_count)
    {
        return Proxy(this->col_count, this->_data + this->col_count * index);
    }
    else
    {
        std::string message = "Error in Matrix operator []";
        throw range_error(message);
    }
}

template <class T>
typename MatrixBase<T>::iterator MatrixBase<T>::begin()
{
    return iterator(this->_data);
}

template <class T>
typename MatrixBase<T>::const_iterator MatrixBase<T>::cbegin() const
{
    return const_iterator(this->_data);
}

template <class T>
typename MatrixBase<T>::iterator MatrixBase<T>::end()
{
    return iterator(this->_data + this->memory_dump);
}

template <class T>
typename MatrixBase<T>::const_iterator MatrixBase<T>::cend() const
{
    return const_iterator(this->_data + this->memory_dump);
}

template <class T>
typename MatrixBase<T>::iterator MatrixBase<T>::rbegin()
{
    return iterator(this->_data + this->memory_dump - 1);
}

template <class T>
typename MatrixBase<T>::const_iterator MatrixBase<T>::rcbegin() const
{
    return const_iterator(this->_data + this->memory_dump - 1);
}

template <class T>
typename MatrixBase<T>::iterator MatrixBase<T>::rend()
{
    return iterator(this->_data - 1);
}

template <class T>
typename MatrixBase<T>::const_iterator MatrixBase<T>::rcend() const
{
    return const_iterator(this->_data - 1);
}

template <class T>
size_t MatrixBase<T>::rows() const
{
    return this->row_count;
}

template <class T>
size_t MatrixBase<T>::columns() const
{
    return this->col_count;
}

template <class T>
size_t MatrixBase<T>::capacity() const
{
    return this->memory_dump;
}

template <class T>
void MatrixBase<T>::zero()
{
    for (size_t i = 0; i < this->memory_dump; ++i)
    {
        this->_data[i] = T();
    }
}

template <class T>
void MatrixBase<T>::swap(MatrixBase<T> &other)
{
    std::swap(this->row_count, other.row_count);
    std::swap(this->col_count, other.col_count);
    std::swap(this->memory_dump, other.memory_dump);
    std::swap(this->_data, other._data);
}

template <class T>
void swap(MatrixBase<T> &lhs, MatrixBase<T> &rhs)
{
    lhs.swap(rhs);
}

template <class T>
bool operator==(const MatrixBase<T> &lhs, const MatrixBase<T> &rhs)
{
    bool are_equal = lhs.size() == rhs.size();

    if (are_equal)
    {
        for (size_t i = 0; i < lhs.size() && are_equal; ++i)
        {
            if (lhs[i] != rhs[i])
            {
                are_equal = false;
            }
        }
    }

    return are_equal;
}

template <class T>
bool operator!=(const MatrixBase<T> &lhs, const MatrixBase<T> &rhs)
{
    return !(rhs == lhs);
}

template <class T>
bool operator<(const MatrixBase<T> &lhs, const MatrixBase<T> &rhs)
{
    bool is_less = lhs.size() < rhs.size();

    if (!is_less && lhs.size() == rhs.size())
    {
        for (size_t i = 0; i < lhs.size() && !is_less; ++i)
        {
            if (lhs[i] < rhs[i])
            {
                is_less = true;
            }
        }
    }

    return is_less;
}

template <class T>
bool operator<=(const MatrixBase<T> &lhs, const MatrixBase<T> &rhs)
{
    return lhs < rhs || lhs == rhs;
}

template <class T>
bool operator>(const MatrixBase<T> &lhs, const MatrixBase<T> &rhs)
{
    return !(lhs < rhs) && !(lhs == rhs);
}

template <class T>
bool operator>=(const MatrixBase<T> &lhs, const MatrixBase<T> &rhs)
{
    return lhs > rhs || lhs == rhs;
}

template <class T>
std::ostream &operator<<(std::ostream &stream, const MatrixBase<T> &mtx)
{
    for (size_t i = 0; i < mtx.rows(); ++i)
    {
        for (size_t j = 0; j < mtx.columns(); ++j)
        {
            stream << mtx[i][j] << " ";
        }

        stream << std::endl;
    }

    return stream;
}


template <class T>
class Matrix : public MatrixBase<T>
{
public:
    typedef typename MatrixBase<T>::iterator iterator;
    typedef typename MatrixBase<T>::const_iterator const_iterator;

    explicit Matrix(size_t, size_t);
    explicit Matrix(size_t, size_t, const T &);
    Matrix(size_t, size_t, iterator, iterator);
    Matrix(size_t, size_t, const_iterator, const_iterator);
    Matrix(size_t, size_t, std::initializer_list<T>);
    Matrix(const Matrix &);
    Matrix(Matrix &&);
    virtual ~Matrix() = default;
    Matrix &operator=(const Matrix &);
    Matrix &operator=(Matrix &&);
    Matrix &operator=(std::initializer_list<T>);

    template <class U>
    friend Matrix<U> operator+(const Matrix<U> &, const Matrix<U> &);
    template <class U>
    friend Matrix<U> operator+(const Matrix<U> &, const U &);
    Matrix &operator+=(const Matrix &);
    Matrix &operator+=(const T &);
    template <class U>
    friend Matrix<U> operator-(const Matrix<U> &, const Matrix<U> &);
    template <class U>
    friend Matrix<U> operator-(const Matrix<U> &, const U &);
    Matrix &operator-=(const Matrix &);
    Matrix &operator-=(const T &);
    template <class U>
    friend Matrix<U> operator*(const Matrix<U> &, const Matrix<U> &);
    template <class U>
    friend Matrix<U> operator*(const Matrix<U> &, const U &);
    Matrix &operator*=(const Matrix &);
    Matrix &operator*=(const T &);
    template <class U>
    friend Matrix<U> operator/(const Matrix<U> &, const U &);
    Matrix &operator/=(const T &);
};

template <class T>
Matrix<T>::Matrix(size_t row_count, size_t col_count)
        : MatrixBase<T>(row_count, col_count)
{
}

template <class T>
Matrix<T>::Matrix(size_t row_count, size_t col_count, const T &value)
        : MatrixBase<T>(row_count, col_count, value)
{
}

template <class T>
Matrix<T>::Matrix(size_t row_count, size_t col_count, iterator first, iterator last)
        : MatrixBase<T>(row_count, col_count, first, last)
{
}

template <class T>
Matrix<T>::Matrix(size_t row_count, size_t col_count, const_iterator first, const_iterator last)
        : MatrixBase<T>(row_count, col_count, first, last)
{
}

template <class T>
Matrix<T>::Matrix(size_t row_count, size_t col_count, std::initializer_list<T> lst)
        : MatrixBase<T>(row_count, col_count, lst)
{
}

template <class T>
Matrix<T>::Matrix(const Matrix &other)
        : MatrixBase<T>(other)
{
}

template <class T>
Matrix<T>::Matrix(Matrix &&other)
        : MatrixBase<T>(std::move(other))
{
}

template <class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &rhs)
{
    MatrixBase<T>::operator=(rhs);

    return *this;
}

template <class T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&rhs)
{
    MatrixBase<T>::operator=(std::move(rhs));

    return *this;
}

template <class T>
Matrix<T> &Matrix<T>::operator=(std::initializer_list<T> lst)
{
    MatrixBase<T>::operator=(lst);

    return *this;
}

template <class T>
Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs)
{
    Matrix<T> result = lhs;
    size_t rows_count = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows();
    size_t cols_count = lhs.columns() < rhs.columns() ? lhs.columns() : rhs.columns();

    for (size_t i = 0; i < rows_count; ++i)
    {
        for (size_t j = 0; j < cols_count; ++j)
        {
            result[i][j] += rhs[i][j];
        }
    }

    return result;
}

template <class T>
Matrix<T> operator+(const Matrix<T> &mtx, const T &value)
{
    Matrix<T> result = mtx;

    for (size_t i = 0; i < mtx.capacity(); ++i)
    {
        result._data[i] += value;
    }

    return result;
}

template <class T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &rhs)
{
    size_t rows_count = this->rows() < rhs.rows() ? this->rows() : rhs.rows();
    size_t cols_count = this->columns() < rhs.columns() ? this->columns() : rhs.columns();

    for (size_t i = 0; i < rows_count; ++i)
    {
        for (size_t j = 0; j < cols_count; ++j)
        {
            (*this)[i][j] += rhs[i][j];
        }
    }

    return *this;
}

template <class T>
Matrix<T> &Matrix<T>::operator+=(const T &value)
{
    for (size_t i = 0; i < this->capacity(); ++i)
    {
        this->_data[i] += value;
    }

    return *this;
}

template <class T>
Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs)
{
    Matrix<T> result = lhs;
    size_t rows_count = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows();
    size_t cols_count = lhs.columns() < rhs.columns() ? lhs.columns() : rhs.columns();

    for (size_t i = 0; i < rows_count; ++i)
    {
        for (size_t j = 0; j < cols_count; ++j)
        {
            result[i][j] -= rhs[i][j];
        }
    }

    return result;
}

template <class T>
Matrix<T> operator-(const Matrix<T> &mtx, const T &value)
{
    Matrix<T> result = mtx;

    for (size_t i = 0; i < mtx.capacity(); ++i)
    {
        result._data[i] -= value;
    }

    return result;
}

template <class T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &rhs)
{
    size_t rows_count = this->rows() < rhs.rows() ? this->rows() : rhs.rows();
    size_t cols_count = this->columns() < rhs.columns() ? this->columns() : rhs.columns();

    for (size_t i = 0; i < rows_count; ++i)
    {
        for (size_t j = 0; j < cols_count; ++j)
        {
            (*this)[i][j] -= rhs[i][j];
        }
    }

    return *this;
}

template <class T>
Matrix<T> &Matrix<T>::operator-=(const T &value)
{
    for (size_t i = 0; i < this->capacity(); ++i)
    {
        this->_data[i] -= value;
    }

    return *this;
}

template <class T>
Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs)
{
    if (lhs.columns() == rhs.rows())
    {
        Matrix<T> result = lhs;

        for (size_t i = 0; i < lhs.rows(); ++i)
        {
            for (size_t j = 0; j < rhs.columns(); ++j)
            {
                for (size_t k = 0; k < lhs.columns(); ++k)
                {
                    result[i][j] += lhs[i][k] * rhs[k][j];
                }
            }
        }

        return result;
    }
    else
    {
        std::string message = "Error in Matrix operator *";
        throw range_error(message);
    }
}

template <class T>
Matrix<T> &operator*(const Matrix<T> &mtx, const T &value)
{
    Matrix<T> result = mtx;

    for (size_t i = 0; i < mtx.capacity(); ++i)
    {
        result._data[i] *= value;
    }

    return result;
}

template <class T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &rhs)
{
    if (this->columns() == rhs.rows())
    {
        for (size_t i = 0; i < this->rows(); ++i)
        {
            for (size_t j = 0; j < rhs.columns(); ++j)
            {
                for (size_t k = 0; k < this->columns(); ++k)
                {
                    (*this)[i][j] = (*this)[i][k] * rhs[k][j];
                }
            }
        }

        return *this;
    }
}

template <class T>
Matrix<T> &Matrix<T>::operator*=(const T &value)
{
    for (size_t i = 0; i < this->capacity(); ++i)
    {
        this->_data[i] *= value;
    }

    return *this;
}

template <class T>
Matrix<T> &operator/(const Matrix<T> &mtx, const T &value)
{
    Matrix<T> result = mtx;

    for (size_t i = 0; i < mtx.capacity(); ++i)
    {
        result._data[i] /= value;
    }

    return result;
}

template <class T>
Matrix<T> &Matrix<T>::operator/=(const T &value)
{
    for (size_t i = 0; i < this->capacity(); ++i)
    {
        this->_data[i] /= value;
    }

    return *this;
}
