#!/bin/bash

ROOT_DIR=${1:-.}

find "$ROOT_DIR" -type f \( -name "*.c" -o -name "*.h" \) | while read -r file; do
    echo "Procesando: $file"

    vim -E -s "$file" << EOF
:Stdheader
:wq
EOF
done
