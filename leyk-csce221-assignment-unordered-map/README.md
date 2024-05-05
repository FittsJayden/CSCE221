# Unordered Map

Have you ever wanted to associate two things together? For instance, you have an array of the names of your friends and an array of their birthdays in order to remember which birthday belongs to which friend. These two arrays are associated because each friend has one corresponding birthday. While many data structures including trees can be used to associate keys and values, hash tables are a popular choice since they support efficent `O(1)` insertion, deletion, and search. They accomplish this by transforming each key into a unique index through the use of a hash function. This index can be used to find the object in an array. Ideally, each index would correspond to a single key-value pair. This is called perfect hashing. In practice, it is very difficult to find a hash function which accomplishes perfect hashing. Most hashing datastructures permit collisions and resolve them through various methods. 

In this assignment, you will be parodying [`std::unordered_map`](https://en.cppreference.com/w/cpp/container/unordered_map) with [`UnorderedMap`](src/UnorderedMap.h). Unordered map is an associative container that stores key-value pairs and can search them by unique keys. Search, insertion, and removal of elements have average constant-time complexity. Internally, the elements are not sorted in any particular order, but organized into buckets. Which bucket an element is placed into depends entirely on the hash of its key. Keys with the same hash code appear in the same bucket. This allows fast access to individual elements, since once the hash is computed, it refers to the exact bucket the element is placed into. Each bucket has an assoicated list where all colliding key-value pairs are stored. This allows the map to achieve high load factors without a drastic reduction in performance. (This effect is commonly associated with closed-addressing.) `std::unordered_map` resizes automatically when the load factor exceedes a user-designated maximum load factor. It accomplishes this by increasing the number of buckets and rehashing the keys. To simplify the assignment, your map will have a fixed size.

## Table of Contents
[Getting Started](#getting-started)

[Assignment](#assignment)

- [Implement Unordered Map](#implement-unordered-map)

    - [Implement the following functions](#implement-the-following-functions)
    
- [Implement the Unordered Map's Iterator](#implement-the-unordered-maps-iterator)

- [Implement the Unordered Map's Local Iterator](#implement-the-unordered-maps-local-iterator)
    
- [Implement two hashing algorithms](#implement-two-hashing-algorithms)

- [Further Reading](#further-reading)

[Application of Unordered Maps](#application-of-unordered-maps)

[Run Tests](#run-tests)

[Main.cpp](#maincpp)

[Turn In](#turn-in)

## Getting started

Download this code by running the following command in the directory of your choice:
```sh
git clone git@github.com:tamu-edu-students/leyk-csce221-assignment-unordered-map.git && cd leyk-csce221-assignment-unordered-map
```
Open the code in your editor of choice. For instance, if you use VS Code:
```sh
code .
```
*Note:* On OSX you may need to enable the `code` command in VS Code with <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> and typing "shell command." You can select the option to install the command, and then the above command will work.

## Assignment

### Implement Unordered Map

Fundamentally, the `UnorderedMap` is a lot like a `List<std::pair<Key, Value>>` (see [your past Programming Assignment](https://github.com/tamu-edu-students/leyk-csce221-assignment-list)). One problem with `List` was that accessing a particular element was very slow because we had to start at the beginning and walk our way through until we found the element. `UnorderedMap` solves this problem by maintaining `_buckets` which is an array of size `_bucket_count` containing pointers to `HashNode`s. These nodes are like Linked List nodes.

How does marking certain nodes grant an advantage to the `UnorderedMap`? Well, these nodes are marked because they mark the start of a new hash code within the map. A hash code is the result of running `_hash()` (the `Hash` function) on a `key`. We often want to map the hash codes to an index within the `_buckets` array to determine which bucket the `key` should be hashed to. This is done via the provided `_range_hash` helper function. The performance is best when each bucket is very small. The average number of nodes in the buckets of the `UnorderedMap` is called the `load_factor`. Typically, the number of buckets changes to ensure that the `load_factor` does not exceed the `max_load_factor` (by default `1.0`). You do not need to increase the number of buckets in this manner.

In Computer Science literature, `UnorderedMap` is often referred to as a Hash Table by Chaining because multiple elements can fall into the same bucket, where they form a chain. This is typically represented as an array of independent Linked Lists. In C++, the suggested architecture is a single, long `List` with certain nodes "remembered" in the `_buckets` array. This is not required for the programming assignment. If it is easier for you, you can create separate `Lists`.

You are to implement the below `UnorderedMap` functions.

----

#### Implement the following functions:

```cpp
size_type _bucket(size_t code) const; // Private Helper
```

**Description:** Returns the index of the bucket for hash code `code`. You should consider utilizing the provided `_range_hash(size_type hash_code, size_type bucket_count)` function. You can call this `_bucket` function from within the  `size_type _bucket(const Key &key)` function, once you have a hash code for its `key`.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Used In:** `_bucket`, `_find`, [`insert`](https://en.cppreference.com/w/cpp/container/unordered_map/insert)

----

```cpp
size_type _bucket(const Key &key) const; // Private Helper
```

**Description:** Returns the index of the bucket for key `key`. Elements (if any) with keys equivalent to `key` are always found in this bucket. You can call this function from within the `size_type _bucket(const value_type &val)` function passing in the key value in `val` as the parameter.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Used In:** `erase`, [`bucket`](https://en.cppreference.com/w/cpp/container/unordered_map/bucket)

----

```cpp
size_type _bucket(const value_type &val) const; // Private Helper
```

**Description:** Returns the index of the bucket for value_type `val`. Elements (if any) with keys equivalent to the key value in `val` are always found in this bucket.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Used In:** `operator++`, [`insert`](https://en.cppreference.com/w/cpp/container/unordered_map/insert)

----

```cpp
HashNode*& _find(size_type code, size_type bucket, const Key & key); // Private Helper
```

**Description:** Starts with the nodes in bucket `bucket` and iterates forward until the key matches `key`, returning the node where the keys match. If no such match occurs, returns `nullptr`.

**Time Complexity:** Average case: *O(1)*, Worst case: *O(`size()`)*

**Used In:** `_find`, [`insert`](https://en.cppreference.com/w/cpp/container/unordered_map/insert)

----

```cpp
HashNode*& _find(const Key & key); // Private Helper
```

**Description:** Calls `_find(size_type code, size_type bucket, const Key & key) ` with the `code` from the `_hash` and the `bucket` from the `_bucket` functions called on `key` and `code` respectively.

**Time Complexity:** Average case: *O(1)*, Worst case: *O(`size()`)*

**Used In:** [`find`](https://en.cppreference.com/w/cpp/container/unordered_map/find), [`erase`](https://en.cppreference.com/w/cpp/container/unordered_map/erase)

----

```cpp
HashNode* _insert_into_bucket(size_type bucket, value_type && value); // Private Helper
```

**Description:** Inserts a new node with pair `value` at index `bucket` in the array of `_buckets` as the new bucket head. This is not necessarily the global head, but is the first node in the bucket. If the global `_head` is empty or the bucket index of `_head` is greater than `value`'s bucket index (`head` should be in the first populated bucket), the inserted node also becomes the new `_head`. The pair `value` should be moved into the node.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Used In:** [`insert`](https://en.cppreference.com/w/cpp/container/unordered_map/insert)

----

```cpp
void _move_content(UnorderedMap & src, UnorderedMap & dst); // Private Helper
```

**Description:** Moves the contents from map `src` into map `dst`. This is meant to be used in the move constructor and move assignment operator functions.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Used In:** [move constructor](https://en.cppreference.com/w/cpp/container/unordered_map/unordered_map), [move assignment operator](https://en.cppreference.com/w/cpp/container/unordered_map/operator=)

----

```cpp
explicit UnorderedMap(size_type bucket_count, const Hash & hash = Hash { }, const key_equal & equal = key_equal { }); // Constructor
```

**Description:** Constructs empty container. You must ensure that the `_bucket_count` is prime by calling the `next_greater_prime` function which will return the prime that is at least as large as `bucket_count`. If you do not have a prime `_bucket_count`, very bad things can happen to the efficiency of the `UnorderedMap`.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** constructor

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/unordered_map

----

```cpp
~UnorderedMap(); // Destructor
```

**Description:** Destructs the `UnorderedMap`. The destructors of the elements are called and the used storage is deallocated. Note, that if the elements are pointers, the pointed-to objects are not destroyed.

**Time Complexity:** *O(`size()`)* &ndash; Linear Time

**Test Names:** *used frequently*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/~unordered_map

----

```cpp
UnorderedMap(const UnorderedMap & other); // Copy Constructor
```

**Description:** Constructs the container with the copy of the contents of other, copies the load factor, the predicate, and the hash function as well.

**Time Complexity:** *O(`size()`)* &ndash; Linear Time

**Test Names:** constructor_copy

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/unordered_map

----

```cpp
UnorderedMap(UnorderedMap && other); // Move Constructor
```

**Description:** Constructs the container with the contents of other using move semantics.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** constructor_move

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/unordered_map

----

```cpp
UnorderedMap & operator=(const UnorderedMap & other); // Copy Assignment Operator
```

**Description:** Replaces the contents with a copy of the contents of other.

**Time Complexity:** *O(`size()` + `other.size()`)*

**Test Names:** operator_copy

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/operator=

----

```cpp
UnorderedMap & operator=(UnorderedMap && other); // Move Assignment Operator
```

**Description:** Replaces the contents with those of `other` using move semantics (i.e. the data in `other` is moved from `other` into this container). `other` is in a valid but unspecified state afterwards.

**Time Complexity:** *O(`size()`)* &ndash; Linear Time

**Test Names:** operator_move

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/operator=

----

```cpp
void clear() noexcept;
```

**Description:** Erases all elements from the container. After this call, [`size()`](https://en.cppreference.com/w/cpp/container/unordered_map/size) returns zero.

Invalidates any references, pointers, or iterators referring to contained elements. May also invalidate past-the-end iterators.

**Time Complexity:** *O(`size()`)* &ndash; Linear Time
**Test Names:** clear_and_empty

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/clear

----

```cpp
size_type size() const noexcept;
```

**Description:** Returns the number of elements in the container.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *used frequently*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/size

----

```cpp
bool empty() const noexcept;
```

**Description:** Checks if the container has no elements.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** clear_and_empty

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/empty

----

```cpp
size_type bucket_count() const noexcept;
```

**Description:** Returns the number of buckets in the container.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *used frequently*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/bucket_count

----

```cpp
const_iterator cbegin();
```

**Description:** Returns a const_iterator to the first element of the `UnorderedMap`.

If the `UnorderedMap` is empty, the returned iterator will be equal to [`end()`](https://en.cppreference.com/w/cpp/container/unordered_map/end). 

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *iterator*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/begin

----

```cpp
const_iterator cend();
```

**Description:** Returns a const_iterator to the element following the last element of the `UnorderedMap`.

This element acts as a placeholder; attempting to access it results in undefined behavior. 

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *iterator*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/end

----

```cpp
iterator begin();
```

**Description:** Returns an iterator to the first element of the `UnorderedMap`.

If the `UnorderedMap` is empty, the returned iterator will be equal to [`end()`](https://en.cppreference.com/w/cpp/container/unordered_map/end). 

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *iterator*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/begin

----

```cpp
iterator end();
```

**Description:** Returns an iterator to the element following the last element of the `UnorderedMap`.

This element acts as a placeholder; attempting to access it results in undefined behavior. 

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *iterator*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/end

----

```cpp
local_iterator begin(size_type n);
```

**Description:** Returns a local iterator to the first element of the bucket with index `n`.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *local_iterator*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/begin2

----

```cpp
local_iterator end(size_type n);
```

**Description:** Returns a local iterator to the element following the last element of the bucket with index `n`. This element acts as a placeholder, attempting to access it results in undefined behavior.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *local_iterator*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/end2

----

```cpp
size_type bucket_size(size_type n);
```

**Description:** Returns the number of elements in the bucket with index `n`.

**Time Complexity:** *O(elements in `n`)* &ndash; Linear Time

**Test Names:** *bucket_size*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/bucket_size

----

```cpp
float load_factor() const;
```

**Description:** Returns the average number of elements per bucket, that is, [`size()`](https://en.cppreference.com/w/cpp/container/unordered_map/size) divided by [`bucket_count()`](https://en.cppreference.com/w/cpp/container/unordered_map/bucket_count).

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *load_factor*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/load_factor

----

```cpp
size_type bucket(const Key & key) const;
```

**Description:** Returns the index of the bucket for key `key`. Elements (if any) with keys equivalent to `key` are always found in this bucket. The returned value is valid only for instances of the container for which [`bucket_count()`](https://en.cppreference.com/w/cpp/container/unordered_map/bucket_count) returns the same value.

The behavior is undefined if [`bucket_count()`](https://en.cppreference.com/w/cpp/container/unordered_map/bucket_count) is zero.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *bucket*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/bucket

----

```cpp
std::pair<iterator, bool> insert(value_type && value);
```

**Description:** Inserts `value` using move semantics. Returns a pair consisting of an iterator to the inserted element (or to the element that prevented the insertion) and a `bool` denoting whether the insertion took place (`true` if insertion happened, `false` if it did not).

**Time Complexity:** Average case: *O(1)*, Worst case: *O(`size()`)*

**Test Names:** *insert_and_move*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/insert

----

```cpp
std::pair<iterator, bool> insert(const value_type & value);
```

**Description:** Inserts `value` using copy semantics. Returns a pair consisting of an iterator to the inserted element (or to the element that prevented the insertion) and a `bool` denoting whether the insertion took place (`true` if insertion happened, `false` if it did not).

**Time Complexity:** Average case: *O(1)*, Worst case: *O(`size()`)*

**Test Names:** *insert_and_local_iterator*, *insert_and_global_iterator*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/insert

----

```cpp
iterator find(const Key & key);
```

**Description:** Finds an element with key equivalent to `key`. If no such element is found, past-the-end (see [`end()`](https://en.cppreference.com/w/cpp/container/unordered_map/end)) iterator is returned.

**Time Complexity:** Average case: *O(1)*, Worst case: *O(`size()`)*

**Test Names:** 

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/find

----

```cpp
T& operator[](const Key & key);
```

**Description:** Inserts a value_type object constructed in-place if the key does not exist. Returns a reference to the mapped value of the new element if no element with key `key` existed. Otherwise, returns a reference to the mapped value of the existing element whose key is equivalent to `key`.

**Time Complexity:** Average case: *O(1)*, Worst case: *O(`size()`)*

**Test Names:** *access_operator*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/operator_at

----

```cpp
iterator erase(iterator pos);
```

**Description:** Removes the element at `pos`. The iterator `pos` must be valid and dereferenceable. Thus the [`end()`](https://en.cppreference.com/w/cpp/container/unordered_map/end) iterator (which is valid, but is not dereferenceable) cannot be used as a value for `pos`. Returns an iterator following the last removed element.

**Time Complexity:** Average case: *O(1)*, Worst case: *O(`size()`)*

**Test Names:** *erase_iterator*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/erase

----

```cpp
size_type erase(const Key & key);
```

**Description:** Removes the element (if one exists) with the key equivalent to `key`. Returns the number of elements removed (`0` or `1`). 

**Time Complexity:** Average case: *O(1)*, Worst case: *O(`size()`)*

**Test Names:** *erase*

**Link:** https://en.cppreference.com/w/cpp/container/unordered_map/erase

----

**Provided Helper**

```cpp
template<typename K, typename V>
void print_map(const UnorderedMap<K, V> & map, std::ostream & os = std::cout)
```

**Description:** Prints everything in `map` to `os` (default: `std::cout`). This is useful for debugging purposes.

**Time Complexity:** Linear in the size of the container, i.e., the number of elements.

----

### Implement the Unordered Map's Iterator

This is an iterator to all of the nodes within the `UnorderedMap`. It should jump from one bucket to the next as it iterates along the `UnorderedMap`. It should visit every node within the bucket before moving to the next bucket.

----

```cpp
explicit basic_iterator(UnorderedMap const * map, HashNode *ptr) noexcept; // Private Helper
```

**Description:** Creates an `iterator` to the key-value pair belonging to the `HashNode` pointed to by `ptr`.

**Time Complexity:** *O(1)* &ndash; Constant Time

----

```cpp
basic_iterator();
```

**Description:** Creates a `basic_iterator` by default, where the pointer beloning to the iterator is `nullptr`.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *iterator*

----

```cpp
reference operator*() const;
```

**Description:** Return a reference to the key-value pair beloning to the `_node` owned by this iterator.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *iterator*

----

```cpp
pointer operator->() const;
```

**Description:** Return a pointer to the key-value pair beloning to the `_node` owned by this iterator.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *iterator*

----

```cpp
basic_iterator &operator++(); // Prefix Increment
```

**Description:** Change the `_node` to be the next `_node` in the `UnorderedMap`, even if that node is in a different bucket. Return a reference to the iterator after the change.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *iterator*

----

```cpp
basic_iterator operator++(int); // Postfix Increment
```

**Description:** Change the `_node` to be the next `_node` in the `UnorderedMap`, even if that node is in a different bucket, but return a copy of the `iterator` from before the change.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *iterator*, *insert_and_global_iterator*

----

```cpp
bool operator==(const basic_iterator &other) const noexcept;
```

**Description:** Test whether two `basic_iterator`s refer to the same `HashNode`.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *iterator*

----

```cpp
bool operator!=(const basic_iterator &other) const noexcept;
```

**Description:** Test whether two `basic_iterator`s refer to different `HashNode`s.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *insert_and_global_iterator*, *iterator*

----

### Implement the Unordered Map's Local Iterator

This is an iterator to the nodes within a single bucket of the `UnorderedMap`.

----

```cpp
explicit local_iterator( HashNode * node ) noexcept; // Private Helper
```

**Description:** Creates a `local_iterator` to the key-value pair belonging to the `HashNode` pointed to by `ptr` limited to the bucket `bucket` within `map`.

**Time Complexity:** *O(1)* &ndash; Constant Time

----

```cpp
local_iterator();
```

**Description:** Creates a `local_iterator` by default, where the pointer beloning to the local iterator is `nullptr`.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *local_iterator*

----

```cpp
reference operator*() const;
```

**Description:** Return a reference to the key-value pair beloning to the `_node` owned by this iterator.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *local_iterator*

----

```cpp
pointer operator->() const;
```

**Description:** Return a pointer to the key-value pair beloning to the `_node` owned by this iterator.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *local_iterator*, *insert_and_local_iterator*

----

```cpp
local_iterator & operator++(); // Prefix Increment
```

**Description:** Change the `_node` to be the next `_node` in the `UnorderedMap`. If that node is in a different bucket, change `_node` to be `nullptr`. Return a reference to the iterator after the change.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *local_iterator*

----

```cpp
local_iterator operator++(int); // Postfix Increment
```

**Description:** Change the `_node` to be the next `_node` in the `UnorderedMap`. If that node is in a different bucket, change `_node` to be `nullptr`. Return a copy of the `local_iterator` from before the change.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *local_iterator*, *insert_and_local_iterator*

----

```cpp
bool operator==(const local_iterator &other) const noexcept;
```

**Description:** Test whether two `local_iterator`s refer to the same `HashNode`.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *local_iterator*

----

```cpp
bool operator!=(const local_iterator &other) const noexcept;
```

**Description:** Test whether two `local_iterator`s refer to different `HashNode`s.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Test Names:** *local_iterator*, *insert_and_local_iterator*

----

### Implement two hashing algorithms

For this assignment, you are also tasked with designing 2 significant hashing algorithms, which could be used in a hash table. Each of the functions also provides some psuedocode.

----

`polynomial_rolling_hash size_t operator() (std::string const & str) const;`

**Description:** Returns the hash code resulting from hashing `str` using a polynomial rolling hash algorithm. To pass our test cases, you will need to have `b` be `19` and `m` be `3298534883309ul`.

**Time Complexity:** *O(`str.size()`)* &ndash; Linear Time

**Test Names:** *polynomial_hash*

**Link:** https://en.wikipedia.org/wiki/Rolling_hash

**Pseudocode:**

```
polynomial_rolling_hash(string str) :
    hash = 0
    p = 1
    for char in str do:
        hash += char * p
        p = (p * b) % m
    return hash
```

----

`fnv1a_hash size_t operator() (std::string const & str) const;`

**Description:** Returns the hash code resulting from hashing `str` using the fnv1a algorithm. To pass our test cases, you will need to have the `prime` be `0x00000100000001B3` and the `basis` be `0xCBF29CE484222325`.

**Time Complexity:** *O(`str.size()`)* &ndash; Linear Time

**Test Names:** *fnv1a_hash*

**Link:** https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function

**Pseudocode:**

```
fnv1a(string str) :
    hash = basis
    for char in str do:
        hash = hash XOR char
        hash = hash * prime
    return hash
```

In cpp, the XOR (exclusive or) operator is `^`. You can use it similarly to a mathematical operator such as `+`. For example

```
int a = 1; // bit representation 00000001
int b = 9; // bit representation 00001001
cout << (a ^ b) << endl; // the result is 8 (bit representation 00001000).
```
----

#### Further Reading
- [Hashing Data Structure - GeeksforGeeks](https://www.geeksforgeeks.org/hashing-data-structure/)
- [Hashing (Separate Chaining) - GeeksforGeeks](https://www.geeksforgeeks.org/hashing-set-2-separate-chaining/)
- [Hash table - Wikipedia](https://en.wikipedia.org/wiki/Hash_table)
- [Hash Table - Tutorialspoint](https://www.tutorialspoint.com/data_structures_algorithms/hash_data_structure.htm)
- Your textbook Chapter 5 Section 3 (page 196)

### Application of Unordered Maps

Unordered maps are perhaps the most commonly used data structure. You will encounter them all of the time in Software Engineering and should be familiar with using them. The specifics of implementation of Hash Tables (Unordered maps) will likely never appear again after this project.

In light of the difficulty of the project, you need only implement an `UnorderedMap`. If you want to see an application, the [`main.cpp`](src/main.cpp) creates an `UnorderedMap` called `map` with at least 30 buckets and gathers statistics about the map after inserting many random values.

## Run Tests

**First consult this guide: [`tests/README.md`](./tests/README.md)**

To run the tests, you need to rename [`main.cpp`](./src/main.cpp) or you need to rename the `int main` function within that file.

Execute the following commands from the `leyk-csce221-assignment-unordered-map` folder to accomplish what you need:

**Build all of the tests**
```sh
make -C tests -j12 build-all
```

**Run the test called `<test-name>`.** Replace `<test-name>` with the name of any `.cpp` file in the [`./tests/tests`](./tests/tests) folder.
```sh
make -C tests -j12 run/<test-name>
```

**Run every test** in the [`./tests/tests`](./tests/tests) folder.
```sh
make -C tests -j12 run-all -k
```

**Debugging tests** &ndash; For a detailed view, see [./tests/README.md](./tests/README.md).
```sh
make -C tests -j12 build-all -k
cd tests/build
gdb <test-name>
cd ../..
```
> Alex recommends you use `cgdb` which has the same commands as `gdb` but a better user interface. You can install it with `sudo apt install cgdb` on `WSL` or `brew install cgdb` on `MacOS` (provided you have [brew](https://brew.sh))

The first command builds the tests, the next enters the folder where the tests were build. The third invokes `gdb` (**use `lldb` if on Mac OSX**) which is used to debug the program by examining Segmentation Faults and running code line-by-line. Finally, the last command takes you back to the top-level directory.


## Incremental Testing:

To ensure the correctness of an insert, the bucket iterator has to be fully implemented so the test cases can compare the insertion location against the correct location. Completing `insert`, `bucket_iterator`, and the required helpers is fairly involved. We suggest the following order:
 
1. `constructor`: complete `bucket_count`, `constructor`, and `size`.
2. `insert_and_global_iterator`: complete `begin`, `end`, `insert`, `iterator::operator++(int)`, `iterator::operator->()`, and `iterator::operator!=`. (You may wish to complete the `_insert_into_bucket`, `_bucket`, and `_find` helpers for `insert`.)
3. `insert_and_local_iterator`: complete `bucket_size`, `begin(bucket)`, `end(bucket)`, `local_iterator::operator++(int)`, `local_iterator::operator!=`, and `local_iterator::operator->()`.
 
After passing these tests, you should be able to selectively complete the remaining methods.

## Main.cpp:

`main.cpp` is a test bench which compares four hash functions and their effect on the spatial distribution of values over the buckets. You can test the performance of your map on the following string hash functions:

1. Zero Hash: A hash function which always maps to zero.
2. First Character Hash: A hash function which returns the first element in the string.
3. Polynomial Rolling Hash: A variant of the polynomial hash which appears in the lecture notes. (Roughly based on a linear congruential generator.)
4. FNV1a: GCC uses a variant of FVN-1A.

This function will be applied to unique keys consisting of randomly generated animals:

```
Colorful Little Penguin
Luxurious Tiffany
Naturalistic Jackal
Embarrassed Squirrel Monkey
Invincible Epagneul Pont Audemer
```

The program will calculate the load-factor, load-variance, and plot the proportion of data in each bucket. A well-designed hash function should distribute the sample data uniformly over the buckets.

## Turn In

Submit the following file **and no other files** to Gradescope:
- [ ] [`UnorderedMap.h`](src/UnorderedMap.h)
- [ ] [`hash_functions.h`](src/hash_functions.h)
- [ ] [`hash_functions.cpp`](src/hash_functions.cpp)
- [ ] [`primes.h`](src/primes.h)
- [ ] [`primes.cpp`](src/primes.cpp)
