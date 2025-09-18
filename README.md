# CMake RE Sanitizers examples and environments

This project is an example repository with predefined CMAKE_TOOLCHAIN_FILE and `cmake-re` Container environments enabling Sanitizers with full instrumentation.

1. [Download and Install `cmake-re`](https://tipi.build/documentation/0000-getting-started-cmake)
2. Pick a sanitizer toolchain and run it in `./02-fully-instrumented`
 - If the toolchains are missing, you can initialize the submodules `git submodule update --init`

## MSan - MemorySanitizer `-DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-clang20-msan.cmake`
Detects use of uninitialized memory, **features a fully-instrumented libc++ 🪄**.

* 👉 `cmake-re -S . -B build/msan -DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-clang20-msan.cmake`
* ️🔍 `cmake-re --build build/msan --run-test main`

## ASan + LSan + UBSan `-DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-clang20-asan-ubsan.cmake`
AdressSanitizer + LeakSanitizer detects use-after-free, overflow, use-after-scope...
UndefinedBehaviourSanitizer detects nullptr dereference, integer overflow

* 👉 ️`cmake-re -S . -B build/asan-ubsan -DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-clang20-asan-ubsan.cmake`
* ️🔍 `cmake-re --build build/asan-ubsan --run-test main`


## TSan - ThreadSanitizer `-DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-clang20-tsan.cmake`
* 👉 `cmake-re -S . -B build/asan-ubsan -DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-clang20-tsan.cmake`
️* 🔍 `cmake-re --build build/asan-ubsan --run-test main`


### Commands for Demo at CppCon2025
```sh
export TIPI_CACHE_CONSUME_ONLY=ON
export TIPI_CACHE_FORCE_ENABLE=OFF
```

## Prebuilt not fully instrumented
```sh
cd 01-prebuilt-package/
cmake-re -S . -B build/prebuilt-deps-release -DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-clang20-prebuilt.cmake -DCMAKE_BUILD_TYPE=Release
cmake-re --build build/prebuilt-deps-release --run-test main

cmake-re -S . -B build/prebuilt-deps -DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-clang20-prebuilt.cmake
cmake-re --build build/prebuilt-deps --run-test main
```

### Valgrind on pre-built
```sh
cd 01-prebuilt-package/
cmake-re -S . -B build/valgrind-prebuilt -DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-clang20-prebuilt.cmake -DCMAKE_TEST_LAUNCHER="/usr/bin/valgrind;--track-origins=yes"
cmake-re --build build/valgrind-prebuilt --run-test main 
```

## From source fully instrumented
```sh
cd 02-fully-instrumented/
cmake-re -S . -B build/fully-instrumented -DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-clang20-msan.cmake
cmake-re --build build/fully-instrumented --run-test main 

cmake-re -DCMAKE_BUILD_TYPE=Release -S . -B build/fully-instrumented-rel -DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-clang20-msan.cmake
cmake-re --build build/fully-instrumented-rel --run-test main 
```

### From source clang-tidy
```sh
cd 02-fully-instrumented/
cmake-re -S . -B build/tidy -DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-clang20-tidy.cmake
cmake-re --build build/tidy 
```


### From source asan + ubsan
```sh
cd 02-fully-instrumented/
cmake-re -S . -B build/asan-ubsan -DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-clang20-asan-ubsan.cmake
cmake-re --build build/asan-ubsan --run-test main
```

