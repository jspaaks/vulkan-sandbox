[![Copier](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/copier-org/copier/master/img/badge/badge-grayscale-inverted-border-orange.json)](https://github.com/copier-org/copier)

# vulkan-sandbox

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

Should output something like:

```text
-- test compile definitions
   DEBUG compile definition has been defined.

-- test wether math library was linked
   sqrt(144) = 12.000000

-- test c2x / c23 features
   0 1 2 3 4

-- test own library
   divide(2, 3) = 0
   multiply(2, 3) = 6

-- test external library
   add(2, 3) = 5
   subtract(2, 3) = -1
```

## Testing

Building and running the tests requires that [Criterion](https://github.com/Snaipe/Criterion) is
installed on the system, e.g. with

```console
$ sudo apt install libcriterion-dev
```

Run the tests with

```console
$ ./dist/bin/test_operations -j1 --verbose
```

 or simply, with:

```console
$ ctest
```

The CMake variable `OPERATIONS_BUILD_TESTING` can be used to build the
tests.

- When this project is the top project, `OPERATIONS_BUILD_TESTING` inherits the value of
  CTest's `BUILD_TESTING`, which is set to ON by default.
- When this project is not the top project but instead it is used as a dependency to a parent
  project, the default is to not build the tests. However, building the tests is still possible by
  setting the `OPERATIONS_BUILD_TESTING` to `ON`, e.g like so:

```console
$ cmake -DOPERATIONS_BUILD_TESTING=ON ..
```

## `clang-format`

The file `.clang-format` contains an initial configuration for (automatic) formatting with [clang-format](https://clang.llvm.org/docs/ClangFormat.html). Run the formatter with e.g.:

```console
# dry run on main.c
$ clang-format -Werror --dry-run main.c

# format in place all *.c and *.h files under ./src
$ clang-format -i `find ./src -type f -name '*.[c|h]'`
```

## Acknowledgements

_This project was initialized using [Copier](https://pypi.org/project/copier) and the [copier-template-for-c-projects](https://github.com/jspaaks/copier-template-for-c-projects)._
