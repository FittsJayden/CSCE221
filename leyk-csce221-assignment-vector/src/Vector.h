#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm> // std::random_access_iterator_tag
#include <cstddef> // size_t
#include <stdexcept> // std::out_of_range
#include <type_traits> // std::is_same

template <class T>
class Vector {
public:
    class iterator;
private:
    T* array;
    size_t _capacity, _size;

    // You may want to write a function that grows the vector
    void grow() {
        _capacity *= 2;
    }

public:
    Vector() noexcept {
        array = new T();
        _capacity = 0;
        _size = 0;
    }
    Vector(size_t count, const T& value) {
        array = new T();
        for (int i=0; i < count; i++) {
            array[i] = value;
        }
        _size = count;
        _capacity = count;
    }
    explicit Vector(size_t count) {
        array = new T();
        _capacity = count;
        _size = count;
    }
    Vector(const Vector& other) {
        this->_size = other.size();
        this->_capacity = other.capacity();

        for (int i = 0; i < other.size(); i++) {
            this->array[i] = other.array[i];
        }
    }
    Vector(Vector&& other) noexcept { /* TODO */ }

    ~Vector() {
        delete[] array;
        _size = 0;
        _capacity = 0;
        //not sure if this pointer needs delete
    }

    Vector& operator=(const Vector& other) { /* TODO */ }
    Vector& operator=(Vector&& other) noexcept { /* TODO */ }

    iterator begin() noexcept {
        if (_size == 0) {
            return iterator(nullptr);
        }
        
        else {
            return iterator(array);
        }
    }
    iterator end() noexcept {
        return iterator (array += _size); //might have to derefernece
    }

    [[nodiscard]] bool empty() const noexcept {
        if (_size > 0) {
            return false;
        }
        return true;
    }
    size_t size() const noexcept {
        return _size;
    }
    size_t capacity() const noexcept {
        return _capacity;
    }

    T& at(size_t pos) {
        
    }
    const T& at(size_t pos) const { /* TODO */ }
    T& operator[](size_t pos) {
        return array[pos];
    }
    const T& operator[](size_t pos) const {
        return array[pos];
    }
    T& front() { /* TODO */ }
    const T& front() const { /* TODO */ }
    T& back() { /* TODO */ }
    const T& back() const { /* TODO */ }

    void push_back(const T& value) { /* TODO */ }
    void push_back(T&& value) { /* TODO */ }
    void pop_back() { /* TODO */ }

    iterator insert(iterator pos, const T& value) { /* TODO */ }
    iterator insert(iterator pos, T&& value) { /* TODO */ }
    iterator insert(iterator pos, size_t count, const T& value) { /* TODO */ }
    iterator erase(iterator pos) { /* TODO */ }
    iterator erase(iterator first, iterator last) { /* TODO */ }

    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
    private:
        // Add your own data members here
        pointer key;
        // HINT: For random_access_iterator, the data member is a pointer 99.9% of the time
    public:
        iterator() {
            key = nullptr;
        }
        // Add any constructors that you may need
        iterator(T* value) {
            key = value;
        }

        // This assignment operator is done for you, please do not add more
        iterator& operator=(const iterator&) noexcept = default;

        [[nodiscard]] reference operator*() const noexcept {
            return *key;
        }
        [[nodiscard]] pointer operator->() const noexcept {
            return key;
        }

        // Prefix Increment: ++a
        iterator& operator++() noexcept {
            key++;
            return *this;
        }

        // Postfix Increment: a++
        // The value returned should be the iterator before it was moved forward in the container
        iterator operator++(int) noexcept {
            iterator temp = key;
            key++;
            return temp;
        }

        // Prefix Decrement: --a
        // The value returned should be the iterator moved backwards in the container
        iterator& operator--() noexcept {
            key--;
            return *this;
        }

        // Postfix Decrement: a--
        // The value returned should be the iterator before it was moved backwards in the container
        iterator operator--(int) noexcept {
            iterator temp = key;
            key--;
            return temp;
        }

        // Should move the iterator forward by an offset and return the new iterator
        iterator& operator+=(difference_type offset) noexcept {
            key += offset;
            return *this;
        }
        
        // Should return a copy of the iterator moved forward by an offset
        // NOTE: The iterator itself should not be moved, only the copy
        [[nodiscard]] iterator operator+(difference_type offset) const noexcept {
            iterator temp = *this;
            return temp += offset;
        }
        
        // Should move the iterator backwards by an offset and return the new iterator
        iterator& operator-=(difference_type offset) noexcept {
            return (*this += (-offset));
        }

        // Should return a copy of the iterator moved backwards by an offset
        // NOTE: The iterator itself should not be moved, only the copy
        [[nodiscard]] iterator operator-(difference_type offset) const noexcept {
            iterator temp = *this;
            return temp -= offset;
        }

        // Should return the difference between two iterators. This should be the offset betweent the
        // elements in memory.
        [[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept {
            return (key - rhs.key);
        }

        // Should return the element at the location offset from the iterator
        [[nodiscard]] reference operator[](difference_type offset) const noexcept {
            return *(key + offset);
        }

        [[nodiscard]] bool operator==(const iterator& rhs) const noexcept {
            return key == rhs.key;
        }
        [[nodiscard]] bool operator!=(const iterator& rhs) const noexcept {
            return (!(key == rhs.key));
        }
        [[nodiscard]] bool operator<(const iterator& rhs) const noexcept {
            return key < rhs.key;
        }
        [[nodiscard]] bool operator>(const iterator& rhs) const noexcept {
            return key > rhs.key;
        }
        [[nodiscard]] bool operator<=(const iterator& rhs) const noexcept {
            return key <= rhs.key;
        }
        [[nodiscard]] bool operator>=(const iterator& rhs) const noexcept {
            return key >= rhs.key;
        }
    
    };


    void clear() noexcept {/* to do */}
};

// This ensures at compile time that the deduced argument _Iterator is a Vector<T>::iterator
// There is no way we know of to back-substitute template <typename T> for external functions
// because it leads to a non-deduced context
namespace {
    template <typename _Iterator>
    using is_vector_iterator = std::is_same<typename Vector<typename _Iterator::value_type>::iterator, _Iterator>;
}

template <typename _Iterator, bool _enable = is_vector_iterator<_Iterator>::value>
[[nodiscard]] _Iterator operator+(typename _Iterator::difference_type offset, _Iterator const& iterator) noexcept { /* TODO */ }

#endif
