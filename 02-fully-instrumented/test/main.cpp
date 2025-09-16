#include <print>
#include <array>

#include <compute_array_sum.hpp>

int main() {

  std::array<int,10> arr;
  arr[5] = 0;
  //std::println("Good Morning Caching & Remote Execution :-) {} \n", arr); 
  std::println("Good Morning Caching & Remote Execution :-) {} \n", compute_array_sum(arr)); 
  return 0;
}
