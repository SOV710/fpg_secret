#pragma once

#include <cstdio>
#include <cstring>

constexpr int MAXN = 9999;
constexpr int MAXSIZE = 10024;
constexpr int DLEN = 4;

struct BigInt {
  int value[MAXSIZE], len;
  bool flag;

  BigInt() {
    len = 1;
    memset(value, 0, sizeof(value));
    flag = false;
  }

  BigInt(const int);
  BigInt(const char *);
  BigInt(const BigInt &);

  BigInt &operator=(const BigInt &);
  BigInt operator+(const BigInt &) const;
  BigInt operator-(const BigInt &) const;
  BigInt operator*(const BigInt &) const;
  BigInt operator/(const BigInt &) const;
  int operator%(const BigInt &) const;

  BigInt operator^(const BigInt &) const;

  bool operator<(const BigInt &) const;
  bool operator<(const int &t) const;

  void print() const;
};
