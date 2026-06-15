FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive

# ── Core toolchain ────────────────────────────────────────────────────────────
RUN apt-get update && apt-get install -y \
    # Build essentials
    build-essential \
    ninja-build \
    pkg-config \
    # Clang 17 (full suite: compiler, clangd, clang-format, clang-tidy, sanitisers)
    clang-17 \
    clangd-17 \
    clang-format-17 \
    clang-tidy-17 \
    lldb-17 \
    # GCC as a secondary compiler (useful for catching compiler-specific warnings)
    g++ \
    # CMake (latest via pip is cleaner than apt on Ubuntu)
    python3-pip \
    # Git and utilities
    git \
    curl \
    wget \
    ca-certificates \
    # Valgrind for memory checking (ASan alternative when needed)
    valgrind \
    # Useful for inspecting assembly output
    binutils \
    && rm -rf /var/lib/apt/lists/*

# ── CMake (recent version) ────────────────────────────────────────────────────
RUN pip3 install cmake --break-system-packages

# ── Symlink clang tools so they're on PATH without version suffix ─────────────
RUN update-alternatives --install /usr/bin/clang++     clang++     /usr/bin/clang++-17     100 \
 && update-alternatives --install /usr/bin/clang       clang       /usr/bin/clang-17       100 \
 && update-alternatives --install /usr/bin/clangd      clangd      /usr/bin/clangd-17      100 \
 && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-17 100 \
 && update-alternatives --install /usr/bin/clang-tidy  clang-tidy  /usr/bin/clang-tidy-17  100 \
 && update-alternatives --install /usr/bin/lldb        lldb        /usr/bin/lldb-17        100

# ── Default to clang++ ────────────────────────────────────────────────────────
ENV CC=clang
ENV CXX=clang++

# ── Non-root user (matches VSCode devcontainer convention) ────────────────────
ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=1000

RUN groupadd --gid $USER_GID $USERNAME \
 && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
 && apt-get update \
 && apt-get install -y sudo \
 && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers \
 && rm -rf /var/lib/apt/lists/*

USER $USERNAME
WORKDIR /workspace
