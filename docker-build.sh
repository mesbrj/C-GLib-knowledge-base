#!/bin/bash
# Docker build and run script for GLib Knowledge Base

set -e

IMAGE_NAME="glib-knowledge-base"
TAG="latest"

echo "Building Docker image: ${IMAGE_NAME}:${TAG}"
echo "========================================"

# Build the Docker image
docker build -t "${IMAGE_NAME}:${TAG}" .

echo ""
echo "Build completed successfully!"
echo ""
echo "To run the container:"
echo "  docker run -it ${IMAGE_NAME}:${TAG}"
echo ""
echo "To run with custom input:"
echo "  echo '1' | docker run -i ${IMAGE_NAME}:${TAG}"
echo ""
echo "To get a shell in the container:"
echo "  docker run -it --entrypoint /bin/bash ${IMAGE_NAME}:${TAG}"
