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
    # Shell
    zsh \
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

# ── Locale (UTF-8 required for zsh Unicode/Powerline chars) ──────────────────
RUN apt-get update && apt-get install -y locales \
 && locale-gen en_US.UTF-8 \
 && rm -rf /var/lib/apt/lists/*
ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8

# ── GitHub CLI ────────────────────────────────────────────────────────────────
RUN curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg \
      | dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg \
 && chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg \
 && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" \
      | tee /etc/apt/sources.list.d/github-cli.list \
 && apt-get update \
 && apt-get install -y gh \
 && rm -rf /var/lib/apt/lists/*

# ── zsh + oh-my-zsh ───────────────────────────────────────────────────────────
RUN chsh -s /usr/bin/zsh root
RUN git clone --depth=1 https://github.com/ohmyzsh/ohmyzsh.git /root/.oh-my-zsh

ENV SHELL=/usr/bin/zsh

WORKDIR /workspace
