#include <cstddef>    // size_t
#include <functional> // std::hash
#include <ios>
#include <utility>    // std::pair
#include <iostream>

#include "primes.h"



template <typename Key, typename T, typename Hash = std::hash<Key>, typename Pred = std::equal_to<Key>>
class UnorderedMap {
    public:

    using key_type = Key;
    using mapped_type = T;
    using const_mapped_type = const T;
    using hasher = Hash;
    using key_equal = Pred;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    private:

    struct HashNode {
        HashNode *next;
        value_type val;

        HashNode(HashNode *next = nullptr) : next{next} {}
        HashNode(const value_type & val, HashNode * next = nullptr) : next { next }, val { val } { }
        HashNode(value_type && val, HashNode * next = nullptr) : next { next }, val { std::move(val) } { }
    };

    size_type _bucket_count;
    HashNode **_buckets;

    HashNode * _head;
    size_type _size;

    Hash _hash;
    key_equal _equal;

    static size_type _range_hash(size_type hash_code, size_type bucket_count) {
        return hash_code % bucket_count;
    }

    public:

    template <typename pointer_type, typename reference_type, typename _value_type>
    class basic_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = _value_type;
        using difference_type = ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

    private:
        friend class UnorderedMap<Key, T, Hash, key_equal>;
        using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

        const UnorderedMap * _map;
        HashNode * _ptr;

        explicit basic_iterator(UnorderedMap const * map, HashNode *ptr) noexcept {
            _map = map;
            _ptr = ptr;
        }

    public:
        basic_iterator() {
            _map = nullptr; 
            _ptr = nullptr;
        };
        basic_iterator(const basic_iterator &) = default;
        basic_iterator(basic_iterator &&) = default;
        ~basic_iterator() = default;
        basic_iterator &operator=(const basic_iterator &) = default;
        basic_iterator &operator=(basic_iterator &&) = default;
        reference operator*() const {
            return _ptr->val;
        }
        pointer operator->() const {
            return &(_ptr->val);
        }
        basic_iterator &operator++() {
            if (_ptr->next != nullptr) {
                _ptr = nullptr;
                return *this;
            }

            size_type curr = _range_hash(_map->_hash(_ptr->val.first), _map->_bucket_count);

            for (auto i = curr + 1; i < _map->_bucket_count; i++) {
                HashNode* buck = _map->_buckets[i];

                if (buck != nullptr) {
                    _ptr = buck;
                    return *this;
                }

            }

            _ptr = nullptr;
            return *this;
        }
        basic_iterator operator++(int) {
            basic_iterator buffer = basic_iterator(_map, _ptr);
            ++(*this);
            return buffer;
        }
        bool operator==(const basic_iterator &other) const noexcept {
            return this->_ptr == other._ptr;
        }
        bool operator!=(const basic_iterator &other) const noexcept {
            return !(this->_ptr == other._ptr);
        }
    };

    using iterator = basic_iterator<pointer, reference, value_type>;
    using const_iterator = basic_iterator<const_pointer, const_reference, const value_type>;

    class local_iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = std::pair<const key_type, mapped_type>;
            using difference_type = ptrdiff_t;
            using pointer = value_type *;
            using reference = value_type &;

        private:
            friend class UnorderedMap<Key, T, Hash, key_equal>;
            using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

            HashNode * _node;

            explicit local_iterator( HashNode * node ) noexcept: _node{node} {}

        public:
            local_iterator(): _node(nullptr) {};

            local_iterator(const local_iterator &) = default;
            local_iterator(local_iterator &&) = default;
            ~local_iterator() = default;
            local_iterator &operator=(const local_iterator &) = default;
            local_iterator &operator=(local_iterator &&) = default;
            reference operator*() const {
                return this->_node->val;
            }
            pointer operator->() const {
                return &(this->_node->val);
            }
            local_iterator & operator++() {
                if (_node->next == nullptr) {
                    _node = nullptr;
                    return *this;
                }

                _node = _node->next;
                return *this;
            }
            local_iterator operator++(int) {
                local_iterator buffer = local_iterator(this->_node);
                ++(*this);
                return buffer;
            }

            bool operator==(const local_iterator &other) const noexcept {
                return this->_node == other._node;
            }
            bool operator!=(const local_iterator &other) const noexcept {
                return !(this->_node == other._node);
            }
    };

private:

    size_type _bucket(size_t code) const {
        return _range_hash(code, this->_bucket_count);
    }
    size_type _bucket(const Key & key) const {
        return _bucket(_hash(key));
    }
    size_type _bucket(const value_type & val) const {
        return _bucket(val.first);
    }

    HashNode*& _find(size_type code, size_type bucket, const Key & key) {

        HashNode** buffer = &(_buckets[bucket]);

        while (*buffer != nullptr) {
            if (_equal((*buffer)->val.first, key)) {
                return *buffer;
            }
            buffer = &((*buffer)->next);
        }

        return *buffer;
    }

    HashNode*& _find(const Key & key) {
        return _find(_hash(key), _bucket(key), key);
    }

    HashNode * _insert_into_bucket(size_type bucket, value_type && value) {
        
        HashNode* newNode = new HashNode(std::move(value));

        if (_head == nullptr || _bucket(_head->val) >= bucket) {
            _head = newNode;
        }

        if (_buckets[bucket] != nullptr) {
            newNode->next = _buckets[bucket];
        }

        _size++;
        _buckets[bucket] = newNode;
        return newNode;
    }

    void _move_content(UnorderedMap & src, UnorderedMap & dst) {
        dst._head = src._head;
        dst._size = src._size;
        dst._equal = std::move(src._equal);
        dst._hash = std::move(src._hash);
        dst._bucket_count = src._bucket_count;
        dst._buckets = src._buckets;

        src._head = nullptr;
        src._buckets = new HashNode*[src._bucket_count]();
        src._size = 0;
    }

public:
    explicit UnorderedMap(size_type bucket_count, const Hash & hash = Hash { },
                const key_equal & equal = key_equal { }) {
                    _head = nullptr;
                    _size = 0;
                    _hash = hash;
                    _equal = equal;
                    _bucket_count = next_greater_prime(bucket_count);
                    _buckets = new HashNode*[_bucket_count]();
                }

    ~UnorderedMap() {
        clear();
        delete [] _buckets;
        _bucket_count = 0;
        _size = 0;
    }

    UnorderedMap(const UnorderedMap & other) {
        this->~UnorderedMap();

        _head = other._head;
        _size = other._size;
        _hash = other._hash;
        _equal = other._equal;
        _bucket_count = other._bucket_count;
        _buckets = new HashNode*[_bucket_count]();

        for (size_type i = 0; i < other._bucket_count; i++) {
            HashNode* newNode = other._buckets[i];

            while (newNode != nullptr) {
                insert(newNode->val);
                newNode = newNode->next;
            }
        }
    }

    UnorderedMap(UnorderedMap && other) {
        _move_content(other, *this);
    }

    UnorderedMap & operator=(const UnorderedMap & other) {
        if (this != &other) {
            this->~UnorderedMap();

            _head = nullptr;
            _hash = other._hash;
            _equal = other._equal;
            _bucket_count = other._bucket_count;
            _buckets = new HashNode*[_bucket_count]();

            for (size_type buck = 0; buck < other._bucket_count; buck++) {
                HashNode* newNode = other._buckets[buck];
                while (newNode != nullptr) {
                    insert(newNode->val);
                    newNode = newNode->next;
                }
            }
        }
        return *this;
    }

    UnorderedMap & operator=(UnorderedMap && other) {
        if (this != &other) {
            this->~UnorderedMap();
            _move_content(other, *this);
        }
        return *this;
    }

    void clear() noexcept {
        if (_size > 0) {

            for (size_type i = 0; i < _bucket_count; i++) {
                HashNode* curr = _buckets[i];

                while (curr != nullptr) {
                    HashNode* search = curr;
                    curr = curr->next;
                    erase(iterator(this, search));
                    _size--;
                }
            }
            _bucket_count = 0;
            _size =0;
        }
        
    }

    size_type size() const noexcept {return _size;}

    bool empty() const noexcept {
        return _size == 0;
    }

    size_type bucket_count() const noexcept {return _bucket_count;}

    iterator begin() {
        return iterator(this, _head);
    }
    iterator end() {
        return iterator(this, nullptr);
    }

    const_iterator cbegin() const {
        return const_iterator(this, _head);
    };
    const_iterator cend() const {
        return const_iterator(this, nullptr);
    };

    local_iterator begin(size_type n) {
        return local_iterator(_buckets[n]);
    }
    local_iterator end(size_type n) {
        return local_iterator(nullptr);
    }

    size_type bucket_size(size_type n) {
        size_type count = 0;
        for (auto i = begin(n); i != end(n); i++) {
            count++;
        }
        return count;
    }

    float load_factor() const {
        return float(_size) / bucket_count();
    }

    size_type bucket(const Key & key) const {
        return _bucket(key);
    }

    std::pair<iterator, bool> insert(value_type && value) {
        HashNode* buffer = _find(value.first);

        if (buffer != nullptr) {
            return std::make_pair(iterator(this, buffer), false);
        }
        else {
            return std::make_pair(iterator(this, _insert_into_bucket(_bucket(value), std::move(value))), true);
        }

    }

    std::pair<iterator, bool> insert(const value_type & value) {
        HashNode* buffer = _find(value.first);

        if (buffer == nullptr) {
            return std::make_pair(iterator(this, _insert_into_bucket(_bucket(value), value_type(value))), true);
        }
        else {
            return std::make_pair(iterator(this, buffer), false);
        }
    }
    iterator find(const Key & key) {
        return iterator(this, _find(key));
    }

    T& operator[](const Key & key) {
        HashNode* buffer = _find(key);

        if (buffer == nullptr) {
            HashNode* newNode = _insert_into_bucket(_bucket(key), std::make_pair(key, T{}));
            return newNode->val.second;
        }
        return buffer->val.second;
    }

    iterator erase(iterator pos) {
        if (pos == end()) {
            return end();
        }

        HashNode* eraseNode = pos._ptr;
        size_type buck = _bucket(pos._ptr->val);
        HashNode* curr = _buckets[buck];

        if (eraseNode == curr) {
            auto i = iterator(this, eraseNode);
            i++;
            _buckets[buck] = eraseNode->next;
            if (eraseNode == _head) {
                _head = i._ptr;
            }
            delete eraseNode;
            _size--;
            return i;
        }

        while (curr != nullptr) {
            if (curr->next == eraseNode) {
                auto i = iterator(this, eraseNode);
                i++;
                curr->next = eraseNode->next;
                delete eraseNode;
                _size--;
                return i;
            }
            curr = curr->next;
        }

        return end();
    }

    size_type erase(const Key & key) {
        size_type buck = _bucket(key);
        HashNode* curr = _buckets[buck];

        if (_equal(key, curr->val.first)) {
            auto it = iterator(this, curr);
            it++;
            _buckets[buck] = curr->next;
            if (_head == curr) {
                _head = it._ptr;
            }
            delete curr;
            _size--;
            return 1;
        }
        while (curr->next != nullptr) {
            if (_equal(key, curr->next->val.first)) {
                HashNode* eraseNode = curr->next;
                curr->next = eraseNode->next;
                delete eraseNode;
                _size--;
                return 1;
            }
            curr = curr->next;
        }
        return 0;
    }

    template<typename KK, typename VV>
    friend void print_map(const UnorderedMap<KK, VV> & map, std::ostream & os);
};

template<typename K, typename V>
void print_map(const UnorderedMap<K, V> & map, std::ostream & os = std::cout) {
    using size_type = typename UnorderedMap<K, V>::size_type;
    using HashNode = typename UnorderedMap<K, V>::HashNode;

    for(size_type bucket = 0; bucket < map.bucket_count(); bucket++) {
        os << bucket << ": ";

        HashNode const * node = map._buckets[bucket];

        while(node) {
            os << "(" << node->val.first << ", " << node->val.second << ") ";
            node = node->next;
        }

        os << std::endl;
    }
}
