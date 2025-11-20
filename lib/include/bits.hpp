#pragma once

#include <concepts>

template <typename T>
concept Integer = std::integral<T>;

template <Integer T> T bitAbs(T x) {
  constexpr int shift = sizeof(T) * 8 - 1;
  return (x ^ (x >> shift)) - (x >> shift);
}

template <Integer T> T bitSameSign(T a, T b) { return ((a ^ b) >= 0); }

template <Integer T> T bitMax(T a, T b) {
  constexpr int shift = sizeof(T) * 8 - 1;
  return (b & ((a - b) >> shift)) | (a & (~((a - b) >> shift)));
}

template <Integer T> T bitMin(T a, T b) {
  constexpr int shift = sizeof(T) * 8 - 1;
  return (a & ((a - b) >> shift)) | (b & (~((a - b) >> shift)));
}

template <Integer T> void bitSwap(T &a, T &b) {
  a ^= b;
  b ^= a;
  a ^= b;
}

template <Integer T> T getBit(T a, T b) { return (a >> b) & 1; }

template <Integer T> T unsetBit(T a, T b) {
  return a & ~(static_cast<T>(1) << b);
}

template <Integer T> T setBit(T a, T b) { return a | (static_cast<T>(1) << b); }

template <Integer T> T flapBit(T a, T b) {
  return a ^ (static_cast<T>(1) << b);
}

template <Integer T> T popcount(T a) {
  int cnt = 0;
  while (a) {
    cnt += a & 1;
    a >>= 1;
  }
  return cnt;
}
