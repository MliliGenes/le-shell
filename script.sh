#!/bin/bash

# This script finds all directories in the current location,
# then creates duplicates of all .c files with "_bonus.c" suffix

# Find all directories in the current location
for dir in */; do
    if [ -d "$dir" ]; then
        echo "Processing directory: $dir"
        
        # Find all .c files in the current directory
        find "$dir" -type f -name "*.c" | while read c_file; do
            # Create the new filename with _bonus.c suffix
            bonus_file="${c_file%.c}_bonus.c"
            
            # Copy the file
            cp "$c_file" "$bonus_file"
            
            echo "Duplicated: $c_file -> $bonus_file"
        done
    fi
done

echo "All C files have been duplicated with _bonus.c suffix."