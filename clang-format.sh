#!/usr/bin/bash

cd -- "$(find ~/ -type d -name cpplox | head -1)"
config_file=".clang-format"


if ! [ -f "$config_file" ]; then
    clang-format -style=google -dump-config > "$config_file"
fi


find . \( -name '*.cpp' -o -name '*.hpp' \) -exec clang-format --style=file -i {} +

rm "$config_file"

echo "Formatting completed."