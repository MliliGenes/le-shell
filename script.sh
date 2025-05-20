#!/bin/bash

# Source directory (mandatory)
SRC_DIR="mandatory"
# Destination directory (bonus)
DST_DIR="bonus"

# Find all .c and .h files in SRC_DIR recursively
find "$SRC_DIR" \( -name "*.c" -o -name "*.h" \) | while read -r filepath; do
    # Get directory relative to SRC_DIR
    rel_dir=$(dirname "${filepath#$SRC_DIR/}")
    # Create same directory in DST_DIR
    mkdir -p "$DST_DIR/$rel_dir"
    
    # Get filename and extension
    filename=$(basename "$filepath")
    base="${filename%.*}"
    ext="${filename##*.}"
    
    # New filename with _bonus suffix
    newfile="${base}_bonus.${ext}"
    
    # Copy and rename
    cp "$filepath" "$DST_DIR/$rel_dir/$newfile"
done
