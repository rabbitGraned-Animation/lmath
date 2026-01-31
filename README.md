# lmath-dev

«lmath» is a lightweight C++ library of vectors, matrix, quats, and other math operations for computer graphics.

The library provides minimal abstraction without hidden allocations, is optimized for high performance, and contains no runtime checks.

## Get-Started

«lmath» is a header-only library, so all you have to do is add the appropriate headers files to your project.

### Requirements:

- C++20 STL implementation
- CMake 3.14 (for build tests)

> The tests were debugged using LLVM-based compilers.

**Run CTest in CMake**:
```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
ctest -v
```
or compile/run each test manually to see the detailed output.

You can test the library's speed using the provided benchmark. To do this, include it in the CMake build or assemble it manually.

**GCC/LLVM**:
```
bench.cc -o bench -std=c++20 -O2 -I path-to-lmath
```

## Docs

Detailed documentation is provided in the [Wiki](https://github.com/rabbitGraned-Animation/lmath/wiki/Docs). There you will find information about the functions and the main APIs.

Keep the contracts and avoid undefined behaviour. More detailed: [C&UB](https://github.com/rabbitGraned-Animation/lmath/wiki/Contracts-&-Undefined-Behavior).

## License

BSD 3-Clause License. Copyright © rabbitGraned Animation.
