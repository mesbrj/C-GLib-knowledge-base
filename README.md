# GLib - Educational Knowledge Base: Data Structures & Algorithms, Operating Systems, Software Engineering

A Educational demonstration program showcasing data structures & algorithms, operating systems concepts, and software engineering principles through GLib's robust implementations. This project is designed to provide practical, hands-on experience with core computer science concepts, implemented in C. It covers dynamic data structures, hash tables, concurrent programming primitives, object-oriented programming in C, and event-driven programming patterns.

## Current Project Status

- Double Linked Lists (GList) with comprehensive demos
- Hash Tables (GHashTable) with student database examples  
- Async Queues (GAsyncQueue) with multi-threading demos
- GObject basics (Object-oriented programming in C)
- Signals & Properties (Event-driven programming)
- Interactive menu system with all 5 demo modules
- Docker containerization
- Educational documentation

## Educational Objectives

This project demonstrates five fundamental concepts in computer science:

### 1. Dynamic Data Structures (Linked Lists)
**Academic Context**: Linear data structures and pointer manipulation  
**Algorithmic Concepts**: Sequential access, dynamic memory allocation, list traversal algorithms

### 2. Hash-Based Data Structures (Hash Tables) 
**Academic Context**: Associative arrays and hash function theory  
**Algorithmic Concepts**: Hash collision resolution, average O(1) lookup complexity, load factor optimization

### 3. Concurrent Programming Primitives (Thread-Safe Queues)
**Academic Context**: Operating systems, concurrent programming, and synchronization  
**Algorithmic Concepts**: Producer-consumer patterns, thread synchronization, deadlock prevention

### 4. Object-Oriented Programming in C (GObject System)
**Academic Context**: OOP principles, design patterns, and software architecture  
**Programming Concepts**: Inheritance, polymorphism, encapsulation, type systems, memory management

### 5. Event-Driven Programming (Signals and Properties)
**Academic Context**: Observer pattern, event-driven architecture, and reactive programming  
**Programming Concepts**: Signal/slot mechanism, property change notifications, interface design

## Interactive Program Features and academic context:

**[Double-Linked-Lists](documentation/double_linked_lists.md)** (GList)
**[Hash-Tables](documentation/hash_tables.md)** (GHashTable)
**[Async-Queues](documentation/async_queue.md)** (GAsyncQueue)
**[GObject-Basics](documentation/gobject_basics.md)** (Object-Oriented Programming in C)
**[Signals-Properties](documentation/signals_properties.md)** (Event-Driven Programming)

The code examples (app and above documentation links) demonstrate usage patterns for some GLib features:

1. **GList**: Custom data structures, sorting, searching, and performance optimization
2. **GHashTable**: Multi-type storage, custom hash functions, and configuration management
3. **GAsyncQueue**: Producer-consumer patterns, load balancing, and priority queues
4. **GObject**: Complete inheritance hierarchy with virtual methods and polymorphism
5. **Signals & Properties**: Event-driven sensor simulation with reactive programming

Each example shows applications that include proper memory management, error handling, and performance considerations.

## Architecture

The project is structured as a shared library (`libglib_features.so`) linked to a main executable (`app_test`):

```
├── src/
│   ├── test_double_linked_lists.{c,h}  # GList demonstrations
│   ├── test_hash_tables.{c,h}          # GHashTable demonstrations  
│   ├── test_async_queue.{c,h}          # GAsyncQueue demonstrations
│   ├── test_gobject_basics.{c,h}       # GObject OOP demonstrations
│   ├── test_signals_properties.{c,h}   # GObject signals/properties demonstrations
│   └── test_menu.c                     # Main interactive program
├── meson.build                         # Build configuration
├── Dockerfile                          # Container configuration
├── docker-build.sh                     # Container build script
└── README.md                           # This file
```

## Prerequisites

- **GLib 2.50+**: Core library for data structures and utilities
- **Meson**: Modern build system (recommended)
- **GCC/Clang**: C compiler with C11 support
- **Linux/Unix**: Threading support (POSIX threads)
- **Docker / podman**: For containerized deployment (recommended)

### Installing Dependencies

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install libglib2.0-dev libgobject-2.0-dev meson build-essential
```

**Fedora/RHEL:**
```bash
sudo dnf install glib2-devel gobject-introspection-devel meson gcc
```

**Arch Linux:**
```bash
sudo pacman -S glib2 gobject-introspection meson gcc
```

**Docker / Podman:**
```bash
# Install Docker (Ubuntu/Debian)
sudo apt install docker.io podman
# Start Docker service
sudo systemctl enable docker
sudo systemctl start docker
sudo usermod -aG docker $USER
```

## Build and Run

### Method 1: Using Meson (Recommended)
```bash
git clone https://github.com/mesbrj/C-GLib-knowledge-base.git
cd C-GLib-knowledge-base
# Install Meson and Ninja build tools
pip install --user meson ninja

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
# Alternatively, run with podman
podman run -it glib-knowledge-base:latest

# Run specific demo (example: option 1)
echo '1' | docker run -i glib-knowledge-base:latest
# Or for podman
echo '1' | podman run -i glib-knowledge-base:latest
```

### Method 3: Manual Build
```bash
# Build shared library
gcc -shared -fPIC -o libglib_features.so \
    src/test_double_linked_lists.c \
    src/test_hash_tables.c \
    src/test_async_queue.c \
    src/test_gobject_basics.c \
    src/test_signals_properties.c \
    `pkg-config --cflags --libs glib-2.0 gobject-2.0`

# Build main executable
gcc -o app_test src/test_menu.c \
    -L. -lglib_features \
    `pkg-config --cflags --libs glib-2.0 gobject-2.0`

# Run with library path
LD_LIBRARY_PATH=. ./app_test
```

## Using the Application

The program provides an interactive menu with the following options:

1. **Double Linked Lists Demo**: Explore GList operations with person data
2. **Hash Tables Demo**: Learn GHashTable with student database
3. **Async Queues Demo**: Experience multi-threading with task queues
4. **GObject Basics Demo**: Discover object-oriented programming in C
5. **Signals and Properties Demo**: Learn event-driven programming patterns
6. **Run All Demos**: Execute all demonstrations sequentially
7. **Show GLib Information**: Display GLib version and features
8. **Exit Program**: Clean exit

Each demonstration includes:
- **Automated Examples**: Pre-populated data showing core functionality
- **Interactive Sections**: User input to explore features hands-on
- **Educational Output**: Detailed explanations of operations
- **Memory Management**: Proper cleanup demonstrations

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

**Advanced Level (Object-Oriented Programming in C)**:
1. Design and implement a complete class hierarchy using GObject (Vehicle -> Car -> SportsCar)
2. Create a plugin system using GObject interfaces and dynamic loading
3. Implement the Model-View-Controller pattern using GObject signals and properties
4. Build a simple state machine using GObject and signals for state transitions

**Expert Level (Event-Driven Architecture)**:
1. Design a messaging system with multiple event types and priority handling
2. Implement an undo/redo system using the Command pattern with GObject
3. Create a reactive programming framework using GObject signals and property bindings
4. Build a distributed event system with serialization and network communication

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

**Object-Oriented Programming**:
- How does GObject implement inheritance in C without native language support?
- What are the advantages and disadvantages of reference counting vs garbage collection?
- Explain the role of virtual function tables (vtables) in polymorphism implementation
- How does the GObject type system enable runtime type checking and introspection?

**Event-Driven Programming**:
- Compare and contrast the Observer pattern with traditional callback mechanisms
- How do signals provide loose coupling between objects in complex applications?
- What are the performance implications of signal emission vs direct method calls?
- Explain how property change notifications can be used to implement reactive UIs

## Testing and Validation

The demonstration includes comprehensive testing scenarios:

- **Memory Leak Detection**: All allocations are properly freed
- **Thread Safety**: Multiple producers and consumers
- **Error Handling**: Graceful handling of edge cases
- **Performance**: Demonstrates O(1) hash operations vs O(n) list operations

## Using This Project in Academic Context

**Introductory Programming**:
- Demonstrate dynamic memory management and pointer concepts
- Show real-world applications of data structures
- Provide hands-on experience with professional C libraries

**Data Structures**:
- Compare theoretical concepts with practical implementations
- Analyze time and space complexity of operations
- Explore different data structure design trade-offs

**Algorithms**:
- Study sorting and searching algorithm implementations
- Analyze algorithmic complexity in practice
- Compare different algorithmic approaches

**Operating Systems**:
- Understand concurrent programming challenges
- Explore synchronization primitives and patterns
- Study producer-consumer problem implementations

**Software Engineering**:
- Examine API design and documentation practices
- Study memory management and resource cleanup
- Explore containerization and build systems

### Study Approach

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
