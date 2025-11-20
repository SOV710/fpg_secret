#include "bignum.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>

BigInt::BigInt(const int n) {
  len = 0;
  memset(value, 0, sizeof(value));
  flag = (n < 0);

  int input = std::abs(n);
  if (input == 0) {
    len = 1;
    value[0] = 0;
    return;
  }

  while (input > 0 && len < MAXSIZE) {
    value[len++] = input % 10;
    input /= 10;
  }
}

void BigInt::print() const {
  if (flag)
    std::cout << '-';
  for (int i = len - 1; i >= 0; --i) {
    std::cout << value[i];
  }
}
