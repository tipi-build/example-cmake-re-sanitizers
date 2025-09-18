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

find_package(compute_array_sum REQUIRED)

add_executable(main test/main.cpp)
target_link_libraries(main compute_array_sum::compute_array_sum)

add_test(NAME main COMMAND ${CMAKE_TEST_LAUNCHER} $<TARGET_FILE:main>)