#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>



void print_vec(const std::vector<int> &vec) {
  for (auto element: vec) {
    std::cout << element << ' '; 
  }
  std::cout << std::endl;
}

int cal_vec(std::vector<int> &input_vec) {
  int len = input_vec.size();
  std::vector<int> const_vec;
  const_vec.assign(input_vec.size(), 1);
  const_vec[len - 1] = 0;

  int count = 0; 

  while (input_vec[0] != input_vec[len - 1]) {
    std::transform(input_vec.begin(), input_vec.end(), const_vec.begin(),
                   input_vec.begin(), std::plus<int>());
    count++;
    // Adjust
    for (int i = len - 1; i > 0; i--) {
      if (input_vec[i] >= input_vec[i - 1]) {
        break;
      } else {
        int tmp = input_vec[i-1];
        input_vec[i-1] = input_vec[i];
        input_vec[i] = tmp;
      }
    }
    print_vec(input_vec);
  }

  return count;
}

int main(int argc, char **argv) {

  int a[] = {1,2,4,4,5,6,7};
  int len = sizeof(a)/sizeof(a[0]);
  std::vector<int> input_vec(a, a+len);
  std::sort(input_vec.begin(), input_vec.end());
  print_vec(input_vec);
  int count = cal_vec(input_vec);
  std::cout << "count = " << count << std::endl;

  return 0;
}
