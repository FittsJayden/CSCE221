# Sorting

The goal of this assignment is to implement the `O(n^2)` sorting algorithms using a similar interface to `std::sort`. These algorithms can be used to sort data structures which implement random access iterators. This includes the [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) data structure you completed in the last assignment.

## Getting Started
Download this code by running the following command in the directory of your choice:
```sh
git clone git@github.com:tamu-edu-students/leyk-csce221-assignment-sorting.git && cd leyk-csce221-assignment-sorting
```

Open the code in your editor of choice. For instance, if you use VS Code:
```sh
code .
```
*Note:* On OSX you may need to enable the `code` command in VS Code with <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> and typing "shell command." You can select the option to install the command, and then the above command will work.

## Assignment
### Implement Sorting Algorithms
You are to implement `bubble_sort()`, `insertion_sort()`, and `selection_sort()` using iterators. 

**HINT:** Implement `swap()` first. This is going to be used in all the sorting algorithms. Move operations are your friend.

#### You must implement the following functions:

`void swap(T & a, T & b) noexcept`

**Description**: swaps the position of two elements 

**Time Complexity**: *O(1)*

**Used in**: *bubble_comparisons*, *bubble_sorts*, *insertion_comparisons*, *insertion_sorts*, *selection_sorts*, *sorts_efficient*, *swap*

----

`void bubble(RandomIter begin, RandomIter end, Comparator comp = Comparator{})`

**Description**: Sorts elements in the range \[`begin`, `end`) using the bubble sort algorithm. This sort should be optimized so the runtime function is about 1/2 n<sup>2</sup> in the worst case. Compare elements using `comp`, which is std::less by default.

**Time Complexity**: *O(n<sup>2</sup>)*

**Used in**: *bubble_comparisons*, *bubble_sorts*, *sorts_efficient*

----

`void insertion(RandomIter begin, RandomIter end, Comparator comp = Comparator{})`

**Description**: Sorts elements in the range \[begin, end) using the insertion sort algorithm. Compare elements using `comp`, which is std::less by default.

**Time Complexity**: *O(n<sup>2</sup>)*

**Used in**: *insertion_comparisons*, *insertion_sorts*, *sorts_efficient*

----

`void selection(RandomIter begin, RandomIter end, Comparator comp = Comparator{})`

**Description**: Sorts elements in the range \[begin, end) using the selection sort algorithm. Compare elements using `comp`, which is std::less by default.

**Time Complexity**: *O(n<sup>2</sup>)*

**Used in**: *selection_comparisons*, *selection_sorts*, *sorts_efficient*

----

An additional 5 points is earned if you do not allocate memory during any of the sorting algorithms. You should not need to do this, so you can almost consider these points as "*free*".

It may be helpful for you to consult:
- Reference for Iterators: https://en.cppreference.com/w/cpp/iterator/iterator
- Reference for Sorts: https://en.cppreference.com/w/cpp/algorithm/sort
- Visualization of Sorting Algorithms: https://pulchroxloom.github.io/visualizing_sorts/
- Videos of Sorting Algorithms Visualized: https://youtu.be/kPRA0W1kECg

### Run The Tests

**First consult this guide: [`tests/README.md`](./tests/README.md)**

To run the tests, you need to rename [`main.cpp`](./src/main.cpp) or you need to rename the `int main` function within that file.

Execute the following commands from the `sorting-vectors` folder to accomplish what you need:

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

## Input File Contents
To help test your code we are providing various input files. 
- Files with the `ordered` prefix consist of numbers in sequence 1, 2, ... , n
- Files with the `rand` prefix consist of non-duplicate random numbers in the range [1, n]
- Files with the `randdup` prefix consist of random numbers in the range [1, n]. There are some duplicate values
- Files with the `reverse` prefix consist of numbers in sequence n, n-1, ... , 1

## Helper program to generate sorted data:

To complete the report, you will need to benchmark the number of comparisons performed by each sorting algorithm.
You can do this manually by compiling and executing `main` but we've written a script to automatically collect this
data into a file.

To run it, execute the following commands on MacOS or WSL:
```
[#] g++ -std=c++17 -o src/main src/main.cpp
[#] bash generate_csv.bash > sorting_data.csv
```

## Turn In
Submit the modified `sorting.h` to Gradescope. In general, submit everything except `main.cpp`.
