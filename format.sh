clang-format --version
find . -maxdepth 1 -name '*.h' -o -name '*.cpp' -exec unix2dos {} \;
find . -maxdepth 1 -name '*.h' -o -name '*.cpp'|xargs clang-format -i -style=file