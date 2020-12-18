#ifndef VECTOR
#define VECTOR

#include <iostream>
#include <cassert>
using namespace std;

template<typename T>
class Vector {
public:
    class ConstIterator;
    class Iterator;
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = Vector::Iterator;
    using const_iterator = Vector::ConstIterator;

    class Iterator {
        public:
        using value_type = Vector::value_type;
        using reference = Vector::reference;
        using pointer = Vector::pointer;
        using difference_type = Vector::difference_type;
        using iterator_category = std::forward_iterator_tag;
        private:
        pointer ptr;

        public:
        Iterator() { this->ptr = nullptr; }
        Iterator(pointer ptr) { this->ptr = ptr; }

        reference operator*() const {
            return *(this->ptr);
        }

        pointer operator->() const {
            return this->ptr;
        }

        bool operator==(const const_iterator& it) const {
            return (this->ptr == it.operator->());
        }

        bool operator!=(const const_iterator& it) const {
            return !(*this == it);
        }
        iterator& operator++() {    //(Prefix)
            this->ptr += 1;
            return *this;
        }             
        iterator operator++(int) {  //(Postfix)
            iterator tmp = *this;
            this->ptr += 1;
            return tmp;
        }           
        operator const_iterator() const {   //(Typ-Konversion)
            // std::cout << "TYPE CONVERSION" << std::endl;
            return ConstIterator(this->ptr);
        }
    };

    class ConstIterator {
        public:
        using value_type = Vector::value_type;
        using reference = Vector::const_reference;
        using pointer = Vector::const_pointer;
        using difference_type = Vector::difference_type;
        using iterator_category = std::forward_iterator_tag;

        private:
        pointer ptr;

        public:
        ConstIterator() { this->ptr = nullptr; }
        ConstIterator(pointer ptr) { this->ptr = ptr; }

        reference operator*() const {
            return *(this->ptr);
        }
        pointer operator->() const {
            return this->ptr;
        }
        bool operator==(const const_iterator& it) const {
            return this->ptr == it.ptr;
        }
        bool operator!=(const const_iterator& it) const {
            return !(*this == it);
        }
        const const_iterator& operator++() {  //(Prefix)
            this->ptr += 1;
            return *this;
        }         
        const const_iterator operator++(int) {  //(Postfix)
            ConstIterator tmp = *this;
            this->ptr += 1;
            return tmp;
        }  

        friend Vector::difference_type operator-(const Vector::ConstIterator& lop, const Vector::ConstIterator& rop) {
            return lop.ptr - rop.ptr;
        }
    };

private:
    size_type sz;                               //Enthält die Anzahl der Elemente im Vector.
    size_type max_sz = min_sz;                  //Enthält die maximale Anzahl an Elementen die möglich sind.
    static constexpr size_type min_sz = 5;

    pointer values;                             //Zeigt auf ein Feld, welches die Elemente des Vectors beinhaltet.

public:
    Vector() {
        sz = 0;
        values = new value_type [max_sz];
    }

    Vector(size_t n) {
        this->sz = 0;
        this->max_sz = n < min_sz ? min_sz : n;
        init(n);
    }

    Vector(initializer_list<value_type> list) {
        sz = list.size();
        init(sz);

        int counter = 0;
        for (value_type item : list) {
            values[counter] = item;
            counter++;
        }
    }

    void init(size_type n) {
        if (n >= max_sz) {
            max_sz = n * 2;
        }
        values = new value_type [max_sz];
    }

    ~Vector() {
        delete [] values;
    }

    Vector(const Vector &rhs) {
        this->sz = rhs.sz;
        this-> max_sz = rhs.max_sz;
        this->values = new value_type[this->max_sz];

        for (size_type i = 0; i < sz; i++) {
            this->values[i] = rhs.values[i];
        }
    }

    void operator=(const Vector &rhs) {
        delete[] this->values;
        this->sz = rhs.sz;
        this-> max_sz = rhs.max_sz;
        this->values = new value_type[this->max_sz];

        for (size_type i = 0; i < sz; i++) {
            this->values[i] = rhs.values[i];
        }
    }

    size_type size() const {
        return sz;
    }

    size_type capacity() const {
        return max_sz;
    }

    bool empty() const {
        return sz <= 0;
    }

    void push_back(value_type x) {
        if (sz >= max_sz) {
            reserve(sz * 2);
        }
        values[sz] = x;
        sz += 1;
    }

    void pop_back() {
        if (sz <= 0) throw runtime_error("Vector ist leer. pop_back() konnte nicht ausgeführt werden!");
        sz -= 1;
    }

    reference at(size_type x) {
        if (x < sz && x >= 0) {
            return values[x];
        } else {
            throw runtime_error("vector.at(): nicht in Range!");
        }
    }

    const_reference at(size_type x) const {
        if (x < sz && x >= 0) {
            return values[x];
        } else {
            throw runtime_error("vector.at(): nicht in Range!");
        }
    }

    reference operator[](size_type index) {
        return at(index);
    }

    const_reference operator[](size_type index) const {
        return at(index);
    }

    void to_string(string suffix = "") {
        cout << "=====================" << endl;

        if (suffix != "") cout << "Var: " << suffix << endl;

        cout << "sz = " << sz << endl;
        cout << "max_sz = " << max_sz << endl;

        cout << "[";

        for (size_type i = 0; i < size(); i++) {
            const value_type value = values[i];

            cout << value;
            if (i < size() - 1) {
                cout << ", ";
            }
        }

        cout << "]" << endl;
        cout << "=====================" << endl;
    }
    void clear() {
        // delete[] values;
        sz = 0;
        // max_sz = min_sz;
        // values = new value_type[max_sz];
    }

    void reserve(size_type n) {
        if (n < max_sz) return;

        value_type* temp = new value_type [n];
        max_sz = n;

        for (size_type i = 0; i < sz; i++) {
            temp[i] = values[i];
        }

        delete[] values;
        values = temp;
    }

    void shrink_to_fit() {
        if (max_sz <= sz) return;
        max_sz = sz;
        if (max_sz < min_sz) {
            max_sz = min_sz;
        }
        value_type* temp = new value_type [max_sz];

        for (size_type i = 0; i < sz; i++) {
            temp[i] = values[i];
        }

        delete[] values;
        values = temp;
    }

    //Iteratoren
    iterator begin() {
        return Iterator(this->values);
    }
    iterator end() {
        return Iterator(this->values + this->sz);
    }
    const_iterator begin() const {
        return ConstIterator(this->values);
    }
    const_iterator end() const {
        return ConstIterator(this->values + this->sz);
    }

    iterator insert(const_iterator pos, const_reference val) {
        auto diff = pos-begin();
        if (diff<0 || static_cast<size_type>(diff)>sz)
            throw std::runtime_error("Iterator out of bounds");
        size_type current{static_cast<size_type>(diff)};
        if (sz>=max_sz)
            reserve(max_sz * 2);
        for (auto i {sz}; i-->current;)
            values[i+1]=values[i];
        values[current]=val;
        ++sz;
        return iterator{values+current};
    }

    iterator erase(const_iterator pos) {
        auto diff = pos-begin();
        if (diff<0 || static_cast<size_type>(diff)>=sz)
            throw std::runtime_error("Iterator out of bounds");
        size_type current{static_cast<size_type>(diff)};
        for (auto i{current}; i<sz-1; ++i)
        values[i]=values[i+1];
        --sz;
        return iterator{values+current};
    }
};

template<typename T>
ostream& operator<<(ostream &os, const Vector<T> &rhs) {
    os << "[";

    for (size_t i = 0; i < rhs.size(); i++) {
        const T value = rhs[i];

        os << value;
        if (i < rhs.size() - 1) {
            os << ", ";
        }
    }

    os << "]";

    return os;
}

#endif