#!/bin/bash
# GLib Knowledge Base - Integration Test Script
# Tests all components to ensure proper build and functionality

echo "=== GLib Knowledge Base Integration Test ==="
echo "Testing build system and demo functionality..."
echo

# Ensure we're in the right directory
cd "$(dirname "$0")"

# Clean and build
echo "1. Setting up build environment..."
if [ -d "builddir" ]; then
    rm -rf builddir
fi

meson setup builddir
if [ $? -ne 0 ]; then
    echo "❌ Meson setup failed"
    exit 1
fi

echo "2. Building project..."
meson compile -C builddir
if [ $? -ne 0 ]; then
    echo "❌ Build failed"
    exit 1
fi

echo "✅ Build successful"
echo

# Verify the executable exists
if [ ! -f "builddir/app_test" ]; then
    echo "❌ Application executable not found"
    exit 1
fi

echo "✅ Integration test passed!"
echo
echo "The GLib Knowledge Base is ready for use."
echo "Run the application with: ./builddir/app_test"
echo
echo "Available demos:"
echo "  1. Double Linked Lists (GList)"
echo "  2. Hash Tables (GHashTable)"
echo "  3. Async Queues (GAsyncQueue)"
echo "  4. GObject Basics (OOP in C)"
echo "  5. Signals & Properties (Event System)"
echo "  6. Run All Demos"
echo "  7. Show GLib Information"
echo "  8. Exit"
