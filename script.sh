#!/bin/bash
for file in $(find bonus/ -type f -name "*_bonus.c" -o -name "*_bonus.h"); do
    sed -i 's/\(#include "\)\(.*\)\.h"/\1\2_bonus.h"/' "$file"
done
