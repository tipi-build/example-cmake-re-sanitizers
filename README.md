
```sh
git submodule add https://github.com/tipi-build/environments.git environments/
```

```sh
export TIPI_CACHE_CONSUME_ONLY=ON
export TIPI_CACHE_FORCE_ENABLE=OFF
export RBE_service=glass.cluster.engflow.com:443
export RBE_tls_client_auth_key=$HOME/engflow-mTLS-glass/engflow.key
export RBE_tls_client_auth_cert=$HOME/engflow-mTLS-glass/engflow.crt
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
cmake-re -S . -B build/tidy -DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-clang20-tidy.cmake
cmake-re --build build/tidy 
```

