/* Copyright 2020 Igor Lyamin */

#include "point.h"
#include "functions.h"

point::point() {
  v_arr.resize(0);
}

point::point(uint16_t n) {
  v_arr.resize(n, 0);
}

point::point(const std::valarray<double>& income) {
  v_arr = income;
}

bool point::operator==(const point& right) const {
  auto r = this->v_arr == right.v_arr;
  for (size_t i = 0; i < r.size(); ++i) {
    if (!r[i]) return false;
  }
  return true;
}

bool point::operator!=(const point& right) const {
  return !((*this) == right);
}

bool point::operator<(const point& right) const {
  point tmp(v_arr.size());
  return getDistance(*this, tmp) < getDistance(right, tmp);
}

std::istream& operator>>(std::istream& is, point& p) {
  for (size_t i = 0; i < p.v_arr.size(); ++i) {
    is >> p.v_arr[i];
  }
  return is;
}

std::ostream& operator<<(std::ostream& is, const point& p) {
  for (size_t i = 0; i < p.v_arr.size(); ++i) {
    is << p.v_arr[i] << " ";
  }
  return is << "\n";
}
