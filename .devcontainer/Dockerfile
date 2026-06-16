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
    # Include What You Use — finds missing/unused #includes
    iwyu \
    # CMake (latest via pip is cleaner than apt on Ubuntu)
    python3-pip \
    # Git and utilities
    git \
    curl \
    wget \
    ca-certificates \
    # Shell
    zsh \
    # Locale (UTF-8 required for zsh Unicode/Powerline chars)
    locales \
    # Valgrind for memory checking (ASan alternative when needed)
    valgrind \
    # Useful for inspecting assembly output
    binutils \
 && locale-gen en_US.UTF-8 \
 && rm -rf /var/lib/apt/lists/*

ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8

# ── CMake + cpplint ───────────────────────────────────────────────────────────
RUN pip3 install cmake cpplint --break-system-packages

# ── IWYU helper scripts (not shipped in the apt package) ─────────────────────
RUN curl -fsSL https://raw.githubusercontent.com/include-what-you-use/include-what-you-use/clang_17/iwyu_tool.py \
      -o /usr/local/bin/iwyu_tool.py \
 && curl -fsSL https://raw.githubusercontent.com/include-what-you-use/include-what-you-use/clang_17/fix_includes.py \
      -o /usr/local/bin/fix_includes.py \
 && chmod +x /usr/local/bin/iwyu_tool.py /usr/local/bin/fix_includes.py

# ── Symlink clang tools so they're on PATH without version suffix ─────────────
RUN update-alternatives --install /usr/bin/clang++      clang++      /usr/bin/clang++-17      100 \
 && update-alternatives --install /usr/bin/clang        clang        /usr/bin/clang-17        100 \
 && update-alternatives --install /usr/bin/clangd       clangd       /usr/bin/clangd-17       100 \
 && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-17 100 \
 && update-alternatives --install /usr/bin/clang-tidy   clang-tidy   /usr/bin/clang-tidy-17   100 \
 && update-alternatives --install /usr/bin/lldb         lldb         /usr/bin/lldb-17         100

ENV CC=clang
ENV CXX=clang++

# ── GitHub CLI ────────────────────────────────────────────────────────────────
RUN curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg \
      | dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg \
 && chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg \
 && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" \
      | tee /etc/apt/sources.list.d/github-cli.list \
 && apt-get update \
 && apt-get install -y gh \
 && rm -rf /var/lib/apt/lists/*

# ── Node.js + Claude CLI ─────────────────────────────────────────────────────
RUN curl -fsSL https://deb.nodesource.com/setup_22.x | bash - \
 && apt-get install -y nodejs \
 && rm -rf /var/lib/apt/lists/*
RUN npm install -g @anthropic-ai/claude-code

# ── zsh + oh-my-zsh ───────────────────────────────────────────────────────────
RUN chsh -s /usr/bin/zsh root \
 && git clone --depth=1 https://github.com/ohmyzsh/ohmyzsh.git /root/.oh-my-zsh

ENV SHELL=/usr/bin/zsh

WORKDIR /workspace
