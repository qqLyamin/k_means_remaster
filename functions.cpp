/* Copyright 2020 Igor Lyamin */

/* local */
#include "functions.h"

int getCountOfThreads() {
  return std::thread::hardware_concurrency() - 1;
}

int getDistance(const point& X, const point& Y) {
  double distance = 0;
  for (size_t tmp = 0; tmp < X.v_arr.size(); ++tmp) {
    distance += pow(abs(static_cast<double>((X.v_arr[tmp] - Y.v_arr[tmp]))), 2);
  }
  return distance;  // probably i can return without sqrt
}
