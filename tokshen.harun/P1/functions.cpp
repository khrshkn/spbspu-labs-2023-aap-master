#include <iostream>
#include <climits>
#include "functions.hpp"

int findSecondMax(std::istream &cin)
{
  const constexpr int max_inp = std::numeric_limits< int >::max();
  const constexpr int min_inp = std::numeric_limits< int >::min();
  int maxInput = INT_MIN;
  int secondMaxInput = INT_MIN;
  int input;
  if (!(cin >> input)) {
    throw std::invalid_argument("Input is not correct\n");
  }
  else {
    maxInput = input;
  }
  while (true) {
    std::cin >> input;
    if (input == 0) {
      break;
    }
    if (input >= max_inp || input <= min_inp) {
      throw std::overflow_error("Overflow!\n");
    }
    if (input > maxInput) {
      secondMaxInput = maxInput;
      maxInput = input;
    }
    else if (input > secondMaxInput && input != maxInput) {
      secondMaxInput = input;
    }
  }
  if (secondMaxInput == INT_MIN) {
    throw std::invalid_argument("You should write min 2 numbers\n");
  }
  else {
    return secondMaxInput;
  }
}
