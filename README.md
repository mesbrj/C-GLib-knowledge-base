# GLib Knowledge Base - Educational Data Structures & Algorithms Demo

A comprehensive educational demonstration program showcasing fundamental data structures and algorithms through GLib's robust implementations. This project serves as a hands-on learning tool for computer science students and developers wanting to understand core algorithmic concepts in a practical context.

## Educational Objectives

This project demonstrates three fundamental concepts in computer science:

### 1. Dynamic Data Structures (Linked Lists)
**Academic Context**: Linear data structures and pointer manipulation  
**Algorithmic Concepts**: Sequential access, dynamic memory allocation, list traversal algorithms

### 2. Hash-Based Data Structures (Hash Tables) 
**Academic Context**: Associative arrays and hash function theory  
**Algorithmic Concepts**: Hash collision resolution, average O(1) lookup complexity, load factor optimization

### 3. Concurrent Programming Primitives (Thread-Safe Queues)
**Academic Context**: Operating systems, concurrent programming, and synchronization  
**Algorithmic Concepts**: Producer-consumer patterns, thread synchronization, deadlock prevention

## Features Demonstrated

### Double Linked Lists (GList)
**Computer Science Fundamentals**: [Doubly linked list Data Structure](https://en.wikipedia.org/wiki/Doubly_linked_list)

- **Dynamic Collections**: Demonstrates dynamic memory allocation and pointer-based data structures
- **List Operations**: Insertion (O(1) prepend, O(n) append), deletion (O(n)), traversal (O(n))
- **Sorting Algorithms**: In-place sorting with custom comparators - [Comparison Sorting](https://en.wikipedia.org/wiki/Comparison_sort)
- **Search Algorithms**: Linear search with custom predicates - [Linear Search](https://en.wikipedia.org/wiki/Linear_search)
- **Memory Management**: Automatic cleanup demonstrating [RAII principles](https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization)

**Key Learning Outcomes**:
- Understanding pointer manipulation and memory management
- Time complexity analysis of list operations
- Implementation of custom comparison functions
- Memory leak prevention techniques

### Hash Tables (GHashTable)
**Computer Science Fundamentals**: [Hash Table Data Structure](https://en.wikipedia.org/wiki/Hash_table)

- **Hash Functions**: Demonstrates string hashing and collision handling - [Hash Function Theory](https://en.wikipedia.org/wiki/Hash_function)
- **Associative Arrays**: Key-value mapping with O(1) average lookup complexity
- **Load Factor Management**: Automatic resizing and rehashing - [Hash Table Load Factor](https://en.wikipedia.org/wiki/Hash_table#Load_factor)
- **Memory Safety**: Custom destructors and automatic cleanup
- **Iteration Patterns**: Hash table traversal and filtering algorithms

**Key Learning Outcomes**:
- Understanding hash function design and collision resolution
- Analyzing average vs worst-case time complexity
- Implementing custom hash and equality functions
- Space-time tradeoff considerations

### Async Queues (GAsyncQueue)
**Computer Science Fundamentals**: [Concurrent Programming](https://en.wikipedia.org/wiki/Concurrent_computing)

- **Thread Safety**: Lock-free data structures and atomic operations - [Thread Safety](https://en.wikipedia.org/wiki/Thread_safety)
- **Producer-Consumer Pattern**: Classic synchronization problem - [Producer-Consumer Problem](https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem)
- **Blocking vs Non-blocking**: Different queue operation modes - [Blocking Queue](https://en.wikipedia.org/wiki/Blocking_queue)
- **Timeout Handling**: Robust concurrent programming with timeouts
- **Deadlock Prevention**: Safe multi-threaded communication - [Deadlock Prevention](https://en.wikipedia.org/wiki/Deadlock_prevention_algorithms)

**Key Learning Outcomes**:
- Understanding concurrent programming challenges
- Implementing thread-safe data structures
- Analyzing synchronization primitives
- Designing robust multi-threaded applications

## Architecture

The project is structured as a shared library (`libglib_features.so`) linked to a main executable (`test_menu`):

```
├── src/
│   ├── test_double_linked_lists.{c,h}  # GList demonstrations
│   ├── test_hash_tables.{c,h}          # GHashTable demonstrations  
│   ├── async_queue.{c,h}               # GAsyncQueue demonstrations
│   └── test_menu.c                     # Main interactive program
├── meson.build                         # Build configuration
└── README.md                           # This file
```

## Prerequisites

- **GLib 2.50+**: Core library for data structures and utilities
- **Meson**: Modern build system (optional)
- **GCC/Clang**: C compiler with C11 support
- **Linux/Unix**: Threading support (POSIX threads)
- **Docker**: For containerized deployment (optional)

### Installing Dependencies

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install libglib2.0-dev meson build-essential
```

**Fedora/RHEL:**
```bash
sudo dnf install glib2-devel meson gcc
```

**Arch Linux:**
```bash
sudo pacman -S glib2 meson gcc
```

**Docker:**
```bash
# Install Docker (Ubuntu/Debian)
sudo apt install docker.io
sudo systemctl start docker
sudo usermod -aG docker $USER
```

## Build and Run

### Method 1: Using Meson (Recommended)
```bash
git clone <repository-url>
cd C-GLib-knowledge-base

# Setup build directory
meson setup builddir

# Compile the project
meson compile -C builddir

# Run the interactive demo
./builddir/app_test
```

### Method 2: Using Docker (Containerized)
```bash
# Build the Docker image
./docker-build.sh

# Run the containerized demo
docker run -it glib-knowledge-base:latest

# Run specific demo (example: option 1)
echo '1' | docker run -i glib-knowledge-base:latest
```

### Method 3: Manual Build
```bash
# Build shared library
gcc -shared -fPIC -o libglib_features.so \
    src/test_double_linked_lists.c \
    src/test_hash_tables.c \
    src/test_async_queue.c \
    `pkg-config --cflags --libs glib-2.0`

# Build main executable
gcc -o app_test src/test_menu.c \
    -L. -lglib_features \
    `pkg-config --cflags --libs glib-2.0`

# Run with library path
LD_LIBRARY_PATH=. ./app_test
```

## Using the Application

The program provides an interactive menu with the following options:

1. **Double Linked Lists Demo**: Explore GList operations with person data
2. **Hash Tables Demo**: Learn GHashTable with student database
3. **Async Queues Demo**: Experience multi-threading with task queues
4. **Run All Demos**: Execute all demonstrations sequentially
5. **Show GLib Information**: Display GLib version and features
6. **Exit Program**: Clean exit

Each demonstration includes:
- **Automated Examples**: Pre-populated data showing core functionality
- **Interactive Sections**: User input to explore features hands-on
- **Educational Output**: Detailed explanations of operations
- **Memory Management**: Proper cleanup demonstrations

## Learning Objectives & Computer Science Curriculum Integration

### Data Structures Course Integration
- **Linear Data Structures**: Practical implementation of linked lists with real-world examples
- **Hash-Based Structures**: Understanding hash tables, collision resolution, and performance analysis
- **Dynamic Memory Management**: Proper allocation, deallocation, and memory leak prevention

### Algorithms Course Integration  
- **Sorting Algorithms**: Custom comparators and in-place sorting techniques
- **Search Algorithms**: Linear search implementation and optimization
- **Time Complexity Analysis**: Big-O notation practical examples and performance measurement

### Operating Systems Course Integration
- **Concurrent Programming**: Thread synchronization and communication
- **Process Synchronization**: Producer-consumer problem implementation
- **Deadlock Prevention**: Safe multi-threaded programming practices

### Software Engineering Course Integration
- **Memory Management**: RAII principles and automatic resource cleanup
- **API Design**: Well-designed interfaces and function signatures
- **Testing & Validation**: Comprehensive error handling and edge case management

## Academic References & Further Reading

### Foundational Computer Science Concepts
- [Data Structures and Algorithms](https://en.wikipedia.org/wiki/Data_structure) - Wikipedia overview
- [Algorithm Analysis](https://en.wikipedia.org/wiki/Analysis_of_algorithms) - Big-O notation and complexity theory
- [Abstract Data Types](https://en.wikipedia.org/wiki/Abstract_data_type) - Theoretical foundations

### Specific Data Structure Resources
- [MIT OpenCourseWare - Introduction to Algorithms](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/)
- [Stanford CS106B - Programming Abstractions](https://web.stanford.edu/class/cs106b/)
- [Algorithms, 4th Edition by Sedgewick & Wayne](https://algs4.cs.princeton.edu/home/) - Comprehensive algorithms textbook

### Concurrent Programming Resources
- [Operating System Concepts by Silberschatz](https://www.os-book.com/) - Classic OS textbook
- [Java Concurrency in Practice](https://jcip.net/) - Concurrency patterns (applicable to C)
- [The Art of Multiprocessor Programming](https://www.elsevier.com/books/the-art-of-multiprocessor-programming/herlihy/978-0-12-415950-1)

### C Programming and GLib Resources
- [GLib Reference Manual](https://docs.gtk.org/glib/) - Official documentation
- [The C Programming Language by Kernighan & Ritchie](https://en.wikipedia.org/wiki/The_C_Programming_Language) - Classic C reference
- [Expert C Programming by Peter van der Linden](https://books.google.com/books/about/Expert_C_Programming.html) - Advanced C concepts

## Implementation Examples with Algorithm Analysis

### Creating and Using a Double Linked List
**Time Complexity Analysis**: Insertion O(1) at head, O(n) at tail, Search O(n)
```c
GList *list = NULL;
Person *person = person_new("Alice", 25, "New York");

// Add to list - O(1) prepend, O(n) append
list = g_list_append(list, person);        // O(n) - traverses to end
list = g_list_prepend(list, another_person); // O(1) - adds at head

// Search - O(n) linear search
GList *found = g_list_find_custom(list, "Alice", find_by_name);

// Sort - O(n log n) using comparison-based sorting
list = g_list_sort(list, compare_by_age);

// Cleanup - O(n) traversal with custom destructor
g_list_free_full(list, (GDestroyNotify)person_free);
```

### Hash Table Operations  
**Time Complexity Analysis**: Average O(1) for insert/lookup/delete, Worst O(n) with poor hash function
```c
// Create with custom hash and equality functions
GHashTable *table = g_hash_table_new_full(
    g_str_hash,           // Hash function: string -> integer
    g_str_equal,          // Equality function for collision resolution
    g_free,               // Key destructor
    student_free          // Value destructor
);

// Insert - O(1) average case, O(n) worst case
g_hash_table_insert(table, g_strdup("alice"), student);

// Lookup - O(1) average case, hash function dependent
Student *found = g_hash_table_lookup(table, "alice");

// Iterate - O(n) where n is number of entries
g_hash_table_foreach(table, print_student, NULL);
```

### Thread-Safe Queue Operations
**Concurrency Analysis**: Lock-free operations, blocking vs non-blocking patterns
```c
GAsyncQueue *queue = g_async_queue_new();

// Producer thread - atomic enqueue operation
g_async_queue_push(queue, task);           // Thread-safe, non-blocking

// Consumer thread - blocking dequeue with synchronization
Task *task = g_async_queue_pop(queue);     // Blocks until item available

// Timeout operation - prevents indefinite blocking
Task *task = g_async_queue_timeout_pop(queue, timeout); // Bounded waiting
```

## Educational Assessment & Laboratory Exercises

### Suggested Laboratory Assignments

**Beginner Level (Data Structures)**:
1. Modify the linked list demo to implement a stack (LIFO) using GList
2. Create a queue (FIFO) implementation and compare performance with linked lists
3. Implement a binary search on a sorted linked list and measure performance

**Intermediate Level (Algorithms)**:
1. Implement different sorting algorithms (bubble, insertion, merge) and compare with GList's built-in sort
2. Create a hash table with different collision resolution strategies (chaining vs open addressing)
3. Analyze hash function quality by measuring collision rates with different data sets

**Advanced Level (Concurrent Programming)**:
1. Implement a thread pool using GAsyncQueue for task distribution
2. Create a bounded buffer problem solution with multiple producers and consumers
3. Implement a reader-writer lock using GLib's synchronization primitives

### Assessment Questions

**Data Structures Understanding**:
- What are the trade-offs between linked lists and arrays for different operations?
- How does the choice of hash function affect hash table performance?
- When would you choose a linked list over a hash table for data storage?

**Algorithm Analysis**:
- Calculate the time complexity of searching for an element in an unsorted linked list
- Explain why hash tables provide O(1) average lookup time but O(n) worst-case time
- Analyze the space complexity of the different data structures demonstrated

**Concurrent Programming**:
- Explain how the producer-consumer pattern prevents race conditions
- What are the benefits and drawbacks of blocking vs non-blocking queue operations?
- How does GAsyncQueue ensure thread safety without explicit locking?

## Testing and Validation

The demonstration includes comprehensive testing scenarios:

- **Memory Leak Detection**: All allocations are properly freed
- **Thread Safety**: Multiple producers and consumers
- **Error Handling**: Graceful handling of edge cases
- **Performance**: Demonstrates O(1) hash operations vs O(n) list operations

## Using This Project in Computer Science Coursework

### For Instructors

This project can be integrated into various computer science courses:

**CS1/CS2 (Introductory Programming)**:
- Demonstrate dynamic memory management and pointer concepts
- Show real-world applications of data structures
- Provide hands-on experience with professional C libraries

**Data Structures Course**:
- Compare theoretical concepts with practical implementations
- Analyze time and space complexity of operations
- Explore different data structure design trade-offs

**Algorithms Course**:
- Study sorting and searching algorithm implementations
- Analyze algorithmic complexity in practice
- Compare different algorithmic approaches

**Operating Systems Course**:
- Understand concurrent programming challenges
- Explore synchronization primitives and patterns
- Study producer-consumer problem implementations

**Software Engineering Course**:
- Examine API design and documentation practices
- Study memory management and resource cleanup
- Explore containerization and build systems

### For Students

**Study Approach**:
1. **Read the Code**: Start by understanding the data structure implementations
2. **Run Experiments**: Modify parameters and observe behavior changes  
3. **Measure Performance**: Add timing code to measure operation complexity
4. **Extend Functionality**: Implement additional features or algorithms
5. **Compare Implementations**: Write alternative implementations and compare

**Assignment Ideas**:
- Implement additional list operations (merge, split, rotate)
- Create custom hash functions and analyze their distribution properties
- Design producer-consumer scenarios with different workload patterns
- Write unit tests for all the implemented functions

## Contributing

Contributions are welcome. Areas for enhancement:

- Additional GLib data structures (GPtrArray, GTree, etc.)
- More complex threading examples
- Performance benchmarking
- Unit tests with GLib's testing framework
- Windows compatibility improvements

## Resources

- [IBM: Manage C data using the GLib collections](https://developer.ibm.com/tutorials/l-glib/)
- [Getting Started with GLib](https://remcokranenburg.com/2021/05/30/getting-started-with-glib.html)
- [Asynchronous operations in C with GObject](https://www.youtube.com/watch?v=rJS2TrkFIAs)

- [GLib Documentation](https://docs.gtk.org/glib/)
- [GLib Tutorial](https://developer.gnome.org/glib/stable/)

- [Meson Build System](https://mesonbuild.com/)
- [C Programming Best Practices](https://github.com/mcinglis/c-style)
