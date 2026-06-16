#!/bin/bash
# Wires caveman hooks inside the devcontainer so claude CLI picks them up.
# HOST_HOME is set via remoteEnv in devcontainer.json (= $HOME on the host).
# ~/.claude is bind-mounted to /root/.claude; we symlink HOST_HOME/.claude →
# /root/.claude so that hook command paths (written with host HOME) resolve here.
set -e

if [ -z "$HOST_HOME" ]; then
  echo "caveman: HOST_HOME not set, skipping"
  exit 0
fi

CAVEMAN_INSTALL=$(ls /root/.claude/plugins/cache/caveman/caveman/*/src/hooks/install.sh 2>/dev/null | head -1)
if [ -z "$CAVEMAN_INSTALL" ]; then
  echo "caveman: plugin not found in /root/.claude/plugins/cache, skipping"
  exit 0
fi

mkdir -p "$HOST_HOME"
ln -sfn /root/.claude "$HOST_HOME/.claude"

HOME="$HOST_HOME" bash "$CAVEMAN_INSTALL"
