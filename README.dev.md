# Developer notes

## CMake

The project has been initialized with a [CMakeLists.txt](CMakeLists.txt)-based
configuration for building with CMake:

```console
# change into the build directory
$ cd build/

# generate the build files
$ cmake ..

# build the project
$ cmake --build .

# install the project to <repo>/build/dist
$ cmake --install .

# run the program to see if it works
$ ./dist/bin/vulkan-sandbox
```

## `clang-format`

The file `.clang-format` contains an initial configuration for (automatic) formatting with [clang-format](https://clang.llvm.org/docs/ClangFormat.html). Run the formatter with e.g.:

```console
# dry run on main.c
$ clang-format -Werror --dry-run main.c

# format in place all *.c and *.h files under ./src
$ clang-format -i `find ./src -type f -name '*.[c|h]'`
```

## Dependencies

- GLFW, for making windows (assumed installed; see [https://www.glfw.org/](https://www.glfw.org/))
- Vulkan, for interacting with GPU (assumed installed; see [https://www.vulkan.org/](https://www.vulkan.org/))
- Handmade Math, for linear algebra (vendored, see [`/third_party`](/third_party) and [https://github.com/HandmadeMath/HandmadeMath](https://github.com/HandmadeMath/HandmadeMath))
