#include <print>
#include <array>

#include <compute_array_sum.hpp>

int main() {
  int x;
  int w = 0;
  int y = x + 1 / w;

  std::array<int,10> arr;
  arr[5] = y;
  std::println("Array sum: {} \n", compute_array_sum(arr)); 
  return 0;
}
 