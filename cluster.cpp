/* Copyright 2020 Igor Lyamin */

#include "cluster.h"

cluster::cluster() {
  n_ = 0;
  sum_ = point();
}

cluster::cluster(const point& point) {
  n_ = 1;
  sum_ = point;
}

cluster::cluster(const int dimension) : n_(0) {
  std::valarray<double> tmp;
  tmp.resize(dimension, 0);
  sum_.v_arr = tmp;
}

void cluster::reset() {
  sum_.v_arr.resize(sum_.v_arr.size(), 0);
  n_ = 0;
}

void cluster::add(const point& p) {
  std::lock_guard<std::mutex> lock(mutex_);
  sum_.v_arr += p.v_arr;
  ++n_;
}

point cluster::getCenter() const {
  point center = sum_;
  if (n_ != 0 && n_ != 1) {
    center.v_arr /= n_;
  }
  return center;
}
