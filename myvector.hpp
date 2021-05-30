#pragma once
#include <iostream>
#include <initializer_list>
#include <cassert>
#include <compare>

template <class T>
class myvector{
private:
    T *m_array;
    int m_size;

public:
    class const_myiterator : std::iterator<std::random_access_iterator_tag, T>{
        friend class myvector<T>;
    private:
        const T *m_ptr;
        const_myiterator(T *ptr) : m_ptr(ptr){};
    public:
        const_myiterator() : m_ptr(nullptr){};
        const_myiterator(const const_myiterator &it) : m_ptr(it.m_ptr){};
        const_myiterator(const_myiterator &&it);
        const_myiterator::reference operator=(const const_myiterator &it) noexcept;
        const_myiterator::reference operator=(const_myiterator &&it) noexcept;
        const_myiterator::reference operator*() const noexcept { return (*m_ptr); };
        const_myiterator::pointer operator->() const noexcept { return (m_ptr); };
        const_myiterator &operator++() noexcept;
        const_myiterator operator++(int) noexcept;
        const_myiterator &operator--() noexcept;
        const_myiterator operator--(int) noexcept;
        const_myiterator &operator+=(const typename const_myiterator::difference_type step) noexcept;
        const_myiterator operator+(const const_myiterator::difference_type step) const noexcept;
        const_myiterator &operator-=(const typename const_myiterator::difference_type step) noexcept;
        const_myiterator operator-(const const_myiterator::difference_type step) const noexcept;
        const_myiterator::difference_type operator-(const const_myiterator &_Right) const noexcept;
        const_myiterator::reference operator[](const const_myiterator::difference_type _Off) const noexcept;
        bool operator==(const const_myiterator &_Right) const noexcept;
        std::strong_ordering operator<=>(const const_myiterator &_Right) const noexcept;
    };
    class myiterator: const_myiterator{
        friend class myvector<T>;
    private:
        T* m_ptr;
        myiterator(T *ptr) :m_ptr(ptr){};
    public:
        myiterator():m_ptr(nullptr){};
        myiterator(const myiterator& it) :m_ptr(it.m_ptr){};
        myiterator(myiterator&& it);
        myiterator::reference operator =(const myiterator & it);
        myiterator::reference operator =(myiterator&& it);
        myiterator::reference operator*() const noexcept;
        myiterator::pointer operator->() const noexcept;
        myiterator& operator++() noexcept;
        myiterator operator++(int) noexcept;
        myiterator& operator--() noexcept;
        myiterator operator--(int) noexcept;
        myiterator& operator+=(const typename myiterator::difference_type _Off) noexcept;
        myiterator operator+(const myiterator::difference_type _Off) const noexcept;
        myiterator& operator-=(const typename myiterator::difference_type _Off) noexcept;
        myiterator operator-(const myiterator::difference_type _Off) const noexcept;
        myiterator::reference operator[](const myiterator::difference_type _Off) const noexcept;
    };
    // constructors
    myvector(){};
    myvector(int size) : m_size(size){};
    myvector(const std::initializer_list<T> &list);
    myvector(const myvector &myvec);
    myvector(myvector &&myvec);
    virtual ~myvector() { delete[] m_array; };
    // operators
    T &operator[](const int index) const { return (m_array[index]); };
    T &operator[](const int index) { return (m_array[index]); };
    myvector<T> &operator=(const myvector<T> &myvec);
    myvector<T> &operator=(myvector<T> &&myvec);
    template <class U>
    friend std::ostream &operator<<(std::ostream &out, const myvector<U> &myvec);
    template <class U>
    friend bool operator==(const myvector<U> &a, const myvector<U> &b);
    // functions
    const_myiterator cbegin() const;
    const_myiterator cend() const;
    myiterator begin() const;
    myiterator end() const;
    void insert(const_myiterator it, T Talue); //ttc assert write
    void push_back(T Talue);
    void pop_back();
    void resize(int size);
    int size() const { return (m_size); };
};

// functions

template <class T>
myvector<T>::const_myiterator myvector<T>::cbegin() const{
    return(myvector<T>::const_myiterator{m_array});
}

template <class T>
myvector<T>::const_myiterator myvector<T>::cend() const{
    return(myvector<T>::const_myiterator{m_array + m_size});
}

template<class T>
myvector<T>::myiterator myvector<T>::begin() const{
    return(myiterator{m_array});
}

template<class T>
myvector<T>::myiterator myvector<T>::end() const{
    return(myiterator{m_array+m_size});
}

template <class T>
void myvector<T>::insert(myvector<T>::const_myiterator it, T Talue){
}

template <class T>
void myvector<T>::push_back(T Talue){
    resize(m_size + 1);
    m_array[m_size - 1] = Talue;
}

template <class T>
void myvector<T>::pop_back(){
    resize(m_size - 1);
}

template <class T>
void myvector<T>::resize(int size){
    T *temp = new T[size];
    for (int i{0}; i < size; ++i)
        temp[i] = m_array[i];
    delete[] m_array;
    m_array = new T[size];
    m_size = size;
    for (int i{0}; i < size; ++i)
        m_array[i] = temp[i];
}

// operators

template <class T>
myvector<T> &myvector<T>::operator=(const myvector<T> &myvec){
    if (*this == myvec)
        return (*this);
    delete[] m_array;
    m_size = myvec.m_size;
    if (myvec.m_array)
    {
        m_array = new T[m_size];
        for (int i{0}; i < myvec.m_size; ++i)
        {
            m_array[i] = myvec.m_array[i];
        }
    }
    else
        m_array = nullptr;
    return (*this);
}

template <class T>
myvector<T> &myvector<T>::operator=(myvector<T> &&myvec){
    if (*this == myvec)
        return (*this);
    delete[] m_array;
    m_size = myvec.m_size;
    if (myvec.m_array)
    {
        m_array = new T[m_size];
        for (int i{0}; i < myvec.m_size; ++i)
        {
            m_array[i] = myvec.m_array[i];
        }
    }
    else
        m_array = nullptr;
    myvec.m_array = nullptr;
    return (*this);
}

template <class U>
bool operator==(const myvector<U> &a, const myvector<U> &b){
    if (a.m_array == b.m_array)
        return (false);
    return (true);
}

template <class U>
std::ostream &operator<<(std::ostream &out, const myvector<U> &myvec){
    for (int i{0}; i < myvec.m_size; ++i)
        out << myvec.m_array[i] << " ";
    return (out);
}

// constructors

template <class T>
myvector<T>::myvector(const std::initializer_list<T> &list) : myvector(list.size()){
    m_array = new T[m_size];
    int i{0};
    for (auto &elem : list)
    {
        m_array[i] = elem;
        ++i;
    }
}

template <class T>
myvector<T>::myvector(const myvector<T> &myvec){
    m_size = myvec.m_size;
    if (myvec.m_array)
    {
        m_array = new T[m_size];
        for (int i{0}; i < myvec.m_size; ++i)
        {
            m_array[i] = myvec.m_array[i];
        }
    }
    else
        m_array = nullptr;
}

template <class T>
myvector<T>::myvector(myvector<T> &&myvec){
    m_size = myvec.m_size;
    if (myvec.m_array)
    {
        m_array = new T[m_size];
        for (int i{0}; i < myvec.m_size; ++i)
        {
            m_array[i] = myvec.m_array[i];
        }
    }
    else
        m_array = nullptr;
    myvec.m_array = nullptr;
}

/*
----------------------------------------------------------------------------------
*/

template <class T>
myvector<T>::const_myiterator& myvector<T>::const_myiterator::operator+=(const typename myvector<T>::const_myiterator::difference_type step) noexcept{
    m_ptr += step;
    return (*this);
}

template <class T>
myvector<T>::const_myiterator& myvector<T>::const_myiterator::operator++() noexcept{
    ++m_ptr;
    return (*this);
}

template <class T>
myvector<T>::const_myiterator myvector<T>::const_myiterator::operator++(int) noexcept{
    auto old{*this};
    ++m_ptr;
    return (old);
}

template <class T>
myvector<T>::const_myiterator& myvector<T>::const_myiterator::operator--() noexcept{
    --m_ptr;
    return (*this);
}

template <class T>
myvector<T>::const_myiterator myvector<T>::const_myiterator::operator--(int) noexcept{
    auto old{*this};
    --m_ptr;
    return (old);
}

template <class T>
myvector<T>::const_myiterator::reference myvector<T>::const_myiterator::operator=(myvector<T>::const_myiterator &&it) noexcept{
    if (&it == this)
        return *this;
    m_ptr = it.m_ptr;
    it.m_ptr = nullptr;
    return (*this);
}

template <class T>
myvector<T>::const_myiterator::reference myvector<T>::const_myiterator::operator=(const myvector<T>::const_myiterator &it) noexcept{
    if (&it == this)
        return *this;
    m_ptr = it.m_ptr;
    return (*this);
}

template <class T>
myvector<T>::const_myiterator::const_myiterator(myvector<T>::const_myiterator &&it){
    m_ptr = it.m_ptr;
    it.m_ptr = nullptr;
}

/*
----------------------------------------------------------------------------------
*/


template <class T>
myvector<T>::myiterator::reference myvector<T>::myiterator::operator =(myvector<T>::myiterator && it){
    if (&it == this)
		return *this;
    m_ptr = it.m_ptr;
    it.m_ptr = nullptr;
    return(*this);
}

template <class T>
myvector<T>::myiterator::reference myvector<T>::myiterator::operator =(const myvector<T>::myiterator & it){
    if (&it == this)
		return *this;
    m_ptr = it.m_ptr;
    return(*this);
}

template <class T>
myvector<T>::myiterator::myiterator(myvector<T>::myiterator&& it){
    m_ptr = it.m_ptr; 
    it.m_ptr = nullptr;
}
