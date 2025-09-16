
```sh
git submodule add https://github.com/tipi-build/environments.git environments/
```

```sh
export TIPI_CACHE_CONSUME_ONLY=ON
export TIPI_CACHE_FORCE_ENABLE=OFF
export RBE_service=glass.cluster.engflow.com:443
export RBE_tls_client_auth_key=$HOME/engflow-mTLS-glass/engflow.key
export RBE_tls_client_auth_cert=$HOME/engflow-mTLS-glass/engflow.crt
#
#
#export TIPI_CONTAINER_BUILD_ADDITIONAL_PARAMETERS="\
#--build-context environments=$PWD/environments \
#--build-arg TIPI_CACHE_CONSUME_ONLY=${TIPI_CACHE_CONSUME_ONLY} \
#--build-arg TIPI_CACHE_FORCE_ENABLE=${TIPI_CACHE_FORCE_ENABLE} \
#--build-arg RBE_service=${RBE_service} \
#--secret id=RBE_tls_client_auth_key,src=${RBE_tls_client_auth_key} \
#--secret id=RBE_tls_client_auth_cert,src=${RBE_tls_client_auth_cert} \
#"

cmake-re -S . -B build/msan-build -DCMAKE_TOOLCHAIN_FILE=environments/linux-ubuntu-2404-msan-cxx23.cmake --distributed -j100
cmake-re --build build/msan-build --distributed -j100 --run-test main 

```