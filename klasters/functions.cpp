/* Copyright 2020 Igor Lyamin */

#include "functions.h"

int getCountOfThreads() {
  SYSTEM_INFO sysinfo;
  GetSystemInfo(&sysinfo);
  int numCPU = sysinfo.dwNumberOfProcessors;
  numCPU = std::thread::hardware_concurrency() == 0 ?
      numCPU : std::thread::hardware_concurrency();
  return numCPU - 1;
}

int getDistance(const point& X, const point& Y) {
  double distance = 0;
  for (size_t tmp = 0; tmp < X.v_arr.size(); ++tmp) {
    distance += pow(abs(static_cast<double>((X.v_arr[tmp] - Y.v_arr[tmp]))), 2);
  }
  return distance;  // probably i can return without sqrt
}

