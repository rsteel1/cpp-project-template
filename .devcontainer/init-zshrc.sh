#!/bin/bash
# Runs on host (initializeCommand) before container starts.
# On Mac/Linux/WSL: copies ~/.zshrc into .zshrc.local for mounting.
# Otherwise: copies .zshrc.baseline.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BASELINE="$SCRIPT_DIR/.zshrc.baseline"
OUTPUT="$SCRIPT_DIR/.zshrc.local"

if command -v uname >/dev/null 2>&1; then
  case "$(uname -s)" in
    Darwin|Linux)
      if [ -f "$HOME/.zshrc" ]; then
        cp "$HOME/.zshrc" "$OUTPUT"
        exit 0
      fi
      ;;
  esac
fi

cp "$BASELINE" "$OUTPUT"
