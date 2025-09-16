cmake_minimum_required(VERSION 3.27.6)

project(example-cmake-re-sanitizers)
enable_testing()

 # Load toolchain specific <CMAKE_TOOLCHAIN_FILE name>.sanitize-ignorelist
cmake_path(GET CMAKE_TOOLCHAIN_FILE STEM msan_ignore_list_path)
set(msan_ignore_list_path "${CMAKE_CURRENT_LIST_DIR}/${msan_ignore_list_path}.sanitize-ignorelist")
if(NOT EXISTS "${msan_ignore_list_path}")
  message(FATAL_ERROR "Failed to find sanitizer ignore list at path ${msan_ignore_list_path}")
endif()

list(APPEND MSAN_FLAGS 
  -fsanitize-ignorelist=${msan_ignore_list_path}
)
add_compile_options(
  -fsanitize-ignorelist=${msan_ignore_list_path}
)
add_link_options(
  -fsanitize-ignorelist=${msan_ignore_list_path}
)

# BEGIN - HFC Initialization
set(FETCHCONTENT_QUIET OFF)
include(FetchContent)

set(hfc_REPOSITORY https://github.com/tipi-build/hfc)
set(hfc_REVISION 42180f1fb49d5301b1167947335e54ebe76f2573)

include(HermeticFetchContent OPTIONAL RESULT_VARIABLE hfc_included) 
if(NOT hfc_included)
  FetchContent_Populate(hfc
    GIT_REPOSITORY https://github.com/tipi-build/hfc.git
    GIT_TAG ${hfc_REVISION}
    SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/cache/hfc-${hfc_REVISION}/src"
    SUBBUILD_DIR "${CMAKE_CURRENT_LIST_DIR}/cache/hfc-${hfc_REVISION}/subbuild"
    BINARY_DIR "${CMAKE_CURRENT_LIST_DIR}/cache/hfc-${hfc_REVISION}/bin"
  )
  FetchContent_GetProperties(hfc)
  message(STATUS "Hermetic FetchContent ${hfc_REVISION} available at '${hfc_SOURCE_DIR}'")
  list(APPEND CMAKE_MODULE_PATH "${hfc_SOURCE_DIR}/cmake")
  include(HermeticFetchContent) 
endif()
# END - HFC Initialization


# Provision Dependencies
FetchContent_Declare(
  compute_array_sum
  GIT_REPOSITORY https://github.com/tipibuild/unittest-compute_array_sum.git
  GIT_TAG        9cbe670be865508690209c64020fbd8bd6d0738f
)

FetchContent_MakeHermetic(compute_array_sum)
HermeticFetchContent_MakeAvailableAtBuildTime(compute_array_sum)

add_executable(main test/main.cpp)
target_link_libraries(main compute_array_sum::compute_array_sum)

add_test(NAME main COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} $<TARGET_FILE:main>)