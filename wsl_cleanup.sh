#!/bin/bash
echo "=== all TileHexaV3 processes ==="
ps aux | grep -i TileHexaV3 | grep -v grep

echo "=== killing all TileHexaV3 processes ==="
pkill -f "build-ubuntu/TileHexaV3" 2>&1

sleep 1
echo "=== after kill ==="
ps aux | grep -i TileHexaV3 | grep -v grep
echo "done"
