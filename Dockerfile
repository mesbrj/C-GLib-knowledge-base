# Multi-stage Dockerfile for GLib Knowledge Base Demo
# Stage 1: Build environment
FROM python:3.11-slim as builder

# Install system dependencies for building
RUN apt-get update && apt-get install -y \
    build-essential \
    libglib2.0-dev \
    pkg-config \
    git \
    && rm -rf /var/lib/apt/lists/*

# Install Python build tools
RUN pip install --no-cache-dir meson ninja

# Set working directory
WORKDIR /build

# Copy source code
COPY . .

# Configure and build the project
RUN meson setup builddir --prefix=/usr/local
RUN meson compile -C builddir

# Install to a staging directory
RUN DESTDIR=/build/install meson install -C builddir

# Stage 2: Runtime environment
FROM python:3.11-slim

# Install only runtime dependencies
RUN apt-get update && apt-get install -y \
    libglib2.0-0 \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean

# Create application user for security
RUN groupadd -r glib && useradd -r -g glib -d /app -s /sbin/nologin glib

# Set working directory
WORKDIR /app

# Copy built binaries and libraries from builder stage
COPY --from=builder /build/install/usr/local/bin/app_test /app/
COPY --from=builder /build/install/usr/local/lib/libglib_features.so /usr/local/lib/

# Set library path
ENV LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

# Update shared library cache
RUN ldconfig

# Change ownership of the app directory
RUN chown -R glib:glib /app

# Switch to non-root user
USER glib

# Set the entry point
ENTRYPOINT ["/app/app_test"]

# Add labels for documentation
LABEL maintainer="GLib Knowledge Base Demo"
LABEL description="Containerized GLib demonstration program"
LABEL version="1.0.0"
